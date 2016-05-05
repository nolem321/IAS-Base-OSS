/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/xpath/XPathAccessNodeHandler.cpp
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
#include "XPathAccessNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../../CallbackRegister.h"
#include "../../exception/ProcessorException.h"

#include <lang/interpreter/exe/expr/Expr.h>

#include <lang/interpreter/exe/expr/xpath/XPathExprFamily.h>
#include <lang/interpreter/exe/expr/xpath/XPathAccessor.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathAccessNodeHandler::XPathAccessNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
XPathAccessNodeHandler::~XPathAccessNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XPathAccessNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::XPath::XPathAccessNode, pNode);
	const  Model::Expr::XPath::XPathAccessNode *pXPathAccessNode = IAS_DYNAMICCAST_CONST(Model::Expr::XPath::XPathAccessNode, pNode);

	CallbackSignature::Result aResultRoot;
	CallbackRegister::SubCall(pXPathAccessNode->getXPathRootNode(),pCtx,aResultRoot);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrRootExpr(aResultRoot.pExpr);


	CallbackSignature::Result aResultAccessor;
	CallbackRegister::SubCall(pXPathAccessNode->getXPathNode(),pCtx,aResultAccessor);
	IAS_DFT_FACTORY<Exe::Expr::XPath::XPathAccessor>::PtrHolder ptrAccessor(aResultAccessor.pXPathAccessor);

	if(!ptrRootExpr->getType()->isDataObjectType())
		IAS_THROW(ProcessorException(String("XPath access requires an data object type but found:")+ptrRootExpr->getType()->getName()));

	ptrAccessor->computeProperties(ptrRootExpr->getType()->asComplexType());

	aResult.pXPathExprFamily=Exe::Expr::XPath::XPathExprFamily::Create(ptrRootExpr.pass(), ptrAccessor.pass());

}
/*************************************************************************/
}
}
}
}
}
}
