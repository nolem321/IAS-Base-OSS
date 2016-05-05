/*
 * File: IAS-LangLib/src/lang/printer/expr/OperNodeHandler.cpp
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
#include "OperNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

namespace IAS {
namespace Lang {
namespace Printer {
namespace Expr {

/*************************************************************************/
OperNodeHandler::OperNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
OperNodeHandler::~OperNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void OperNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::OperNode, pNode);
	const Model::Expr::OperNode *pOperNode = IAS_DYNAMICCAST_CONST(Model::Expr::OperNode, pNode);

}
/*************************************************************************/
}
}
}
}
