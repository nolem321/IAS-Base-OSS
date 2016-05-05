/*
 * File: IAS-LangLib/src/lang/interpreter/proc/dec/ResultDeclarationNodeHandler.cpp
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
#include "ResultDeclarationNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

#include <lang/interpreter/exe/dec/VariableDeclaration.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {
namespace Dec {

/*************************************************************************/
ResultDeclarationNodeHandler::ResultDeclarationNodeHandler(){}
/*************************************************************************/
ResultDeclarationNodeHandler::~ResultDeclarationNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ResultDeclarationNodeHandler::call(const Model::Node* pNode,
									  CallbackCtx *pCtx,
									  CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Dec::ResultDeclarationNode, pNode);
	const Model::Dec::ResultDeclarationNode *pDeclarationNode = IAS_DYNAMICCAST_CONST(Model::Dec::ResultDeclarationNode, pNode);

	handle(pDeclarationNode,pCtx,aResult);
}

/*************************************************************************/
}
}
}
}
}
