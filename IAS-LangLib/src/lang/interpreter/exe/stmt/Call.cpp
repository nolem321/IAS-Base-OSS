/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Call.cpp
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
#include "Call.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../expr/ExprList.h"
#include "../Context.h"
#include "../ProgramContext.h"
#include "../Program.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
Call::Call(Program* pProgram, Expr::ExprList* pExprList):
	pProgram(pProgram),
	ptrExprList(pExprList){
	IAS_TRACER;
}
/*************************************************************************/
Call::~Call() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Call::execute(Exe::Context *pCtx) const{
	IAS_TRACER;

	IAS_DFT_FACTORY<ProgramContext>::PtrHolder ptrContext(
			IAS_DFT_FACTORY<ProgramContext>::Create(pCtx->getDataFactory(),pProgram));
	ptrExprList->evaluate(pCtx,ptrContext->getParameters());

	ptrContext->execute(pCtx);
}
/*************************************************************************/
}
}
}
}
}
