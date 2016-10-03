/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/ResultHandlerForIO.cpp
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
#include "ResultHandlerForIO.h"
#include<qs/log/LogLevel.h>

#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>

#include "../exception/RollbackMeException.h"

#include "../io/Output.h"
#include "../logic/LogicBase.h"

#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>


using namespace ::org::invenireaude::qsystem;


namespace IAS{
using namespace Lang;
namespace QS {
namespace Workers {
namespace Proc {
namespace Prog {

/*************************************************************************/
ResultHandlerForIO::ResultHandlerForIO(const ::IAS::DM::DataFactory *pDataFactory,
									   Logic::LogicBase* pLogic)throw():
	pDataFactory(pDataFactory),
	pLogic(pLogic){

	IAS_TRACER;
}
/*************************************************************************/
ResultHandlerForIO::~ResultHandlerForIO() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ResultHandlerForIO::handle(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
									  Lang::Interpreter::Exe::ProgramContext *pProgramContext){
	IAS_TRACER;

	if(pProgramContext->hasResult()){

		DM::DataObjectPtr dmOutput(pProgramContext->getResult());

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"has Result: null=="<<dmOutput.isNull());
		pLogic->getOutput()->send(dmContext,dmOutput);

	}
}
/*************************************************************************/
void ResultHandlerForIO::handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
									  	 Lang::Interpreter::Exe::ProgramContext *pProgramContext,
										 Lang::Interpreter::Exe::InterpreterProgramException& e){
	IAS_TRACER;


	const DM::Property* pProperty = pProgramContext->getParameters()->getType()->asComplexType()->getProperties().getProperty(1);

	if(workers::DataFactory::GetInstance()->getRoutingType()->equals(pProperty->getType()))
		IAS_THROW(RollbackMeException("Program has failed in the RAW mode."));

	try{

		try{
			dmContext->setException(e.getValue());
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),e.getValue()->getType()->getFullName()+", info: "+e.getValue()->getString("info"));

		}catch(DM::RuntimeException& e2){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),workers::DataFactory::GetInstance()->getExceptionType()->getFullName()
						<<" was expected, but got: "<<e.getValue()->getType()->getFullName()<<"\n"
						<<DM::XML::XMLHelper::Stringify(pDataFactory,e.getValue()));
		}

		try{
			pLogic->getError()->send(dmContext,pProgramContext->getParameters()->getDataObject(pProperty));
		}catch(ItemNotFoundException&){
				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"No error defined, [ "
						<<"exception:"<<DM::XML::XMLHelper::Stringify(pDataFactory,e.getValue()));
		}

		return;

	}catch(Exception& e2){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Send to error failed, execute method"
									" does not know what to do with this exception:"+e2.toString() +
									DM::XML::XMLHelper::Stringify(pDataFactory,e.getValue()));
	}

	IAS_THROW(RollbackMeException("Program has failed or RAW mode (the routing data type)."));

}
/*************************************************************************/
}
}
}
}
}
