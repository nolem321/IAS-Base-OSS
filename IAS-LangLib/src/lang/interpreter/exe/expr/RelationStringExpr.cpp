/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationStringExpr.cpp
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
#include "RelationStringExpr.h"
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
class RelationStringExprDiff : public RelationStringExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		String strLeft = ptrLeft->evaluateString(pCtx);
		String strRight = ptrRight->evaluateString(pCtx);
		return strLeft.compare(strRight) != 0;
	};

protected:
	RelationStringExprDiff(Expr* pLeft, Expr* pRight):
		RelationStringExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationStringExprDiff>;

};
/*************************************************************************/
class RelationStringExprEq : public RelationStringExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		String strLeft = ptrLeft->evaluateString(pCtx);
		String strRight = ptrRight->evaluateString(pCtx);
		return strLeft.compare(strRight) == 0;
	};

protected:
	RelationStringExprEq(Expr* pLeft, Expr* pRight):
		RelationStringExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationStringExprEq>;

};
/*************************************************************************/
class RelationStringExprEqGt : public RelationStringExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		String strLeft = ptrLeft->evaluateString(pCtx);
		String strRight = ptrRight->evaluateString(pCtx);
		return strLeft.compare(strRight) >= 0;
	};

protected:
	RelationStringExprEqGt(Expr* pLeft, Expr* pRight):
		RelationStringExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationStringExprEqGt>;

};
/*************************************************************************/
class RelationStringExprEqLess : public RelationStringExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		String strLeft = ptrLeft->evaluateString(pCtx);
		String strRight = ptrRight->evaluateString(pCtx);
		return strLeft.compare(strRight) <= 0;
	};

protected:
	RelationStringExprEqLess(Expr* pLeft, Expr* pRight):
		RelationStringExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationStringExprEqLess>;

};
/*************************************************************************/
class RelationStringExprGt : public RelationStringExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		String strLeft = ptrLeft->evaluateString(pCtx);
		String strRight = ptrRight->evaluateString(pCtx);
		return strLeft.compare(strRight) > 0;
	};

protected:
	RelationStringExprGt(Expr* pLeft, Expr* pRight):
		RelationStringExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationStringExprGt>;

};
/*************************************************************************/
class RelationStringExprLess : public RelationStringExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		String strLeft = ptrLeft->evaluateString(pCtx);
		String strRight = ptrRight->evaluateString(pCtx);
		return strLeft.compare(strRight) < 0;
	};

protected:
	RelationStringExprLess(Expr* pLeft, Expr* pRight):
		RelationStringExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationStringExprLess>;

};
/*************************************************************************/
RelationStringExpr::RelationStringExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationStringExpr::~RelationStringExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationStringExpr* RelationStringExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){

	IAS_TRACER;

	IAS_DFT_FACTORY<RelationStringExpr>::PtrHolder ptrRelationStringExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationStringExpr = IAS_DFT_FACTORY<RelationStringExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationStringExpr = IAS_DFT_FACTORY< RelationStringExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationStringExpr = IAS_DFT_FACTORY<RelationStringExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationStringExpr = IAS_DFT_FACTORY<RelationStringExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationStringExpr = IAS_DFT_FACTORY< RelationStringExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationStringExpr = IAS_DFT_FACTORY< RelationStringExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationStringExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
