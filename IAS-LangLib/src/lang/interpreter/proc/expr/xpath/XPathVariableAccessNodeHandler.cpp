/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/xpath/XPathVariableAccessNodeHandler.cpp
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
#include "XPathVariableAccessNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/xpath/BlockVariablesDataObjectExpr.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {
namespace XPath {


/*************************************************************************/
XPathVariableAccessNodeHandler::XPathVariableAccessNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
XPathVariableAccessNodeHandler::~XPathVariableAccessNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XPathVariableAccessNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::XPath::XPathVariableAccessNode, pNode);
	const  Model::Expr::XPath::XPathVariableAccessNode *pXPathVariableAccessNode = IAS_DYNAMICCAST_CONST(Model::Expr::XPath::XPathVariableAccessNode, pNode);

	String strName = pXPathVariableAccessNode->getName();

	int iOffset;
	const DM::Property* pProperty;
	const DM::ComplexType* pComplexType;

	//TODO (L) do we need to pass pProperty & Complex type * ? remove dynamic cast - redefine api findVariable

	pCtx->getBlockChain()->findVariable(strName,iOffset,pProperty,pComplexType);

	aResult.pExpr=IAS_DFT_FACTORY<Exe::Expr::XPath::BlockVariablesDataObjectExpr>::Create(iOffset,
			dynamic_cast<const DM::Type*>(pComplexType));

}
/*************************************************************************/
}
}
}
}
}
}
