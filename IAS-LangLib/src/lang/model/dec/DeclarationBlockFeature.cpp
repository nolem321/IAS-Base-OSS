/*
 * File: IAS-LangLib/src/lang/model/dec/DeclarationBlockFeature.cpp
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
#include "DeclarationBlockFeature.h"
#include<lang/log/LogLevel.h>

#include "DeclarationNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {


/*************************************************************************/
DeclarationBlockFeature::DeclarationBlockFeature() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DeclarationBlockFeature::~DeclarationBlockFeature() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DeclarationBlockFeature::init(){
	IAS_TRACER;
}

/*************************************************************************/
void DeclarationBlockFeature::addDeclaration(::IAS::Lang::Model::Dec::DeclarationNode* pDeclaration){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pDeclaration);
	phcDeclarations.addPointer(pDeclaration);
	lstDeclarations.push_back(pDeclaration);
}
/*************************************************************************/
const DeclarationBlockFeature::DeclarationNodesList& DeclarationBlockFeature::getDeclarationsListAsConst() const{
	IAS_TRACER;
	return lstDeclarations;
}
/*************************************************************************/
const DeclarationBlockFeature::DeclarationNodesList& DeclarationBlockFeature::getDeclarationsList()const {
	IAS_TRACER;
	return lstDeclarations;
}
/*************************************************************************/
}
}
}
}
