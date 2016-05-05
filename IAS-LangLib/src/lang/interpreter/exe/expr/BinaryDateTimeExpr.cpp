/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryDateTimeExpr.cpp
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
#include "BinaryDateTimeExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class BinaryDateTimeExprPlusDateTime : public BinaryDateTimeExpr {
public:
	virtual ::IAS::DateTime evaluateDateTime(Context *pCtx) const{
		IAS_TRACER;
		return ::IAS::DateTime(ptrLeft->evaluateDateTime(pCtx) + ptrRight->evaluateDateTime(pCtx));
	};

protected:
	BinaryDateTimeExprPlusDateTime(Expr* pLeft, Expr* pRight):
		BinaryDateTimeExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryDateTimeExprPlusDateTime>;

};

/*************************************************************************/
class BinaryDateTimeExprMinusDateTime : public BinaryDateTimeExpr {
public:
	virtual ::IAS::DateTime evaluateDateTime(Context *pCtx) const{
		IAS_TRACER;
		return ptrLeft->evaluateDateTime(pCtx) - ptrRight->evaluateDateTime(pCtx);
	};

protected:
	BinaryDateTimeExprMinusDateTime(Expr* pLeft, Expr* pRight):
		BinaryDateTimeExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryDateTimeExprMinusDateTime>;

};

/*************************************************************************/
BinaryDateTimeExpr::BinaryDateTimeExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryDateTimeExpr::~BinaryDateTimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryDateTimeExpr* BinaryDateTimeExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryDateTimeExpr>::PtrHolder ptrBinaryDateTimeExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryDateTimeExpr = IAS_DFT_FACTORY<BinaryDateTimeExprPlusDateTime>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::SubtractionNode)){
		ptrBinaryDateTimeExpr = IAS_DFT_FACTORY<BinaryDateTimeExprMinusDateTime>::Create(pLeft,pRight);
	}else{
		IAS_THROW(InternalException(String("No operator for this node: ")+aTypeInfoProxy.ti->name()));
	}

	return ptrBinaryDateTimeExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
