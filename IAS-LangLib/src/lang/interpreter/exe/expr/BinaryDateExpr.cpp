/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryDateExpr.cpp
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
#include "BinaryDateExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class BinaryDateExprPlusDate : public BinaryDateExpr {
public:
	virtual ::IAS::Date evaluateDate(Context *pCtx) const{
		IAS_TRACER;
		return ::IAS::Date(ptrLeft->evaluateDate(pCtx) + ptrRight->evaluateDate(pCtx));
	};

protected:
	BinaryDateExprPlusDate(Expr* pLeft, Expr* pRight):
		BinaryDateExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryDateExprPlusDate>;

};

/*************************************************************************/
class BinaryDateExprMinusDate : public BinaryDateExpr {
public:
	virtual ::IAS::Date evaluateDate(Context *pCtx) const{
		IAS_TRACER;
		return ptrLeft->evaluateDate(pCtx) - ptrRight->evaluateDate(pCtx);
	};

protected:
	BinaryDateExprMinusDate(Expr* pLeft, Expr* pRight):
		BinaryDateExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryDateExprMinusDate>;

};

/*************************************************************************/
BinaryDateExpr::BinaryDateExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryDateExpr::~BinaryDateExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryDateExpr* BinaryDateExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryDateExpr>::PtrHolder ptrBinaryDateExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryDateExpr = IAS_DFT_FACTORY<BinaryDateExprPlusDate>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::SubtractionNode)){
		ptrBinaryDateExpr = IAS_DFT_FACTORY<BinaryDateExprMinusDate>::Create(pLeft,pRight);
	}else{
		IAS_THROW(InternalException(String("No operator for this node: ")+aTypeInfoProxy.ti->name()));
	}

	return ptrBinaryDateExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
