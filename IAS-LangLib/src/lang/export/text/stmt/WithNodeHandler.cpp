/*
 * File: IAS-LangLib/src/lang/export/text/stmt/WithNodeHandler.cpp
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
#include "WithNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
namespace Stmt {

/*************************************************************************/
WithNodeHandler::WithNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
WithNodeHandler::~WithNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void WithNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::WithNode, pNode);
	const Model::Stmt::WithNode *pWithNode = IAS_DYNAMICCAST_CONST(Model::Stmt::WithNode, pNode);

	const Model::Expr::XPath::XPathAccessNode   *pXPathAccessNode = pWithNode->getVariableExpr();
	const Model::Stmt::StatementNode            *pStatementNode  = pWithNode->getStatementNode();


	printKeyword(aResult,"WITH");

	if(pWithNode->hasVariable()){
		aResult.ssOutput<<" "<<pWithNode->getVariable()<<" ";
		printKeyword(aResult,"AS");
	}
  aResult.ssOutput<<" ";
	CallbackRegister::SubCall(pXPathAccessNode,pCtx,aResult);
  aResult.ssOutput<<" ";
	printKeyword(aResult,"DO");
  aResult.ssOutput<<std::endl;
	pCtx->iIndent++;
	printIndent(pCtx,aResult);
	CallbackRegister::SubCall(pStatementNode,pCtx,aResult);
	pCtx->iIndent--;

}
/*************************************************************************/
}
}
}
}
}
