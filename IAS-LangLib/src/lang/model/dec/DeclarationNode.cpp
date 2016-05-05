/*
 * File: IAS-LangLib/src/lang/model/dec/DeclarationNode.cpp
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
#include "DeclarationNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {

/*************************************************************************/
DeclarationNode::DeclarationNode(const String& strVariable,
		 	 	 	 	 	 	 const String& strType,
		 	 	 	 	 	 	 const String& strNamespace):
 strVariable(strVariable),
 strType(strType),
 strNamespace(strNamespace),
 bIsArray(false){

	IAS_TRACER;

	//TODO (M) the same for DeclarationNode, check what exec builder does.
	//if(this->strNamespace.length() == 0)
	//	this->strNamespace=DM::DataFactory::BuildInTypesNamespace;

}
/*************************************************************************/
DeclarationNode::~DeclarationNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DeclarationNode::setIsArray(bool bIsArray){
	IAS_TRACER;
	this->bIsArray=bIsArray;
}
/*************************************************************************/
}
}
}
}
