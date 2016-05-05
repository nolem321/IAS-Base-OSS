/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/LogicalBinaryOperFamily.cpp
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
#include "LogicalBinaryOperFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class LogicalBinaryOperAnd : public LogicalBinaryOperFamily {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);

		if(!bLeft)
			return false;

		return ptrRight->evaluateBoolean(pCtx);
	};

protected:
	LogicalBinaryOperAnd(const DM::DataFactory* pDataFactory,BooleanExpr* pLeft, BooleanExpr* pRight):
		LogicalBinaryOperFamily(pDataFactory,pLeft,pRight){}

	friend class ::IAS::Factory<LogicalBinaryOperAnd>;

};
/*************************************************************************/
class LogicalBinaryOperOr : public LogicalBinaryOperFamily {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		if(bLeft)
			return true;
		return ptrRight->evaluateBoolean(pCtx);
	};

protected:
	LogicalBinaryOperOr(const DM::DataFactory* pDataFactory, BooleanExpr* pLeft, BooleanExpr* pRight):
		LogicalBinaryOperFamily(pDataFactory,pLeft,pRight){}
	friend class ::IAS::Factory<LogicalBinaryOperOr>;

};
/*************************************************************************/
LogicalBinaryOperFamily::LogicalBinaryOperFamily(const DM::DataFactory* pDataFactory,BooleanExpr* pLeft, BooleanExpr* pRight){
	IAS_TRACER;

	setType(pDataFactory->getDefaultType(DM::Type::BooleanType));
	ptrLeft=pLeft;
	ptrRight=pRight;
}
/*************************************************************************/
LogicalBinaryOperFamily::~LogicalBinaryOperFamily() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BooleanExpr* LogicalBinaryOperFamily::Create(const DM::DataFactory* pDataFactory,
												BooleanExpr* pLeft,
												 BooleanExpr* pRight,
												 TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pLeft);
	IAS_CHECK_IF_NULL(pRight);

	IAS_DFT_FACTORY<LogicalBinaryOperFamily>::PtrHolder ptrLogicalBinaryOper;

	if(aTypeInfoProxy == &typeid(Model::Expr::LogicalAndNode)){
		ptrLogicalBinaryOper = IAS_DFT_FACTORY<LogicalBinaryOperAnd>::Create(pDataFactory,pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::LogicalOrNode)){
		ptrLogicalBinaryOper = IAS_DFT_FACTORY<LogicalBinaryOperOr>::Create(pDataFactory,pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrLogicalBinaryOper.pass();
}
/*************************************************************************/
}
}
}
}
}
