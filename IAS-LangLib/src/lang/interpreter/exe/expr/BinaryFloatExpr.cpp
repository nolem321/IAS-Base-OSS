/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryFloatExpr.cpp
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
#include "BinaryFloatExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../exception/InterpreterException.h"

#include <lang/exception/ScriptUsageException.h>


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
class BinaryFloatExprAdditionFloat : public BinaryFloatExpr {
public:
	virtual Float evaluateFloat(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft+fRight;
	};
protected:
	BinaryFloatExprAdditionFloat(Expr* pLeft, Expr* pRight):
		BinaryFloatExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryFloatExprAdditionFloat>;
};
/*************************************************************************/
class BinaryFloatExprSubtractionFloat : public BinaryFloatExpr {
public:
	virtual Float evaluateFloat(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft-fRight;
	};
protected:
	BinaryFloatExprSubtractionFloat(Expr* pLeft, Expr* pRight):
		BinaryFloatExpr(pLeft,pRight){}

	friend class  ::IAS::Factory<BinaryFloatExprSubtractionFloat>;
};
/*************************************************************************/
class BinaryFloatExprMultiplyFloat : public BinaryFloatExpr {
public:
	virtual Float evaluateFloat(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft*fRight;
	};
protected:
	BinaryFloatExprMultiplyFloat(Expr* pLeft, Expr* pRight):
		BinaryFloatExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryFloatExprMultiplyFloat>;

};
/*************************************************************************/
class BinaryFloatExprDivisionFloat : public BinaryFloatExpr {
public:
	virtual Float evaluateFloat(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		if(fRight == 0)
			IAS_THROW(InterpreterException("Division by zero."));
		return fLeft/fRight;
	};
protected:
	BinaryFloatExprDivisionFloat(Expr* pLeft, Expr* pRight):
		BinaryFloatExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryFloatExprDivisionFloat>;

};
/*************************************************************************/
class BinaryFloatExprModuloFloat : public BinaryFloatExpr {
public:
	virtual Float evaluateFloat(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		if(fRight == 0)
				IAS_THROW(InterpreterException("Division by zero."));
		return (int)fLeft%(int)fRight;
	};
protected:
	BinaryFloatExprModuloFloat(Expr* pLeft, Expr* pRight):
		BinaryFloatExpr(pLeft,pRight){}

	friend class::IAS::Factory<BinaryFloatExprModuloFloat>;
};
/*************************************************************************/
BinaryFloatExpr::BinaryFloatExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryFloatExpr::~BinaryFloatExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryFloatExpr* BinaryFloatExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryFloatExpr>::PtrHolder ptrBinaryFloatExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryFloatExpr = IAS_DFT_FACTORY<BinaryFloatExprAdditionFloat>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::SubtractionNode)){
		ptrBinaryFloatExpr = IAS_DFT_FACTORY<BinaryFloatExprSubtractionFloat>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::MultiplyNode)){
			ptrBinaryFloatExpr = IAS_DFT_FACTORY<BinaryFloatExprMultiplyFloat>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::DivisionNode)){
			ptrBinaryFloatExpr = IAS_DFT_FACTORY<BinaryFloatExprDivisionFloat>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::ModuloNode)){
			ptrBinaryFloatExpr = IAS_DFT_FACTORY<BinaryFloatExprModuloFloat>::Create(pLeft,pRight);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for a float argument."));
	}

	return ptrBinaryFloatExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
