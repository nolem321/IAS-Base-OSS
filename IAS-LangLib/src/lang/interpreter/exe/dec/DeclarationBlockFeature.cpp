/*
 * File: IAS-LangLib/src/lang/interpreter/exe/dec/DeclarationBlockFeature.cpp
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

#include <commonlib/commonlib.h>

#include "../Context.h"
#include <vector>
#include "../exception/InterpreterRuntimeException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Dec {

/*************************************************************************/
DeclarationBlockFeature::DeclarationBlockFeature() throw(){
	IAS_TRACER;
	pType=NULL;
	iSeq=0;
}

/*************************************************************************/
DeclarationBlockFeature::~DeclarationBlockFeature() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DeclarationBlockFeature::AutoPopUp::AutoPopUp(Context *pCtx, DM::DataObject *pVariables) throw()
:pCtx(pCtx){
	pCtx->pushBlock(pVariables);
};
/*************************************************************************/
DeclarationBlockFeature::AutoPopUp::~AutoPopUp(){ pCtx->popBlock(); };
/*************************************************************************/
void DeclarationBlockFeature::declareBlockVariables(DM::DataFactory *pDataFactory){
	IAS_TRACER;

	int iTypeId;

	{
		Mutex mutex;
		Mutex::Locker locker(mutex);
		static int iCounter = 0;
		iTypeId = ++iCounter;
	}

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Declare variables for:"<<iTypeId);

	StringStream ssTmp;
	ssTmp<<"IAS/Script/T"<<iTypeId;

	this->declareType(pDataFactory,DM::DataFactory::RootTypeName,ssTmp.str());

}
/*************************************************************************/
DM::DataObject* DeclarationBlockFeature::createAndInitializeVariables() const{
	IAS_TRACER;

	IAS_DFT_FACTORY<DM::DataObject>::PtrHolder ptrVariables;

	ptrVariables = pType->createDataObject();

	const DM::ComplexType *pComplexType =  pType->asComplexType();
	const DM::PropertyList& lstProperties = pComplexType->getProperties();

	for(int iIdx=0; iIdx<lstProperties.getSize(); iIdx++)
		if(! lstProperties.getProperty(iIdx)->isMulti() &&
				lstProperties.getProperty(iIdx)->getType()->getTypeEnum() != DM::Type::AnyType)
			ptrVariables->createDataObject(lstProperties.getProperty(iIdx));

	return ptrVariables.pass();
}
/*************************************************************************/
const DM::Type *DeclarationBlockFeature::getType() const{
	return TypeCreator::getType();
}
/*************************************************************************/
}
}
}
}
}
