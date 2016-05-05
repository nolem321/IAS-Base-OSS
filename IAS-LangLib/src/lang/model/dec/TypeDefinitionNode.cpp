/*
 * File: IAS-LangLib/src/lang/model/dec/TypeDefinitionNode.cpp
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
#include "TypeDefinitionNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {

/*************************************************************************/
TypeDefinitionNode::TypeDefinitionNode():
		strNamespace(DM::DataFactory::BuildInTypesNamespace){
	IAS_TRACER;
}
/*************************************************************************/
void TypeDefinitionNode::setName(const String& strName){
	IAS_TRACER;
	this->strName=strName;
}
/*************************************************************************/
void TypeDefinitionNode::setNamespace(const String& strNamespace){
	IAS_TRACER;
	this->strNamespace=strNamespace;
}
/*************************************************************************/
TypeDefinitionNode::~TypeDefinitionNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TypeDefinitionNode::setBaseTypeNode(TypeInfoNode* pTypeInfoNode){
	IAS_TRACER;
	this->ptrBaseTypeNode=pTypeInfoNode;
}
/*************************************************************************/
}
}
}
}
