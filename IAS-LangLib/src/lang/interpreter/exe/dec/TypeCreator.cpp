/*
 * File: IAS-LangLib/src/lang/interpreter/exe/dec/TypeCreator.cpp
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
#include "TypeCreator.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"
#include <vector>
#include "../exception/InterpreterException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Dec {

/*************************************************************************/
TypeCreator::TypeCreator() throw(){
	IAS_TRACER;
	pType=NULL;
	iSeq=0;
}

/*************************************************************************/
TypeCreator::~TypeCreator() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool TypeCreator::hasProperty(const String& strName) const{
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"has:"<<strName<<" in "<<(void*)this);
	return hmVariables.hasKey(strName);
}
/*************************************************************************/
const DM::Property* TypeCreator::getProperty(const String& strName) const{
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"get:"<<strName<<" in "<<(void*)this);

	if(hmVariables.hasKey(strName)){
		DM::ComplexType *pComplexType =  pType->asComplexType();
		return pComplexType->getProperties().getProperty(strName);
	}

	IAS_THROW(ItemNotFoundException(String("Variable: ")+=strName));
}
/*************************************************************************/
void TypeCreator::addProperty(Exe::Dec::VariableDeclaration* pVariableDeclaration){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"VarDecl:"<<pVariableDeclaration->getName()<<" at "<<(void*)pVariableDeclaration);

	IAS_CHECK_IF_NULL(pVariableDeclaration);
	if(hmVariables.count(pVariableDeclaration->getName()))
		IAS_THROW(InterpreterException(pVariableDeclaration->getName()+" <- variable already defined."));
	hmVariables[pVariableDeclaration->getName()]=pVariableDeclaration;
	pVariableDeclaration->setSeq(iSeq++);


}
/*************************************************************************/
const DM::Type *TypeCreator::getType() const{
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pType);
	return pType;
}
/*************************************************************************/
void TypeCreator::declareType(DM::DataFactory *pDataFactory,
								const String& strName,
								const String& strNamespace,
								const DM::Type* pBaseType){

	IAS_TRACER;

	IAS_CHECK_IF_VALID(pDataFactory);

	pType = pDataFactory->defineType(strNamespace,strName,pBaseType);

	if(pType->isDataObjectType()){

		DM::ComplexType *pComplexType =  pType->asComplexType();

		std::vector< Exe::Dec::VariableDeclaration *> tabOrderedDeclartions;

		tabOrderedDeclartions.resize(hmVariables.size());

		for(HashMapStringToPointer<Exe::Dec::VariableDeclaration>::const_iterator it=hmVariables.begin();
			it != hmVariables.end();
			it++)
			tabOrderedDeclartions[it->second->getSeq()]=it->second;


		for(int iIdx=0; iIdx<tabOrderedDeclartions.size(); iIdx++){

			const Exe::Dec::VariableDeclaration *pVariable = tabOrderedDeclartions[iIdx];
			IAS_CHECK_IF_NULL(pVariable);
			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Declare: "<<
								pVariable->getName()<<" of "<<
								pVariable->getType()->getFullName());

			pComplexType->defineProperty(pVariable->getName(),
										 pVariable->getType(),
										 pVariable->isArray());

		}

	}
}
/*************************************************************************/
}
}
}
}
}
