/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/UnaryFloatExpr.cpp
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
#include "UnaryFloatExpr.h"
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
class UnaryFloatExprNegative : public UnaryFloatExpr {
public:
	virtual Float evaluateFloat(Context *pCtx) const{
		IAS_TRACER;
		Float fValue = ptrExpr->evaluateFloat(pCtx);
		return -fValue;
	};
protected:
	UnaryFloatExprNegative(Expr* pExpr):
		UnaryFloatExpr(pExpr){}
	friend class ::IAS::Factory<UnaryFloatExprNegative>;
};
/*************************************************************************/
UnaryFloatExpr::UnaryFloatExpr(Expr* pExpr):
		UnaryExprFamily(pExpr){
	IAS_TRACER;
}
/*************************************************************************/
UnaryFloatExpr::~UnaryFloatExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
UnaryFloatExpr* UnaryFloatExpr::Create(Expr* pExpr, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<UnaryFloatExpr>::PtrHolder ptrUnaryFloatExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::NegativeNode)){
		ptrUnaryFloatExpr = IAS_DFT_FACTORY<UnaryFloatExprNegative>::Create(pExpr);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for a float argument."));
	}

	return ptrUnaryFloatExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
