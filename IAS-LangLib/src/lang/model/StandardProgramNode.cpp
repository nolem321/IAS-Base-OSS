/*
 * File: IAS-LangLib/src/lang/model/StandardProgramNode.cpp
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
#include "StandardProgramNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "stmt/StatementsListNode.h"
#include "dec/ParametersNode.h"

namespace IAS {
namespace Lang {
namespace Model {

using namespace Stmt;

/*************************************************************************/
StandardProgramNode::StandardProgramNode(Dec::QualifiedNameNode*        pQualifiedNameNode,
		  	  	  	  	  	  	  	  	 StatementsListNode*            pStatementListNode,
		  	  	  	  	  	  	  	  	 Dec::ParametersNode*           pParametersNode):
 ProgramNode(pQualifiedNameNode,pParametersNode,false){
IAS_TRACER;
	this->ptrStatementListNode=pStatementListNode;
}
/*************************************************************************/
StandardProgramNode::StandardProgramNode(Dec::QualifiedNameNode*        pQualifiedNameNode,
		  	  	  	  	  	  	  	  	 StatementsListNode*            pStatementListNode,
		  	  	  	  	  	  	  	  	 Dec::ParametersNode*           pParametersNode,
		  	  	  	  	  	  	  	  	 Dec::DeclarationNode*          pResultDeclartionNode):
ProgramNode(pQualifiedNameNode,pParametersNode,false){

	IAS_TRACER;

	this->ptrStatementListNode=pStatementListNode;
	addResultDeclarationNode(pResultDeclartionNode);
}
/*************************************************************************/
StandardProgramNode::~StandardProgramNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
