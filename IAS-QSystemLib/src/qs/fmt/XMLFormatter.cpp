/*
 * File: IAS-QSystemLib/src/qs/fmt/XMLFormatter.cpp
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
#include "XMLFormatter.h"
#include<qs/log/LogLevel.h>
#include "dm/json/JSONHelper.h"

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {


const String& XMLFormatter::CElementEncoding("XMLfEnc");
const String& XMLFormatter::CElementName("XMLfName");
const String& XMLFormatter::CElementURI("XMLfURI");
const String& XMLFormatter::CEnvFirstNS("."+DM::XML::XMLHelper::CEnvFirstNS);

/*************************************************************************/
XMLFormatter::XMLFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

}
/*************************************************************************/
XMLFormatter::~XMLFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(true,"Parsing:       "<<tsrParsing);
	//IAS_LOG(true,"Serializing:   "<<tsrSerialization);

}
/*************************************************************************/
void XMLFormatter::read(DM::DataObjectPtr& dmData,
		   	   	   	   	std::istream&       istream,
		   	   	   	   	QS::API::Attributes *pAttributes){

	IAS_TRACER;


	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
			IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pDataFactory));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readStream(istream));

	dmData=ptrDoc->getRootObject();

	if(pAttributes){
		pAttributes->setValue(CElementName,ptrDoc->getElement());
		pAttributes->setValue(CElementURI,ptrDoc->getURI());
	}


	//TODO XML Document does not return original value on reading but the default one.
	//pAttributes->setValue(CElementEncoding,ptrDoc->getEncoding());

}
/*************************************************************************/
void XMLFormatter::write(const DM::DataObject* dmData,
						 std::ostream&       ostream,
						 QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();

	String strValue;

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
			IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pDataFactory));

	//TODO rething this cast/DM API Legacy is painful.
	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<DM::XML::XMLDocument>::Create(const_cast< ::IAS::DM::DataObject*>(dmData)));

	if(pAttributes){
		if(pAttributes->isSet(CElementName))
			ptrDocument->setElement(pAttributes->getValue(CElementName));

		if(pAttributes->isSet(CElementURI))
			ptrDocument->setURI(pAttributes->getValue(CElementURI));

		if(pAttributes->isSet(CElementEncoding))
			ptrDocument->setEncoding(pAttributes->getValue(CElementEncoding));

		if(pAttributes->isSet(CEnvFirstNS) && pAttributes->getValue(CEnvFirstNS).compare("N") == 0)
			ptrXMLHelper->setEmptyFirstNS(true);
		else
			ptrXMLHelper->setEmptyFirstNS(false);
	}

	ptrXMLHelper->save(ostream,ptrDocument);

	if(pAttributes){
		pAttributes->setValue(CElementName,ptrDocument->getElement());
		pAttributes->setValue(CElementURI,ptrDocument->getURI());
	}

	tsrSerialization.addSample(ts);
}
/*************************************************************************/
}
}
}
