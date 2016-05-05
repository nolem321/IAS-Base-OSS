/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationTimeExpr.cpp
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
#include "RelationTimeExpr.h"
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
class RelationTimeExprDiff : public RelationTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Time tLeft = ptrLeft->evaluateTime(pCtx);
		Time tRight = ptrRight->evaluateTime(pCtx);
		return tLeft != tRight;
	};

protected:
	RelationTimeExprDiff(Expr* pLeft, Expr* pRight):
		RelationTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationTimeExprDiff>;

};
/*************************************************************************/
class RelationTimeExprEq : public RelationTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Time tLeft = ptrLeft->evaluateTime(pCtx);
		Time tRight = ptrRight->evaluateTime(pCtx);
		return tLeft == tRight;
	};

protected:
	RelationTimeExprEq(Expr* pLeft, Expr* pRight):
		RelationTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationTimeExprEq>;

};
/*************************************************************************/
class RelationTimeExprEqGt : public RelationTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Time tLeft = ptrLeft->evaluateTime(pCtx);
		Time tRight = ptrRight->evaluateTime(pCtx);
		return tLeft <= tRight;
	};

protected:
	RelationTimeExprEqGt(Expr* pLeft, Expr* pRight):
		RelationTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationTimeExprEqGt>;

};
/*************************************************************************/
class RelationTimeExprEqLess : public RelationTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Time tLeft = ptrLeft->evaluateTime(pCtx);
		Time tRight = ptrRight->evaluateTime(pCtx);
		return tLeft >= tRight;
	};

protected:
	RelationTimeExprEqLess(Expr* pLeft, Expr* pRight):
		RelationTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationTimeExprEqLess>;

};
/*************************************************************************/
class RelationTimeExprGt : public RelationTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Time tLeft = ptrLeft->evaluateTime(pCtx);
		Time tRight = ptrRight->evaluateTime(pCtx);
		return tLeft > tRight;
	};

protected:
	RelationTimeExprGt(Expr* pLeft, Expr* pRight):
		RelationTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationTimeExprGt>;

};
/*************************************************************************/
class RelationTimeExprLess : public RelationTimeExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		Time tLeft = ptrLeft->evaluateTime(pCtx);
		Time tRight = ptrRight->evaluateTime(pCtx);
		return tLeft < tRight;
	};

protected:
	RelationTimeExprLess(Expr* pLeft, Expr* pRight):
		RelationTimeExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationTimeExprLess>;

};
/*************************************************************************/
RelationTimeExpr::RelationTimeExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationTimeExpr::~RelationTimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationTimeExpr* RelationTimeExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){

	IAS_TRACER;

	IAS_DFT_FACTORY<RelationTimeExpr>::PtrHolder ptrRelationTimeExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationTimeExpr = IAS_DFT_FACTORY<RelationTimeExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationTimeExpr = IAS_DFT_FACTORY< RelationTimeExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationTimeExpr = IAS_DFT_FACTORY<RelationTimeExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationTimeExpr = IAS_DFT_FACTORY<RelationTimeExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationTimeExpr = IAS_DFT_FACTORY< RelationTimeExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationTimeExpr = IAS_DFT_FACTORY< RelationTimeExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationTimeExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
