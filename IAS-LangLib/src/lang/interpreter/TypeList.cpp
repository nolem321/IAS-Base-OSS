/*
 * File: IAS-LangLib/src/lang/interpreter/TypeList.cpp
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
#include "TypeList.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/expr/ExprList.h>
#include <lang/interpreter/exe/expr/Expr.h>
#include "../script/parser.h"

namespace IAS {
namespace Lang {
namespace Interpreter {

/*************************************************************************/
TypeList::TypeList(bool bAnyType):bAnyThing(bAnyType){
	IAS_TRACER;
}
/*************************************************************************/
TypeList::TypeList(const Exe::Expr::ExprList* pExprList):bAnyThing(false){
	IAS_TRACER;

	const Exe::Expr::ExprList::OrderedExprTab& tabExpr(pExprList->getExprVector());

	for(int iIdx=0;iIdx<tabExpr.size();iIdx++){
		lstTypes.push_back(tabExpr[iIdx]->getType());
	}

}
/*************************************************************************/
void TypeList::append(const IAS::DM::Type* pType){
	IAS_TRACER;
	bAnyThing=false;

	lstTypes.push_back(pType);
}
/*************************************************************************/
const ::IAS::DM::Type* TypeList::operator[](size_t iIdx)const{
	IAS_TRACER;
	if(iIdx<0 || iIdx>lstTypes.size())
		IAS_THROW(InternalException("Out of range."));
	return lstTypes.at(iIdx);
}
/*************************************************************************/
}
}
}
