/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/DefaultResultHandler.cpp
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
#include "DefaultResultHandler.h"
#include<qs/log/LogLevel.h>

#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include "../exception/RollbackMeException.h"

#include "../io/Output.h"
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
DefaultResultHandler::DefaultResultHandler(const ::IAS::DM::DataFactory *pDataFactory)throw():
	pDataFactory(pDataFactory){
	IAS_TRACER;
}
/*************************************************************************/
DefaultResultHandler::~DefaultResultHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DefaultResultHandler::handle(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
									  Lang::Interpreter::Exe::ProgramContext *pProgramContext){
	IAS_TRACER;

}
/*************************************************************************/
void DefaultResultHandler::handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
		 	 	 	 	 	 	 	 	   Lang::Interpreter::Exe::ProgramContext *pProgramContext,
										   Lang::Interpreter::Exe::InterpreterProgramException& e){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Program failed and does not know what to do with this exception:"<<
									DM::XML::XMLHelper::Stringify(pDataFactory,e.getValue()));


	IAS_THROW(RollbackMeException(String("Program has failed: ")+DM::XML::XMLHelper::Stringify(pDataFactory,e.getValue())));
}
/*************************************************************************/
}
}
}
}
}
