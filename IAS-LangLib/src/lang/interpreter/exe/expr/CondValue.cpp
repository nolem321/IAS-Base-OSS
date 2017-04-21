/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/CondValue.cpp
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
#include "CondValue.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "xpath/XPathAccessor.h"
#include "../Context.h"
#include "xpath/XPathExprFamily.h"
#include "BooleanExpr.h"
#include <lang/exception/ScriptUsageException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
CondValue::CondValue(const DM::DataFactory* pDataFactory,
						 BooleanExpr      *pCondition,
					     Expr* pExprTrue,
						 Expr* pExprFalse):
		ptrCondition(pCondition),
		ptrExprTrue(pExprTrue),
		ptrExprFalse(pExprFalse){
	IAS_TRACER;

	setType(ptrExprTrue->getType());

}
/*************************************************************************/
CondValue::~CondValue() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CondValue::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{
	IAS_TRACER;
	if(ptrCondition->evaluateBoolean(pCtx))
		ptrExprTrue->evaluate(pCtx,refResult);
	else
		ptrExprFalse->evaluate(pCtx,refResult);
}
/*************************************************************************/
}
}
}
}
}
