/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/IndexNodeHandler.cpp
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
#include "IndexNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"
#include "../ExecStore.h"

#include <lang/interpreter/TypeList.h>

#include <lang/interpreter/exe/allexe.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/expr/xpath/XPathExprFamily.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
IndexNodeHandler::IndexNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
IndexNodeHandler::~IndexNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void IndexNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::IndexNode, pNode);
	const Model::Stmt::IndexNode *pIndexNode = IAS_DYNAMICCAST_CONST(Model::Stmt::IndexNode, pNode);

	const Model::Expr::XPath::XPathAccessNode   *pListXPathAccessNode   = pIndexNode->getListXPathAccessNode();
	const Model::Expr::XPath::XPathAccessNode   *pIndexXPathAccessNode  = pIndexNode->getIndexXPathAccessNode();

	IAS_DFT_FACTORY<Exe::Expr::XPath::XPathExprFamily>::PtrHolder ptrListExpr(createVarExpr(pCtx,pListXPathAccessNode));

	aResult.pStatement = IAS_DFT_FACTORY<Exe::Stmt::Index>::Create(ptrListExpr.pass(), computeXPath(pIndexXPathAccessNode));

	aResult.pStatement->setSourceLine(pIndexNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
Exe::Expr::XPath::XPathExprFamily* IndexNodeHandler::createVarExpr(CallbackCtx *pCtx,
		const Model::Expr::XPath::XPathAccessNode *pXPathAccessNode) {


	CallbackSignature::Result aResultTmp;
	CallbackRegister::SubCall(pXPathAccessNode, pCtx, aResultTmp);

	return aResultTmp.pXPathExprFamily;
}
/*************************************************************************/
String IndexNodeHandler::computeXPath(const Model::Expr::XPath::XPathAccessNode  *pXListAccessNode)const {

   StringStream ssXPath;

	const Model::Expr::XPath::XPathNode::ElementList& lstElements(pXListAccessNode->getXPathNode()->getElements());

	bool bFirst = true;

	for(Model::Expr::XPath::XPathNode::ElementList::const_iterator it = lstElements.begin();
			it != lstElements.end(); it++){

		if(!bFirst)
			ssXPath<<"/";

		ssXPath<<(*it)->getName();

		if((*it)->isMulti())
			IAS_THROW(BadUsageException("Arrays are not allowed in the index key expression."))

		bFirst = false;
	}

   return ssXPath.str();
}
/*************************************************************************/
}
}
}
}
}
