/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationIntegerExpr.cpp
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
#include "RelationIntegerExpr.h"
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
class RelationIntegerExprDiff : public virtual RelationIntegerExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		return iLeft!=iRight;
	};

protected:
	RelationIntegerExprDiff(Expr* pLeft, Expr* pRight):
		RelationIntegerExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationIntegerExprDiff>;

};
/*************************************************************************/
class RelationIntegerExprEq : public virtual RelationIntegerExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		return iLeft==iRight;
	};

protected:
	RelationIntegerExprEq(Expr* pLeft, Expr* pRight):
		RelationIntegerExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationIntegerExprEq>;

};
/*************************************************************************/
class RelationIntegerExprEqGt : public virtual RelationIntegerExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),iLeft << " ? " <<iRight);
		return iLeft>=iRight;
	};

protected:
	RelationIntegerExprEqGt(Expr* pLeft, Expr* pRight):
		RelationIntegerExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationIntegerExprEqGt>;

};
/*************************************************************************/
class RelationIntegerExprEqLess : public virtual RelationIntegerExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),iLeft << " ? " <<iRight);
		return iLeft<=iRight;
	};

protected:
	RelationIntegerExprEqLess(Expr* pLeft, Expr* pRight):
		RelationIntegerExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationIntegerExprEqLess>;

};
/*************************************************************************/
class RelationIntegerExprGt : public virtual RelationIntegerExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		return iLeft > iRight;
	};

protected:
	RelationIntegerExprGt(Expr* pLeft, Expr* pRight):
		RelationIntegerExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationIntegerExprGt>;

};
/*************************************************************************/
class RelationIntegerExprLess : public virtual RelationIntegerExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		int iLeft = ptrLeft->evaluateInt(pCtx);
		int iRight = ptrRight->evaluateInt(pCtx);
		return iLeft < iRight;
	};

protected:
	RelationIntegerExprLess(Expr* pLeft, Expr* pRight):
		RelationIntegerExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationIntegerExprLess>;

};
/*************************************************************************/
RelationIntegerExpr::RelationIntegerExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationIntegerExpr::~RelationIntegerExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationIntegerExpr* RelationIntegerExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;
	IAS_DFT_FACTORY<RelationIntegerExpr>::PtrHolder ptrRelationIntegerExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationIntegerExpr = IAS_DFT_FACTORY<RelationIntegerExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationIntegerExpr = IAS_DFT_FACTORY<RelationIntegerExprDiff>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqGtNode)){
			ptrRelationIntegerExpr = IAS_DFT_FACTORY<RelationIntegerExprEqGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqLessNode)){
			ptrRelationIntegerExpr = IAS_DFT_FACTORY<RelationIntegerExprEqLess>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalGtNode)){
			ptrRelationIntegerExpr = IAS_DFT_FACTORY<RelationIntegerExprGt>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalLessNode)){
				ptrRelationIntegerExpr = IAS_DFT_FACTORY<RelationIntegerExprLess>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationIntegerExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
