/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/SortNodeHandler.cpp
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
#include "SortNodeHandler.h"
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
SortNodeHandler::SortNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
SortNodeHandler::~SortNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SortNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::SortNode, pNode);
	const Model::Stmt::SortNode *pSortNode = IAS_DYNAMICCAST_CONST(Model::Stmt::SortNode, pNode);

	const Model::Expr::XPath::XPathAccessNode   *pListXPathAccessNode    = pSortNode->getListXPathAccessNode();
	const Model::Dec::QualifiedNameNode         *pQualifiedNameNode      = pSortNode->getQualifiedNameNode();

	bool bReverse = pSortNode->isDescending();

	IAS_DFT_FACTORY<Exe::Expr::XPath::XPathExprFamily>::PtrHolder ptrListExpr(createVarExpr(pCtx,pListXPathAccessNode));

	Exe::Program *pProgram = NULL;


	Interpreter::TypeList lstSignatureTypes;

	lstSignatureTypes.append(ptrListExpr->getType());
	lstSignatureTypes.append(ptrListExpr->getType());

	pProgram = pCtx->getExecStore()->getExecutable(pQualifiedNameNode->getQualifiedName(),
																     lstSignatureTypes);

	if(!pProgram->getParameters()->hasResult() ||
		pProgram->getParameters()->getResultProperty()->getType()->getTypeEnum() != DM::Type::BooleanType)
		IAS_THROW(BadUsageException("Sort function must return a boolean result."));


	aResult.pStatement = IAS_DFT_FACTORY<Exe::Stmt::Sort>::Create(ptrListExpr.pass(), pProgram, bReverse);

	aResult.pStatement->setSourceLine(pSortNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
Exe::Expr::XPath::XPathExprFamily* SortNodeHandler::createVarExpr(CallbackCtx *pCtx,
		const Model::Expr::XPath::XPathAccessNode *pXPathAccessNode) {


	CallbackSignature::Result aResultTmp;
	CallbackRegister::SubCall(pXPathAccessNode, pCtx, aResultTmp);

	return aResultTmp.pXPathExprFamily;
}
/*************************************************************************/
}
}
}
}
}
