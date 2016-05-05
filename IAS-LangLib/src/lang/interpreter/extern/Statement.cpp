/*
 * File: IAS-LangLib/src/lang/interpreter/extern/Statement.cpp
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
#include "Statement.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/interpreter/exe/exception/InterpreterException.h>
#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {

/*************************************************************************/
void Statement::execute(Exe::Context *pCtx) const{
	IAS_TRACER;

	try{
		executeExternal(pCtx);

	}catch(Exe::InterpreterException& e){
		throw;
	}catch(Exception& e){
		IAS_THROW(Exe::InterpreterException(e.toString()));
	}catch(std::exception& e){
		IAS_THROW(Exe::InterpreterException(e.what()));
#ifdef __GNUC__
	}catch(__cxxabiv1::__forced_unwind&){
		throw;
#endif
	}catch(...){
		IAS_THROW(Exe::InterpreterException("External program failed."));
	}
}
/*************************************************************************/
}
}
}
}
