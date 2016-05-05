/*
 * File: IAS-DataModelLib/src/dm/tools/Formatter.cpp
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
#include "../../dm/tools/Formatter.h"

#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/json/JSONHelper.h"
#include "../../dm/Type.h"
#include "../../dm/xml/XMLDocument.h"
#include "../../dm/xml/XMLHelper.h"

namespace IAS {
namespace DM {
namespace Tools {
/*************************************************************************/
DM::DataObjectPtr Formatter::LoadStream(std::istream& is, const DM::DataFactory* pDataFactory, const DM::Type* pExpectedType){
	IAS_TRACER;

	int c = is.get();

	while(is.good() && isblank(c)){
		c = is.get();
	}

	if(!is.good())
		IAS_THROW(Impl::RuntimeException("Unexpected end of stream before any data."));

	is.unget();

	DM::DataObjectPtr dmResult;

	if(c == '<'){

		IAS_DFT_FACTORY<XML::XMLHelper>::PtrHolder ptrHelper(IAS_DFT_FACTORY<XML::XMLHelper>::Create(pDataFactory));
		IAS_DFT_FACTORY<XML::XMLDocument>::PtrHolder ptrDoc(ptrHelper->readStream(is));

		dmResult=ptrDoc->getRootObject();

	}else if( c == '{' ){

		IAS_DFT_FACTORY<JSON::JSONHelper>::PtrHolder ptrHelper(IAS_DFT_FACTORY<JSON::JSONHelper>::Create(pDataFactory));
		dmResult = ptrHelper->load(is, pExpectedType);

	}else{
		IAS_THROW(BadUsageException("Expected '<' for XML or '{' for JSON content. "))
	}

	if(pExpectedType && !dmResult->getType()->isAssignableTo(pExpectedType))
		IAS_THROW(Impl::RuntimeException("Expected")<<pExpectedType->getFullName()<<", got: "<<dmResult->getType()->getFullName());

	return dmResult;

}
/*************************************************************************/
DM::DataObjectPtr Formatter::LoadFile(const String& strFileName, const DM::DataFactory* pDataFactory, const DM::Type* pExpectedType){
	IAS_TRACER;

	IAS_DFT_FACTORY<InputFile>::PtrHolder ptrFile(IAS_DFT_FACTORY<InputFile>::Create(strFileName));

	ptrFile->open();

	return LoadStream(ptrFile->getStreamRef(),pDataFactory,pExpectedType);

}
/*************************************************************************/
}
}
}
