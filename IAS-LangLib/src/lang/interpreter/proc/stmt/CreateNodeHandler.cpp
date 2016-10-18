/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/CreateNodeHandler.cpp
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
#include "CreateNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../../exe/stmt/CreateWithStatement.h"
#include "../CallbackRegister.h"

#include "lang/interpreter/exe/expr/Expr.h"
#include "lang/interpreter/exe/stmt/Create.h"
#include "lang/interpreter/exe/expr/xpath/XPathAccessor.h"
#include "lang/interpreter/exe/expr/xpath/XPathExprFamily.h"

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
CreateNodeHandler::CreateNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
CreateNodeHandler::~CreateNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CreateNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::CreateNode, pNode);
	const Model::Stmt::CreateNode *pCreateNode = IAS_DYNAMICCAST_CONST(Model::Stmt::CreateNode, pNode);

	CallbackSignature::Result aResultTmp;
	CallbackRegister::SubCall(pCreateNode->getXPathAccessNode(),pCtx,aResultTmp);

	IAS_DFT_FACTORY<Exe::Stmt::Create>::PtrHolder ptrStatement;

	if(!pCreateNode->hasStatement()){

		ptrStatement = IAS_DFT_FACTORY<Exe::Stmt::Create>::Create(aResultTmp.pXPathExprFamily);

	}else{

		Exe::Stmt::CreateWithStatement* pCreateWithStatement;

		ptrStatement = pCreateWithStatement = IAS_DFT_FACTORY<Exe::Stmt::CreateWithStatement>::Create(aResultTmp.pXPathExprFamily);

		BlockChain::AutoPopUp autoPopUp(pCtx->getBlockChain(), pCreateWithStatement);
		pCreateWithStatement->declareBlockVariables(pCtx->getDataFactory());

		CallbackRegister::SubCall(pCreateNode->getStatementNode(),pCtx,aResultTmp);
		pCreateWithStatement->setStatement(aResultTmp.pStatement);
	}


	aResult.pStatement= ptrStatement.pass();

	aResult.pStatement->setSourceLine(pCreateNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
}
}
}
}
}
