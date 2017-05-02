/*
 * File: IAS-LangLib/src/lang/interpreter/text/expr/xpath/XPathNodeHandler.cpp
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
#include "XPathNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../../CallbackRegister.h"
#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/xpath/XPathAccessor.h>

namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
namespace Expr {
namespace XPath {


/*************************************************************************/
XPathNodeHandler::XPathNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
XPathNodeHandler::~XPathNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XPathNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::XPath::XPathNode, pNode);
	const Model::Expr::XPath::XPathNode *pXPathNode = IAS_DYNAMICCAST_CONST(Model::Expr::XPath::XPathNode, pNode);

	const Model::Expr::XPath::XPathNode::ElementList& lstElements = pXPathNode->getElements();

	for(Model::Expr::XPath::XPathNode::ElementList::const_iterator it=lstElements.begin();
		it != lstElements.end();
		it++){

		if(it != lstElements.begin())
			aResult.ssOutput<<".";

		aResult.ssOutput<<(*it)->getName();

		if((*it)->isMulti()){
			aResult.ssOutput<<"[";
			if((*it)->isHashIndex())
				aResult.ssOutput<<"[";

			CallbackRegister::SubCall((*it)->getMultiExpr(),pCtx,aResult);
			aResult.ssOutput<<"]";

			if((*it)->isHashIndex())
				aResult.ssOutput<<"]";
		}
	};


}
/*************************************************************************/
}
}
}
}
}
}
