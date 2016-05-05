/*
 * File: IAS-LangLib/src/lang/interpreter/proc/NodeHandler.cpp
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
#include "NodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {

/*************************************************************************/
NodeHandler::NodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
NodeHandler::~NodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void NodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result&      aResult){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
