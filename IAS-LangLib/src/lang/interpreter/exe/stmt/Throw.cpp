/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Throw.cpp
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
#include "Throw.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "LeftSide.h"
#include "../expr/Expr.h"
#include "lang/model/dec/DeclarationNode.h"
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
Throw::Throw() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Throw::Throw(Expr::Expr *pExpr){
	IAS_TRACER;

	this->ptrExpr=pExpr;
}
/*************************************************************************/
Throw::~Throw() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Throw::execute(Context *pCtx) const{
	IAS_TRACER;

	if(hasExpression()){

		DM::DataObjectPtr ptrValueObject;
		ptrExpr->evaluate(pCtx, ptrValueObject);

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Throwing: "<<ptrValueObject->getType()->getFullName())

		IAS_THROW(InterpreterProgramException(ptrValueObject));

	}else{
		//TODO not implemented rethrow
		IAS_THROW(InternalException("not implemented rethrow"))
	}
}
/*************************************************************************/
}
}
}
}
}
