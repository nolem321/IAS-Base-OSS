/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/GetTypeNSExpr.cpp
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
#include "GetTypeNSExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
GetTypeNSExpr::GetTypeNSExpr(const DM::DataFactory* pDataFactory, Expr* pExpr){
	IAS_TRACER;
	ptrExpr=pExpr;
	setType(pDataFactory->getDefaultType(DM::Type::TextType));
}

/*************************************************************************/
GetTypeNSExpr::~GetTypeNSExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String GetTypeNSExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dmResult;

	ptrExpr->evaluate(pCtx,dmResult);

	return dmResult->getType()->getURI();
}
/*************************************************************************/
}
}
}
}
}
