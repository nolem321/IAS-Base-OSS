/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationDataObjectExpr.cpp
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
#include "RelationDataObjectExpr.h"
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
class RelationDataObjectExprDiff : public RelationDataObjectExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;

		DM::DataObjectPtr dmLeft;
		DM::DataObjectPtr dmRight;

		ptrLeft->evaluate(pCtx,dmLeft);
		ptrRight->evaluate(pCtx,dmRight);

		return ! dmLeft->equals(dmRight);
	};

protected:
	RelationDataObjectExprDiff(Expr* pLeft, Expr* pRight):
		RelationDataObjectExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDataObjectExprDiff>;

};
/*************************************************************************/
class RelationDataObjectExprEq : public RelationDataObjectExpr {
public:
	virtual bool evaluateBoolean(Context *pCtx) const{
		IAS_TRACER;
		DM::DataObjectPtr dmLeft;
		DM::DataObjectPtr dmRight;

		ptrLeft->evaluate(pCtx,dmLeft);
		ptrRight->evaluate(pCtx,dmRight);

		return dmLeft->equals(dmRight);
	};

protected:
	RelationDataObjectExprEq(Expr* pLeft, Expr* pRight):
		RelationDataObjectExpr(pLeft,pRight){};

	friend class ::IAS::Factory<RelationDataObjectExprEq>;

};
/*************************************************************************/
RelationDataObjectExpr::RelationDataObjectExpr(Expr* pLeft, Expr* pRight):
	RelationFamily(pLeft,pRight){
	IAS_TRACER;
}
/*************************************************************************/
RelationDataObjectExpr::~RelationDataObjectExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
RelationDataObjectExpr* RelationDataObjectExpr::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){

	IAS_TRACER;

	IAS_DFT_FACTORY<RelationDataObjectExpr>::PtrHolder ptrRelationDataObjectExpr;

	if(aTypeInfoProxy == &typeid(Model::Expr::RelationalEqNode)){
		ptrRelationDataObjectExpr = IAS_DFT_FACTORY<RelationDataObjectExprEq>::Create(pLeft,pRight);

	}else if(aTypeInfoProxy == &typeid(Model::Expr::RelationalDiffNode)){
			ptrRelationDataObjectExpr = IAS_DFT_FACTORY< RelationDataObjectExprDiff>::Create(pLeft,pRight);

	}else{
		IAS_THROW(InternalException("No operator for this node."));
	}

	return ptrRelationDataObjectExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
