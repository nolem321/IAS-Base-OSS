/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationBooleanExpr.cpp
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
#include "RelationBooleanExpr.h"
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
class RelationBooleanExprDiff : public RelationBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft!=bRight;
	};

protected:
	RelationBooleanExprDiff(Expr* pLeft, Expr* pRight):
		RelationBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationBooleanExprDiff>;

};
/*************************************************************************/
class RelationBooleanExprEq : public RelationBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft==bRight;
	};
protected:
	RelationBooleanExprEq(Expr* pLeft, Expr* pRight):
		RelationBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationBooleanExprEq>;

};
/*************************************************************************/
class RelationBooleanExprEqGt : public RelationBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft>=bRight;
	};

protected:
	RelationBooleanExprEqGt(Expr* pLeft, Expr* pRight):
		RelationBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationBooleanExprEqGt>;

};
/*************************************************************************/
class RelationBooleanExprEqLess : public RelationBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft<=bRight;
	};

protected:
	RelationBooleanExprEqLess(Expr* pLeft, Expr* pRight):
		RelationBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationBooleanExprEqLess>;

};
/*************************************************************************/
class RelationBooleanExprGt : public RelationBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft > bRight;
	};

protected:
	RelationBooleanExprGt(Expr* pLeft, Expr* pRight):
		RelationBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationBooleanExprGt>;

};
/*************************************************************************/
class RelationBooleanExprLess : public RelationBooleanExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		bool bLeft = ptrLeft->evaluateBoolean(pCtx);
		bool bRight = ptrRight->evaluateBoolean(pCtx);
		return bLeft < bRight;
	};

protected:
	RelationBooleanExprLess(Expr* pLeft, Expr* pRight):
		RelationBooleanExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationBooleanExprLess>;

};
/*************************************************************************/
RelationBooleanExpr::RelationBooleanExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationBooleanExpr::~RelationBooleanExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationBooleanExpr* RelationBooleanExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<RelationBooleanExpr>::PtrHolder ptrRelationBooleanExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationBooleanExpr = IAS_DFT_FACTORY<RelationBooleanExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationBooleanExpr = IAS_DFT_FACTORY<RelationBooleanExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationBooleanExpr =  IAS_DFT_FACTORY<RelationBooleanExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationBooleanExpr = IAS_DFT_FACTORY< RelationBooleanExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationBooleanExpr = IAS_DFT_FACTORY<RelationBooleanExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationBooleanExpr = IAS_DFT_FACTORY<RelationBooleanExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationBooleanExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
