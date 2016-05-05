/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/ProgramSet.cpp
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
#include "ProgramSet.h"
#include<qs/log/LogLevel.h>

#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/interpreter/exe/stmt/Statement.h>
#include <lang/model/stmt/StatementNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>
#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>

#include "../exception/RollbackMeException.h"

#include "../io/Output.h"
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <qs/ui/Messages.h>

using namespace ::org::invenireaude::qsystem;


namespace IAS{
using namespace Lang;
namespace QS {
namespace Workers {
namespace Proc {
namespace Prog {

/*************************************************************************/
ProgramSet::ProgramSet(const ::IAS::DM::DataFactory *pDataFactory, ResultHandler *pResultHandler):
	pDataFactory(pDataFactory),
	ptrResultHandler(pResultHandler){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);
}
/*************************************************************************/
ProgramSet::~ProgramSet() throw(){
	IAS_TRACER;


	if(hmPrograms.size()){
		IAS_LOG(LogLevel::INSTANCE.isProfile() , "*** Script Performance Report ***");

	for(ProgramMap::const_iterator it = hmPrograms.begin(); it != hmPrograms.end(); it++)
		IAS_LOG(LogLevel::INSTANCE.isProfile() ,it->second->strName<<it->second->tsrExe);

	}
}
/*************************************************************************/
void ProgramSet::addProgram(::IAS::Lang::Interpreter::Exe::Program *pProgram,
							const String& strName){
	IAS_TRACER;

	hmPrograms[pProgram]=IAS_DFT_FACTORY<StatsEntry>::Create<const String&>(strName);
	hmProgramByName[strName]=pProgram;
}
/*************************************************************************/
bool ProgramSet::match(::IAS::Lang::Interpreter::Exe::Program *pProgram,
		   	   	   	   const ::IAS::DM::Type* pCtxType,
		   	   	   	   const ::IAS::DM::Type* pDataType){
	IAS_TRACER;

	const DM::PropertyList& lstProperties(pProgram->getParameters()->getType()->asComplexType()->getProperties());

	if(lstProperties.getSize() < 2 ){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"NoMatch: "<<hmPrograms[pProgram]->strName);
		return false;
	}

	if(!pCtxType->isAssignableTo(lstProperties.getProperty(0)->getType())){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"NoMatch: "<<hmPrograms[pProgram]->strName);
		return false;
	}

	if(!pDataType->isAssignableTo(lstProperties.getProperty(1)->getType())){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"NoMatch: "<<hmPrograms[pProgram]->strName);
		return false;
	}

	return true;
}
/*************************************************************************/
void ProgramSet::execute(::IAS::Lang::Interpreter::Exe::Program *pProgram,
						 ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						  DM::DataObject* dmData){
		IAS_TRACER;

	TimeSample ts(true);

	if(!pProgram)
		IAS_THROW(BadUsageException("Program not loaded."));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Execute: "<<hmPrograms[pProgram]->strName);

	IAS_DFT_FACTORY<Interpreter::Exe::ProgramContext>::PtrHolder ptrProgramContext(
			IAS_DFT_FACTORY<Interpreter::Exe::ProgramContext>::Create(pDataFactory,pProgram));

	const DM::PropertyList& lstProperties(pProgram->getParameters()->getType()->asComplexType()->getProperties());

	ptrProgramContext->getParameters()->setDataObject(lstProperties.getProperty(0),dmContext);
	ptrProgramContext->getParameters()->setDataObject(lstProperties.getProperty(1),dmData);

	try{
		ptrProgramContext->execute();

	//TODO test context update after the program execution
	//	dmContext = ::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->
	//			getContextType()->cast(ptrProgramContext->getParameters()->getDataObject(lstProperties.getProperty(0)));

		if(!ptrResultHandler.isNull())
			ptrResultHandler->handle(dmContext,ptrProgramContext);

	}catch(Lang::Interpreter::Exe::InterpreterProgramException& e){

		UserMessage(UI::Messages::MSGE_ScriptException)<<e.getName()<<e.getInfo();

		if(!ptrResultHandler.isNull())
			ptrResultHandler->handleException(dmContext,ptrProgramContext,e);
		else
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),e.getName()<<":"<<e.getInfo());

	}catch(Lang::Interpreter::Exe::InterpreterException& e){

		UserMessage(UI::Messages::MSGE_ScriptFailed)<<e.getName()<<e.getInfo();

		IAS_THROW(RollbackMeException(String("Program error: ")+e.getName()+":"+e.getInfo()));
	}

	Mutex::Locker locker(mutex);
	hmPrograms[pProgram]->tsrExe.addSample(ts);
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"DONE!");
}
/*************************************************************************/
::IAS::Lang::Interpreter::Exe::Program *ProgramSet::getProgram(const String& strProgramName)const{
	IAS_TRACER;

	if(hmProgramByName.count(strProgramName)==0)
		IAS_THROW(ItemNotFoundException(strProgramName+" - program not found."));

	return hmProgramByName.at(strProgramName);
}
/*************************************************************************/
unsigned int ProgramSet::execute(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 DM::DataObject* dmData){
	IAS_TRACER;

	//TODO more efficient for a larger number of programs.

	unsigned int iCounter = 0;

	for(ProgramMap::iterator it=hmPrograms.begin(); it != hmPrograms.end(); it++)
		if(match(it->first, dmContext->getType(), dmData->getType())){
			execute(it->first,dmContext,dmData);
			iCounter++;
		}

	return iCounter;
}
/*************************************************************************/
void ProgramSet::execute(const String& strProgramName,
						 ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						  DM::DataObject* dmData){
		IAS_TRACER;

	::IAS::Lang::Interpreter::Exe::Program *pProgram=getProgram(strProgramName);
	if(match(pProgram, dmContext->getType(), dmData->getType()))
		execute(pProgram,dmContext,dmData);
}
/*************************************************************************/
void ProgramSet::setResultHandler(ResultHandler *pResultHandler){
	IAS_TRACER;
	ptrResultHandler=pResultHandler;
}
/*************************************************************************/
}
}
}
}
}
