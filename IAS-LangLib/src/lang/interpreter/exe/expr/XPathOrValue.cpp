/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/XPathOrValue.cpp
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
#include "XPathOrValue.h"
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
XPathOrValue::XPathOrValue(const DM::DataFactory* pDataFactory,
					 XPath::XPathExprFamily* pVarExpr,
					 Expr* pDefault):
		ptrVarExpr(pVarExpr),
		ptrDefault(pDefault){
	IAS_TRACER;

	setType(ptrVarExpr->getType());

}
/*************************************************************************/
XPathOrValue::~XPathOrValue() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XPathOrValue::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{
	IAS_TRACER;


  if(ptrVarExpr->isSet(pCtx) && !ptrVarExpr->isNull(pCtx)){
  	ptrVarExpr->evaluate(pCtx,refResult);
  }else{
		ptrDefault->evaluate(pCtx,refResult);
  }
}
/*************************************************************************/
}
}
}
}
}
