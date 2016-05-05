/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationDateTimeExpr.cpp
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
#include "RelationDateTimeExpr.h"
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
class RelationDateTimeExprDiff : public RelationDateTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		DateTime tLeft = ptrLeft->evaluateDateTime(pCtx);
		DateTime tRight = ptrRight->evaluateDateTime(pCtx);
		return tLeft != tRight;
	};

protected:
	RelationDateTimeExprDiff(Expr* pLeft, Expr* pRight):
		RelationDateTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateTimeExprDiff>;

};
/*************************************************************************/
class RelationDateTimeExprEq : public RelationDateTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		DateTime tLeft = ptrLeft->evaluateDateTime(pCtx);
		DateTime tRight = ptrRight->evaluateDateTime(pCtx);
		return tLeft == tRight;
	};

protected:
	RelationDateTimeExprEq(Expr* pLeft, Expr* pRight):
		RelationDateTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateTimeExprEq>;

};
/*************************************************************************/
class RelationDateTimeExprEqGt : public RelationDateTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		DateTime tLeft = ptrLeft->evaluateDateTime(pCtx);
		DateTime tRight = ptrRight->evaluateDateTime(pCtx);
		return tLeft <= tRight;
	};

protected:
	RelationDateTimeExprEqGt(Expr* pLeft, Expr* pRight):
		RelationDateTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateTimeExprEqGt>;

};
/*************************************************************************/
class RelationDateTimeExprEqLess : public RelationDateTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		DateTime tLeft = ptrLeft->evaluateDateTime(pCtx);
		DateTime tRight = ptrRight->evaluateDateTime(pCtx);
		return tLeft >= tRight;
	};

protected:
	RelationDateTimeExprEqLess(Expr* pLeft, Expr* pRight):
		RelationDateTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateTimeExprEqLess>;

};
/*************************************************************************/
class RelationDateTimeExprGt : public RelationDateTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		DateTime tLeft = ptrLeft->evaluateDateTime(pCtx);
		DateTime tRight = ptrRight->evaluateDateTime(pCtx);
		return tLeft > tRight;
	};

protected:
	RelationDateTimeExprGt(Expr* pLeft, Expr* pRight):
		RelationDateTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateTimeExprGt>;

};
/*************************************************************************/
class RelationDateTimeExprLess : public RelationDateTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		DateTime tLeft = ptrLeft->evaluateDateTime(pCtx);
		DateTime tRight = ptrRight->evaluateDateTime(pCtx);
		return tLeft < tRight;
	};

protected:
	RelationDateTimeExprLess(Expr* pLeft, Expr* pRight):
		RelationDateTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDateTimeExprLess>;

};
/*************************************************************************/
RelationDateTimeExpr::RelationDateTimeExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationDateTimeExpr::~RelationDateTimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationDateTimeExpr* RelationDateTimeExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){

	IAS_TRACER;

	IAS_DFT_FACTORY<RelationDateTimeExpr>::PtrHolder ptrRelationDateTimeExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationDateTimeExpr = IAS_DFT_FACTORY<RelationDateTimeExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationDateTimeExpr = IAS_DFT_FACTORY< RelationDateTimeExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationDateTimeExpr = IAS_DFT_FACTORY<RelationDateTimeExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationDateTimeExpr = IAS_DFT_FACTORY<RelationDateTimeExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationDateTimeExpr = IAS_DFT_FACTORY< RelationDateTimeExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationDateTimeExpr = IAS_DFT_FACTORY< RelationDateTimeExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationDateTimeExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
