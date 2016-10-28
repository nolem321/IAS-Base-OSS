/*
 * File: IAS-LangLib/src/lang/model/ProgramNode.cpp
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
#include "ProgramNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "dec/ParametersNode.h"
#include "dec/QualifiedNameNode.h"

namespace IAS {
namespace Lang {
namespace Model {

/*************************************************************************/
ProgramNode::ProgramNode(Dec::QualifiedNameNode*   pQualifiedNameNode,
						 Dec::ParametersNode*      pParametersNode,
						 bool bIsExternal):
		   	      bIsReturningResult(false),
				  bIsExternal(bIsExternal){
IAS_TRACER;
this->ptrQualifiedNameNode=pQualifiedNameNode;
this->ptrParametersNode=pParametersNode;
}
/*************************************************************************/
ProgramNode::~ProgramNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool ProgramNode::isExternal() const{
	return bIsExternal;
}
/*************************************************************************/
void ProgramNode::addResultDeclarationNode(Dec::DeclarationNode*     pResultDeclartionNode){
	IAS_TRACER;
	ptrParametersNode->addDeclaration(pResultDeclartionNode);
	bIsReturningResult=true;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Result for:"<<(void*)this<<","<<ptrQualifiedNameNode->getQualifiedName());
}
/*************************************************************************/
}
}
}
