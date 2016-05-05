/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/UnaryIntegerExpr.cpp
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
#include "UnaryIntegerExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include <lang/exception/ScriptUsageException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class UnaryIntegerExprNegative : public UnaryIntegerExpr {
public:
	virtual int evaluateInt(Context *pCtx) const{
		IAS_TRACER;
		int iValue = ptrExpr->evaluateInt(pCtx);
		return -iValue;
	};
protected:
	UnaryIntegerExprNegative(Expr* pExpr):
		UnaryIntegerExpr(pExpr){}
	friend class  ::IAS::Factory<UnaryIntegerExprNegative>;
};
/*************************************************************************/
UnaryIntegerExpr::UnaryIntegerExpr(Expr* pExpr):
		UnaryExprFamily(pExpr){
	IAS_TRACER;
}
/*************************************************************************/
UnaryIntegerExpr::~UnaryIntegerExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
UnaryIntegerExpr* UnaryIntegerExpr::Create(Expr* pExpr, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<UnaryIntegerExpr>::PtrHolder ptrUnaryIntegerExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::NegativeNode)){
		ptrUnaryIntegerExpr = IAS_DFT_FACTORY<UnaryIntegerExprNegative>::Create(pExpr);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for an integer argument."));
	}

	return ptrUnaryIntegerExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
