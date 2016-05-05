/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/FunCall.cpp
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
#include "FunCall.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Program.h"
#include "../ProgramContext.h"
#include "ExprList.h"

#include "lang/interpreter/exe/dec/Parameters.h"
#include "lang/model/dec/ResultDeclarationNode.h"

#include "FunCallArray.h"
#include "FunCallValue.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
FunCall::FunCall(Program* pProgram, ExprList* pExprList){
	IAS_TRACER;
	this->pProgram=pProgram;
	ptrExprList=pExprList;
	//TODO (L) make method in the Program class.
	setType(pProgram->getParameters()->getType()->asComplexType()->
			getProperties().getProperty(Model::Dec::ResultDeclarationNode::CStrResultVariable)->getType());
}
/*************************************************************************/
FunCall::~FunCall() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Expr* FunCall::Create(Program* pProgram, ExprList* pExprList){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Create: "<<(pProgram->isReturningResult() ? "Array" : "Value"));

	IAS_DFT_FACTORY<Expr>::PtrHolder ptrResult;

	if(pProgram->getParameters()->getResultProperty()->isMulti()){
		ptrResult = IAS_DFT_FACTORY<FunCallArray>::Create(pProgram, pExprList);
	}else{
		ptrResult = IAS_DFT_FACTORY<FunCallValue>::Create(pProgram, pExprList);
	}

	return ptrResult.pass();
}
/*************************************************************************/
}
}
}
}
}
