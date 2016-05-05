/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationFloatExpr.cpp
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
#include "RelationFloatExpr.h"
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
class RelationFloatExprDiff : public RelationFloatExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft!=fRight;
	};

protected:
	RelationFloatExprDiff(Expr* pLeft, Expr* pRight):
		RelationFloatExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationFloatExprDiff>;

};
/*************************************************************************/
class RelationFloatExprEq : public RelationFloatExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft==fRight;
	};

protected:
	RelationFloatExprEq(Expr* pLeft, Expr* pRight):
		RelationFloatExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationFloatExprEq>;

};
/*************************************************************************/
class RelationFloatExprEqGt : public RelationFloatExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft>=fRight;
	};

protected:
	RelationFloatExprEqGt(Expr* pLeft, Expr* pRight):
		RelationFloatExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationFloatExprEqGt>;

};
/*************************************************************************/
class RelationFloatExprEqLess : public RelationFloatExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft<=fRight;
	};

protected:
	RelationFloatExprEqLess(Expr* pLeft, Expr* pRight):
		RelationFloatExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationFloatExprEqLess>;

};
/*************************************************************************/
class RelationFloatExprGt : public RelationFloatExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft > fRight;
	};

protected:
	RelationFloatExprGt(Expr* pLeft, Expr* pRight):
		RelationFloatExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationFloatExprGt>;

};
/*************************************************************************/
class RelationFloatExprLess : public RelationFloatExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Float fLeft = ptrLeft->evaluateFloat(pCtx);
		Float fRight = ptrRight->evaluateFloat(pCtx);
		return fLeft < fRight;
	};

protected:
	RelationFloatExprLess(Expr* pLeft, Expr* pRight):
		RelationFloatExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationFloatExprLess>;

};
/*************************************************************************/
RelationFloatExpr::RelationFloatExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationFloatExpr::~RelationFloatExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationFloatExpr* RelationFloatExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<RelationFloatExpr>::PtrHolder ptrRelationFloatExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationFloatExpr = IAS_DFT_FACTORY<RelationFloatExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationFloatExpr = IAS_DFT_FACTORY< RelationFloatExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationFloatExpr = IAS_DFT_FACTORY<RelationFloatExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationFloatExpr = IAS_DFT_FACTORY<RelationFloatExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationFloatExpr = IAS_DFT_FACTORY<RelationFloatExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationFloatExpr = IAS_DFT_FACTORY<RelationFloatExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationFloatExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
