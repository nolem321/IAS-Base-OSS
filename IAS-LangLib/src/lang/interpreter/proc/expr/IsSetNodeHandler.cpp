/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/IsSetNodeHandler.cpp
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
#include "IsSetNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/IsSet.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
IsSetNodeHandler::IsSetNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
IsSetNodeHandler::~IsSetNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void IsSetNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::IsSetNode, pNode);
	const  Model::Expr::IsSetNode *pIsSetNode = IAS_DYNAMICCAST_CONST(Model::Expr::IsSetNode, pNode);

	CallbackSignature::Result aResultTmp;
	CallbackRegister::SubCall(pIsSetNode->getXPathAccessNode(),pCtx,aResultTmp);

	aResult.pBooleanExpr=
		IAS_DFT_FACTORY<Exe::Expr::IsSet>::Create(pCtx->getDataFactory(),aResultTmp.pXPathExprFamily);

}
/*************************************************************************/
}
}
}
}
}
