/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/ResultHandler.cpp
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
#include "ResultHandler.h"
#include<qs/log/LogLevel.h>

#include <lang/interpreter/exe/ProgramContext.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>

#include "qs/workers/proc/exception/RollbackMeException.h"

#include "qs/workers/proc/io/Output.h"
#include "qs/workers/proc/logic/LogicBase.h"

#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic{
namespace SPS {

/*************************************************************************/
ResultHandler::ResultHandler(const ::IAS::DM::DataFactory *pDataFactory)throw():
	DefaultResultHandler(pDataFactory){

	IAS_TRACER;
}
/*************************************************************************/
ResultHandler::~ResultHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ResultHandler::handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
									Lang::Interpreter::Exe::ProgramContext *pProgramContext,
									Lang::Interpreter::Exe::InterpreterProgramException& e){
	IAS_TRACER;


	if(pProcessCacheEntry)
		pProcessCacheEntry->failed(e);

	//ResultHandlerForIO::handleException(dmContext, pProgramContext, e);
}
/*************************************************************************/
}
}
}
}
}
}
