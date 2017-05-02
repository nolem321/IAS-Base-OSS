/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Index.cpp
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
#include "Index.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "../Program.h"
#include "../ProgramContext.h"

#include "../expr/xpath/XPathExprFamily.h"
#include "../expr/xpath/XPathAccessor.h"
#include "Statement.h"
#include "LeftSide.h"
#include "../exception/NullObjectReferenceException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
Index::Index(Expr::XPath::XPathExprFamily  *pListExpr,
		     const String& strXPath):
		  ptrListExpr(pListExpr),
		  strXPath(strXPath){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(ptrListExpr);
}
/*************************************************************************/
Index::~Index() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void Index::execute(Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dmContext;

	DM::DataObjectList& lstArray(ptrListExpr->getTargetObjectList(pCtx));

	lstArray.hashWith(strXPath);

}
/*************************************************************************/
}
}
}
}
}
