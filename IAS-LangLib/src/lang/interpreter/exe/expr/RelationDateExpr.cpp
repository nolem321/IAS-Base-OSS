/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationDateExpr.cpp
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
#include "RelationDateExpr.h"
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
class RelationDateExprDiff : public RelationDateExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Date tLeft = ptrLeft->evaluateDate(pCtx);
		Date tRight = ptrRight->evaluateDate(pCtx);
		return tLeft != tRight;
	};

protected:
	RelationDateExprDiff(Expr* pLeft, Expr* pRight):
		RelationDateExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateExprDiff>;

};
/*************************************************************************/
class RelationDateExprEq : public RelationDateExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Date tLeft = ptrLeft->evaluateDate(pCtx);
		Date tRight = ptrRight->evaluateDate(pCtx);
		return tLeft == tRight;
	};

protected:
	RelationDateExprEq(Expr* pLeft, Expr* pRight):
		RelationDateExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateExprEq>;

};
/*************************************************************************/
class RelationDateExprEqGt : public RelationDateExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Date tLeft = ptrLeft->evaluateDate(pCtx);
		Date tRight = ptrRight->evaluateDate(pCtx);
		return tLeft <= tRight;
	};

protected:
	RelationDateExprEqGt(Expr* pLeft, Expr* pRight):
		RelationDateExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateExprEqGt>;

};
/*************************************************************************/
class RelationDateExprEqLess : public RelationDateExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Date tLeft = ptrLeft->evaluateDate(pCtx);
		Date tRight = ptrRight->evaluateDate(pCtx);
		return tLeft >= tRight;
	};

protected:
	RelationDateExprEqLess(Expr* pLeft, Expr* pRight):
		RelationDateExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateExprEqLess>;

};
/*************************************************************************/
class RelationDateExprGt : public RelationDateExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Date tLeft = ptrLeft->evaluateDate(pCtx);
		Date tRight = ptrRight->evaluateDate(pCtx);
		return tLeft > tRight;
	};

protected:
	RelationDateExprGt(Expr* pLeft, Expr* pRight):
		RelationDateExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateExprGt>;

};
/*************************************************************************/
class RelationDateExprLess : public RelationDateExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Date tLeft = ptrLeft->evaluateDate(pCtx);
		Date tRight = ptrRight->evaluateDate(pCtx);
		return tLeft < tRight;
	};

protected:
	RelationDateExprLess(Expr* pLeft, Expr* pRight):
		RelationDateExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateExprLess>;

};
/*************************************************************************/
RelationDateExpr::RelationDateExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationDateExpr::~RelationDateExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationDateExpr* RelationDateExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){

	IAS_TRACER;

	IAS_DFT_FACTORY<RelationDateExpr>::PtrHolder ptrRelationDateExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationDateExpr = IAS_DFT_FACTORY<RelationDateExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationDateExpr = IAS_DFT_FACTORY< RelationDateExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationDateExpr = IAS_DFT_FACTORY<RelationDateExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationDateExpr = IAS_DFT_FACTORY<RelationDateExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationDateExpr = IAS_DFT_FACTORY< RelationDateExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationDateExpr = IAS_DFT_FACTORY< RelationDateExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationDateExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
