/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/UnaryDataObjectExpr.cpp
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
#include "UnaryDataObjectExpr.h"
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
class UnaryDataObjectExprNegative : public UnaryDataObjectExpr {
public:
	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{
		IAS_TRACER;
		int iValue = ptrExpr->evaluateInt(pCtx);
		refResult->setInteger(-iValue);
	};
protected:
	UnaryDataObjectExprNegative(Expr* pExpr):
		UnaryDataObjectExpr(pExpr){}
	friend class ::IAS::Factory<UnaryDataObjectExprNegative>;
};
/*************************************************************************/
UnaryDataObjectExpr::UnaryDataObjectExpr(Expr* pExpr):
		UnaryExprFamily(pExpr){
	IAS_TRACER;
}
/*************************************************************************/
UnaryDataObjectExpr::~UnaryDataObjectExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
UnaryDataObjectExpr* UnaryDataObjectExpr::Create(Expr* pExpr, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<UnaryDataObjectExpr>::PtrHolder ptrUnaryDataObjectExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::NegativeNode)){
		ptrUnaryDataObjectExpr = IAS_DFT_FACTORY<UnaryDataObjectExprNegative>::Create(pExpr);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for a date object argument."));
	}

	return ptrUnaryDataObjectExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
