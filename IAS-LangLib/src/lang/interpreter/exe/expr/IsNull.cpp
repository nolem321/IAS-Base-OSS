/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/IsNull.cpp
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
#include "IsNull.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "xpath/XPathAccessor.h"
#include "../Context.h"
#include "xpath/XPathExprFamily.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
IsNull::IsNull(const DM::DataFactory* pDataFactory, XPath::XPathExprFamily* pVarExpr):
		ptrVarExpr(pVarExpr){
	IAS_TRACER;
	setType(pDataFactory->getDefaultType(DM::Type::BooleanType));
}
/*************************************************************************/
IsNull::~IsNull() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool IsNull::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return ptrVarExpr->isNull(pCtx);
}
/*************************************************************************/
}
}
}
}
}
