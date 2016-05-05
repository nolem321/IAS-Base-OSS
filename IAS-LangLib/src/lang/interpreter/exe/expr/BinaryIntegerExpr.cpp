/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryIntegerExpr.cpp
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
#include "BinaryIntegerExpr.h"
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
class BinaryIntegerExprPlusInteger : public BinaryIntegerExpr {
public:
	virtual int evaluateInt(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		return iLeft+=iRight;
	};
protected:
	BinaryIntegerExprPlusInteger(Expr* pLeft, Expr* pRight):
		BinaryIntegerExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryIntegerExprPlusInteger>;

};
/*************************************************************************/
class BinaryIntegerExprMinusInteger : public BinaryIntegerExpr {
public:
	virtual int evaluateInt(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		return iLeft-=iRight;
	};
protected:
	BinaryIntegerExprMinusInteger(Expr* pLeft, Expr* pRight):
		BinaryIntegerExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryIntegerExprMinusInteger>;

};
/*************************************************************************/
class BinaryIntegerExprMultiplyInteger : public BinaryIntegerExpr {
public:
	virtual int evaluateInt(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		return iLeft*=iRight;
	};

protected:
	BinaryIntegerExprMultiplyInteger(Expr* pLeft, Expr* pRight):
		BinaryIntegerExpr(pLeft,pRight){}
	friend class ::IAS::Factory<BinaryIntegerExprMultiplyInteger>;
};
/*************************************************************************/
class BinaryIntegerExprDivisionInteger : public BinaryIntegerExpr {
public:
	virtual int evaluateInt(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		if(iRight == 0)
			IAS_THROW(InterpreterException("Division by zero."));
		return iLeft/=iRight;
	};
protected:
	BinaryIntegerExprDivisionInteger(Expr* pLeft, Expr* pRight):
		BinaryIntegerExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryIntegerExprDivisionInteger>;

};
/*************************************************************************/
class BinaryIntegerExprModuloInteger : public BinaryIntegerExpr {
public:
	virtual int evaluateInt(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		if(iRight == 0)
				IAS_THROW(InterpreterException("Division by zero."));
		return iLeft%=iRight;
	};
protected:
	BinaryIntegerExprModuloInteger(Expr* pLeft, Expr* pRight):
		BinaryIntegerExpr(pLeft,pRight){}

	friend class ::IAS::Factory<BinaryIntegerExprModuloInteger>;

};
/*************************************************************************/
BinaryIntegerExpr::BinaryIntegerExpr(Expr* pLeft, Expr* pRight):
		 BinaryExprFamily(pLeft,pRight){}
/*************************************************************************/
BinaryIntegerExpr::~BinaryIntegerExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BinaryIntegerExpr* BinaryIntegerExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<BinaryIntegerExpr>::PtrHolder ptrBinaryIntegerExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::AdditionNode)){
		ptrBinaryIntegerExpr = IAS_DFT_FACTORY<BinaryIntegerExprPlusInteger>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::SubtractionNode)){
		ptrBinaryIntegerExpr= IAS_DFT_FACTORY<BinaryIntegerExprMinusInteger>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::MultiplyNode)){
			ptrBinaryIntegerExpr = IAS_DFT_FACTORY<BinaryIntegerExprMultiplyInteger>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::DivisionNode)){
			ptrBinaryIntegerExpr = IAS_DFT_FACTORY<BinaryIntegerExprDivisionInteger>::Create(pLeft,pRight);
	}else if(aTypeInfoProxy == &typeid(Model::Expr::ModuloNode)){
			ptrBinaryIntegerExpr = IAS_DFT_FACTORY<BinaryIntegerExprModuloInteger>::Create(pLeft,pRight);
	}else{
		IAS_THROW(ScriptUsageException("Bad operator for an integer argument."));
	}

	return ptrBinaryIntegerExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
