/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/SizeOfNodeHandler.cpp
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
#include "SizeOfNodeHandler.h"
#include "../exception/ProcessorException.h"

#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/SizeOf.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
SizeOfNodeHandler::SizeOfNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
SizeOfNodeHandler::~SizeOfNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SizeOfNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::SizeOfNode, pNode);
	const  Model::Expr::SizeOfNode *pSizeOfNode = IAS_DYNAMICCAST_CONST(Model::Expr::SizeOfNode, pNode);


	CallbackSignature::Result aResultTmp;
	CallbackRegister::SubCall(pSizeOfNode->getXPathAccessNode(),pCtx,aResultTmp);

	aResult.pExpr=
		IAS_DFT_FACTORY<Exe::Expr::SizeOf>::Create(pCtx->getDataFactory(),aResultTmp.pXPathExprFamily);

}
/*************************************************************************/
}
}
}
}
}
