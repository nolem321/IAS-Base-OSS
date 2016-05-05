/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryBooleanExpr.cpp
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
#include "BinaryBooleanExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../exception/InterpreterRuntimeException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class BinaryBooleanExprPlusBoolean : public BinaryBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft || bRight;
	};
protected:
	BinaryBooleanExprPlusBoolean(Expr* pLeft, Expr* pRight):
		BinaryBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<BinaryBooleanExprPlusBoolean>;
};
/*************************************************************************/
class BinaryBooleanExprMultiplyBoolean : public BinaryBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft && bRight;
	};
protected:
	BinaryBooleanExprMultiplyBoolean(Expr* pLeft, Expr* pRight):
	BinaryBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<BinaryBooleanExprMultiplyBoolean>;
};
/*************************************************************************/
BinaryBooleanExpr::BinaryBooleanExpr(Expr* pLeft, Expr* pRight):
		BinaryExprFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
BinaryBooleanExpr::~BinaryBooleanExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryBooleanExpr* BinaryBooleanExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryBooleanExpr>::PtrHolder ptrBinaryBooleanExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		return IAS_DFT_FACTORY<BinaryBooleanExprPlusBoolean>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::MultiplyNode))
		return IAS_DFT_FACTORY<BinaryBooleanExprMultiplyBoolean>::Create(pLeft,pRight);


	IAS_THROW(InternalException("No operator for this node."));

}
/*************************************************************************/
}
}
}
}
}
