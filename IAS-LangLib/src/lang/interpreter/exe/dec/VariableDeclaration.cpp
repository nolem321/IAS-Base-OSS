/*
 * File: IAS-LangLib/src/lang/interpreter/exe/dec/VariableDeclaration.cpp
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
#include "VariableDeclaration.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Dec {

/*************************************************************************/
VariableDeclaration::VariableDeclaration(const String& strName,
								  const DM::Type *pType,
								  bool bIsArray){
	IAS_TRACER;

	this->strName=strName;
	this->pType=pType;
	this->bIsArray=bIsArray;
	this->iSeq=iSeq;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"VarDecl:"<<(void*)this);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"VarDecl:"<<strName<<" of "<<
								pType->getURI()<<":"<<
								pType->getName()<<(bIsArray?"[]":""));
}

/*************************************************************************/
VariableDeclaration::~VariableDeclaration() throw(){
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"VarDeclDeleted:"<<strName<<" of "<<
									pType->getURI()<<":"<<
									pType->getName());
}
/*************************************************************************/
void VariableDeclaration::setSeq(int iSeq){
	IAS_TRACER;
	this->iSeq=iSeq;
}
/*************************************************************************/
}
}
}
}
}
