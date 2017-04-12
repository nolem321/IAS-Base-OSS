/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/FunCallValue.cpp
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
#include "FunCallValue.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Program.h"
#include "../ProgramContext.h"
#include "ExprList.h"

#include "lang/interpreter/exe/dec/Parameters.h"
#include "lang/model/dec/ResultDeclarationNode.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
FunCallValue::FunCallValue(Program* pProgram, ExprList* pExprList):
	FunCall(pProgram,pExprList)
{ IAS_TRACER; }
/*************************************************************************/
FunCallValue::~FunCallValue() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void FunCallValue::evaluate(IAS::Lang::Interpreter::Exe::Context* pCtx, IAS::DM::DataObjectPtr& refOutput)const{
	IAS_TRACER;

	IAS_DFT_FACTORY<ProgramContext>::PtrHolder ptrContext(
			IAS_DFT_FACTORY<ProgramContext>::Create(pCtx->getDataFactory(),
			pProgram));

	ptrExprList->evaluate(pCtx,ptrContext->getParameters(),true);

	IAS_LOG(Lang::LogLevel::INSTANCE.isLogic(), "CALLTRACE: >> "<<pProgram->getName()<<DM::XML::XMLHelper::Stringify(pCtx->getDataFactory(),ptrContext->getParameters()));

	ptrContext->execute(pCtx);

	refOutput=ptrContext->getResult();

	IAS_LOG(Lang::LogLevel::INSTANCE.isLogic(), "CALLTRACE: << ");
}
/*************************************************************************/
}
}
}
}
}
