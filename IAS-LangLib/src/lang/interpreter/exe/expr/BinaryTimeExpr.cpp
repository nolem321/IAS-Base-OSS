/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryTimeExpr.cpp
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
#include "BinaryTimeExpr.h"
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
class BinaryTimeExprPlusTime : public BinaryTimeExpr {
public:
	virtual ::IAS::Time evaluateTime(Context *pCtx) const{
		IAS_TRACER;
		return ::IAS::Time(ptrLeft->evaluateTime(pCtx) + ptrRight->evaluateTime(pCtx));
	};

protected:
	BinaryTimeExprPlusTime(Expr* pLeft, Expr* pRight):
		BinaryTimeExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryTimeExprPlusTime>;

};

/*************************************************************************/
class BinaryTimeExprMinusTime : public BinaryTimeExpr {
public:
	virtual ::IAS::Time evaluateTime(Context *pCtx) const{
		IAS_TRACER;
		return ptrLeft->evaluateTime(pCtx) - ptrRight->evaluateTime(pCtx);
	};

protected:
	BinaryTimeExprMinusTime(Expr* pLeft, Expr* pRight):
		BinaryTimeExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryTimeExprMinusTime>;

};

/*************************************************************************/
BinaryTimeExpr::BinaryTimeExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryTimeExpr::~BinaryTimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryTimeExpr* BinaryTimeExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryTimeExpr>::PtrHolder ptrBinaryTimeExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryTimeExpr = IAS_DFT_FACTORY<BinaryTimeExprPlusTime>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::SubtractionNode)){
		ptrBinaryTimeExpr = IAS_DFT_FACTORY<BinaryTimeExprMinusTime>::Create(pLeft,pRight);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for a date/time argument."));
	}

	return ptrBinaryTimeExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
