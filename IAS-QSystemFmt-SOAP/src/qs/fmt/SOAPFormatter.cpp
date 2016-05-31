/*
 * File: IAS-QSystemLib/src/qs/fmt/SOAPFormatter.cpp
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
#include "SOAPFormatter.h"
#include <qs/log/LogLevel.h>
#include "dm/json/JSONHelper.h"
#include <dm/xml/LibXMLLexerForStream.h>
#include <dm/xml/LibXMLWriterForStream.h>

#include <qs/api.h>

#include "Parser.h"
#include "Serializer.h"

namespace IAS {
namespace QS {
namespace Fmt {


const String& SOAPFormatter::CElementEncoding("XMLfEnc");
const String& SOAPFormatter::CElementName("XMLfName");
const String& SOAPFormatter::CElementURI("XMLfURI");

/*************************************************************************/
SOAPFormatter::SOAPFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);
	ptrXMLHelper=IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pDataFactory);
	ptrXMLHelper->setEmptyFirstNS(true);

}
/*************************************************************************/
SOAPFormatter::~SOAPFormatter() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SOAPFormatter::read(DM::DataObjectPtr& dmData,
		   	   	   	   	std::istream&       istream,
		   	   	   	   	QS::API::Attributes *pAttributes){

	IAS_TRACER;


	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();


	IAS_DFT_FACTORY<Parser>::PtrHolder ptrParser(IAS_DFT_FACTORY<Parser>::Create(ptrXMLHelper,
			IAS_DFT_FACTORY<DM::XML::LibXMLLexerForStream>::Create<std::istream&>(istream),
			pAttributes));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrParser->parse());

	dmData=ptrDoc->getRootObject();

	if(pAttributes){
		pAttributes->setValue(CElementName,ptrDoc->getElement());
		pAttributes->setValue(CElementURI,ptrDoc->getURI());
	}

}
/*************************************************************************/
void SOAPFormatter::write(const DM::DataObject* dmData,
						 std::ostream&       ostream,
						 QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();

	String strValue;


	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<DM::XML::XMLDocument>::Create(const_cast< ::IAS::DM::DataObject*>(dmData)));

	if(pAttributes){
		if(pAttributes->isSet(CElementName))
			ptrDocument->setElement(pAttributes->getValue(CElementName));

		if(pAttributes->isSet(CElementURI))
			ptrDocument->setURI(pAttributes->getValue(CElementURI));

		if(pAttributes->isSet(CElementEncoding))
			ptrDocument->setEncoding(pAttributes->getValue(CElementEncoding));
	}

	IAS_DFT_FACTORY<DM::XML::LibXMLWriterForStream>::PtrHolder ptrWriter(
			IAS_DFT_FACTORY<DM::XML::LibXMLWriterForStream>::Create<std::ostream&>(ostream));

	IAS_DFT_FACTORY<Serializer>::PtrHolder ptrSerializer(IAS_DFT_FACTORY<Serializer>::Create(ptrXMLHelper, ptrWriter,pAttributes));
	ptrSerializer->serialize(ptrDocument);

	if(pAttributes){
		pAttributes->setValue("TYPE",ptrDocument->getElement());
		pAttributes->setValue("SET","REBXMLNSC");

	}

	tsrSerialization.addSample(ts);
}
/*************************************************************************/
}
}
}

/*************************************************************************/
extern "C"{
void* _ias_qs_fmt_SOAP(const ::IAS::DM::DataFactory* pDataFactory){
	IAS_TRACER;
	return IAS_DFT_FACTORY< ::IAS::QS::Fmt::SOAPFormatter >::Create(pDataFactory);
}
}
/*************************************************************************/
