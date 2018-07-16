/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/TaskPool.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "TaskPool.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/task/WaitingRoom.h>
#include <qs/workers/proc/task/WaitingRoomQueue.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"
#include "../ProgramProvider.h"


#include "../prog/DefaultResultHandler.h"

#include <org/invenireaude/qsystem/workers/DaemonControl.h>
#include <org/invenireaude/qsystem/workers/logic/ExeName.h>


using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {


/*************************************************************************/
TaskPool::ResultHandler::ResultHandler(Task::WaitingRoomQueue* pWaitingRoomQueue)throw():
		pWaitingRoomQueue(pWaitingRoomQueue){
	IAS_TRACER;
}
/*************************************************************************/
TaskPool::ResultHandler::~ResultHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TaskPool::ResultHandler::handle(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
									  Lang::Interpreter::Exe::ProgramContext *pProgramContext){
	IAS_TRACER;

	pWaitingRoomQueue->setTaskSuccess(
				dmContext->getMID(),
				pProgramContext->hasResult() ? pProgramContext->getResult() : NULL
				);

}
/*************************************************************************/
void TaskPool::ResultHandler::handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
		 	 	 	 	 	 	 	 	   Lang::Interpreter::Exe::ProgramContext *pProgramContext,
										   Lang::Interpreter::Exe::InterpreterProgramException& e){
	IAS_TRACER;

	pWaitingRoomQueue->setTaskFailure(
				dmContext->getMID(),
				e.getValue()
			);

}
/*************************************************************************/


/*************************************************************************/
TaskPool::TaskPool(const ::org::invenireaude::qsystem::workers::logic::TaskPool* dmParameters,
					 	 	 WCM::WorkContextManager* pWorkContextManager):
	LogicBase(dmParameters, pWorkContextManager){
	IAS_TRACER;

	const DM::DataFactory* pDataFactory = pWorkContextManager->getGlobalContext()->getDataFactory();

	strWaitingRoomQueue = dmParameters->getQueue();

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"WaitingRoomQueue: "<<strWaitingRoomQueue);

	pWaitingRoomQueue = pWorkContextManager->getGlobalContext()->getWaitingRoom()->createQueue(strWaitingRoomQueue);

	IAS_DFT_FACTORY<ResultHandler>::PtrHolder ptrResultHandler(
				IAS_DFT_FACTORY<ResultHandler>::Create(pWaitingRoomQueue));

	ptrProgramSet = IAS_DFT_FACTORY<Prog::ProgramSet>::Create(pDataFactory, ptrResultHandler.pass());

	const workers::logic::Ext::ExeNameList& lstExeNames(dmParameters->getLoadList());

	for(int iIdx=0;iIdx< lstExeNames.size();iIdx++){
		pWorkContextManager->getGlobalContext()->getProgramProvider()->load(lstExeNames.at(iIdx),ptrProgramSet);
	}

	if(!isDM())
		IAS_LOG(QS::LogLevel::INSTANCE.isError(),"Parsing switch is ignored for the Task Pool logic.");
}
/*************************************************************************/
TaskPool::~TaskPool() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TaskPool::receive(bool bNoWait){
	IAS_TRACER;

	String strTaskId;
	pWaitingRoomQueue->getScheduledData(strTaskId, dmData);

	dmContext = workers::DataFactory::GetInstance()->getContextType()->createContext();
	dmContext->setMID(strTaskId);
}
/*************************************************************************/
void TaskPool::compute(){
	IAS_TRACER;

	computeDM(dmContext, dmData);

}
/*************************************************************************/
void TaskPool::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 		  DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==TaskPool starts.");

	if(!dmData.isNull())
		ptrProgramSet->execute(dmContext,dmData);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==TaskPool ends.");
}
/*************************************************************************/
}
}
}
}
}
