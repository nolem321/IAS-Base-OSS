/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/TryCatch.cpp
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
#include "TryCatch.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "CatchList.h"
#include "Catch.h"

#include <lang/interpreter/exe/exception/InterpreterProgramException.h>


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
TryCatch::TryCatch(Statement* pStatement, CatchList* pCatchList):
	ptrStatement(pStatement),
	ptrCatchList(pCatchList){
	IAS_TRACER;
}
/*************************************************************************/
TryCatch::~TryCatch() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TryCatch::execute(Context *pCtx) const{
	IAS_TRACER;

	try{

		ptrStatement->execute(pCtx);

	}catch(InterpreterProgramException& e){

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Catching: "<<e.getValue()->getType()->getFullName());

		Catch* pCatch;

		if(ptrCatchList->match(e.getValue()->getType(),pCatch))
			pCatch->execute(pCtx,e.getValue());
		else
			throw;
	}
}
/*************************************************************************/
}
}
}
}
}
