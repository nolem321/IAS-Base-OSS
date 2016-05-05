/*
 * File: IAS-LangLib/src/lang/model/stmt/StatementsListNode.cpp
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
#include "StatementsListNode.h"
#include<lang/log/LogLevel.h>
#include "StatementNode.h"

#include "../dec/DeclarationNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt {


/*************************************************************************/
StatementsListNode::StatementsListNode(){
	IAS_TRACER;
}

/*************************************************************************/
StatementsListNode::~StatementsListNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementsListNode::addStatement(StatementNode* pStatement){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pStatement);
	phcStatements.addPointer(pStatement);
	lstStatements.push_back(pStatement);
}
/*************************************************************************/
const StatementsListNode::StatementNodesList& StatementsListNode::getStatementsListAsConst() const{
	IAS_TRACER;
	return lstStatements;
}
/*************************************************************************/
const StatementsListNode::StatementNodesList& StatementsListNode::getStatementsList()const {
	IAS_TRACER;
	return lstStatements;
}
/*************************************************************************/
}
}
}
}
