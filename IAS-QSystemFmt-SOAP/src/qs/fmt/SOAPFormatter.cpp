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

/*************************************************************************/
SOAPFormatter::SOAPFormatter(const DM::DataFactory* pDataFactory, const String& strNS):
		pDataFactory(pDataFactory),
		strNS(strNS){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

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

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
			IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pDataFactory));

	ptrXMLHelper->setEmptyFirstNS(false);
	ptrXMLHelper->setPrefixElements(true);

	IAS_DFT_FACTORY<Parser>::PtrHolder ptrParser(IAS_DFT_FACTORY<Parser>::Create(ptrXMLHelper,
			IAS_DFT_FACTORY<DM::XML::LibXMLLexerForStream>::Create<std::istream&>(istream),
			pAttributes));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrParser->parse());

	dmData=ptrDoc->getRootObject();

	if(pAttributes){
		pAttributes->setValue(XMLFormatter::CElementName,ptrDoc->getElement());
		pAttributes->setValue(XMLFormatter::CElementURI,ptrDoc->getURI());
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

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
			IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pDataFactory));

	ptrXMLHelper->setEmptyFirstNS(false);
	ptrXMLHelper->setPrefixElements(true);

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<DM::XML::XMLDocument>::Create(const_cast< ::IAS::DM::DataObject*>(dmData)));

	if(pAttributes){
		if(pAttributes->isSet(XMLFormatter::CElementName))
			ptrDocument->setElement(pAttributes->getValue(XMLFormatter::CElementName));

		if(pAttributes->isSet(XMLFormatter::CElementURI))
			ptrDocument->setURI(pAttributes->getValue(XMLFormatter::CElementURI));

		if(pAttributes->isSet(XMLFormatter::CElementEncoding))
			ptrDocument->setEncoding(pAttributes->getValue(XMLFormatter::CElementEncoding));

		if(pAttributes->isSet(XMLFormatter::CEnvFirstNS) && pAttributes->getValue(XMLFormatter::CEnvFirstNS).compare("N") == 0)
					ptrXMLHelper->setEmptyFirstNS(true);
				else
					ptrXMLHelper->setEmptyFirstNS(false);

	}

	IAS_DFT_FACTORY<DM::XML::LibXMLWriterForStream>::PtrHolder ptrWriter(
			IAS_DFT_FACTORY<DM::XML::LibXMLWriterForStream>::Create<std::ostream&>(ostream));


	IAS_DFT_FACTORY<Serializer>::PtrHolder ptrSerializer(
			IAS_DFT_FACTORY<Serializer>::Create(ptrXMLHelper, ptrWriter, strNS, pAttributes));
	ptrSerializer->serialize(ptrDocument);

	if(pAttributes){
		pAttributes->setValue("TYPE",ptrDocument->getElement());
		pAttributes->setValue("SET","REBXMLNSC");

	}

	tsrSerialization.addSample(ts);
}
/*************************************************************************/
SOAPFormatterV1::SOAPFormatterV1(const DM::DataFactory* pDataFactory):
		SOAPFormatter(pDataFactory, "http://schemas.xmlsoap.org/soap/envelope/"){}
/*************************************************************************/
SOAPFormatterV12::SOAPFormatterV12(const DM::DataFactory* pDataFactory):
		SOAPFormatter(pDataFactory, "http://www.w3.org/2003/05/soap-envelope"){}
/*************************************************************************/
void SOAPFormatterV12::read(DM::DataObjectPtr& dmData,
		   	   	   	   		std::istream&       istream,
							QS::API::Attributes *pAttributes){

	IAS_TRACER;

	StringStream ssTmp;

	getSOAPContent(istream,ssTmp);

	SOAPFormatter::read(dmData, ssTmp, pAttributes);
}
/*************************************************************************/
void SOAPFormatterV12::getSOAPContent(std::istream& istream,
								   StringStream& ostream){

	String line;
	String boundry;
	String boundryEnd;

	bool inXml = false;

	while(!istream.eof()){

		getline(istream,line,'\r');

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Line:["<<line<<"]");

		char c;

		if((c=istream.get()) != '\n')
			IAS_THROW(BadUsageException("HTTP MTOM Parser Error: LF expected after CR: (int)c = "+TypeTools::IntToString(c)));

		if(!istream.good())
			IAS_THROW(BadUsageException("HTTP MTOM Parser Error: content reader failed."));

		if(inXml)
			if (line.compare(boundry) && line.compare(boundryEnd)){
				ostream << line;
			}else
				break;

		if ((line.length() > 1) && (line[0] == '-') && (line[1] == '-'))
			if (boundry.empty()) {
				boundry = line;
				boundryEnd = boundry + "--";
			}
			else
				break;

		if(!inXml && (line.length() > 0) && (line[0] == '<')) {
			ostream << line;
			inXml = true;
		}
	}


	IAS_LOG(LogLevel::INSTANCE.isInfo(),"SOAPContent:[["<<ostream.str()<<"]]");
}
/*************************************************************************/

}
}
}

/*************************************************************************/
extern "C"{
void* _ias_qs_fmt_SOAP(const ::IAS::DM::DataFactory* pDataFactory){
	IAS_TRACER;
	return IAS_DFT_FACTORY< ::IAS::QS::Fmt::SOAPFormatterV1 >::Create(pDataFactory);
}

void* _ias_qs_fmt_SOAP12(const ::IAS::DM::DataFactory* pDataFactory){
	IAS_TRACER;
	return IAS_DFT_FACTORY< ::IAS::QS::Fmt::SOAPFormatterV12 >::Create(pDataFactory);
}
}
/*************************************************************************/
