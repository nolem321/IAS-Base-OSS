/*
 * File: IAS-LangLib/src/lang/model/stmt/CatchListNode.cpp
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
#include "CatchListNode.h"
#include<lang/log/LogLevel.h>
#include "CatchNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt {

/*************************************************************************/
CatchListNode::CatchListNode(){
	IAS_TRACER;
}
/*************************************************************************/
CatchListNode::~CatchListNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CatchListNode::addCatchNode(CatchNode* pCatch){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pCatch);
	phcCatchNodes.addPointer(pCatch);
	lstCatchNodes.push_back(pCatch);
}
/*************************************************************************/
const CatchListNode::CatchNodesList& CatchListNode::getCatchNodesList()const {
	IAS_TRACER;
	return lstCatchNodes;
}
/*************************************************************************/
}
}
}
}
