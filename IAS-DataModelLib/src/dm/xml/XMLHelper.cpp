/*
 * File: IAS-DataModelLib/src/dm/xml/XMLHelper.cpp
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
#include "../../dm/xml/XMLHelper.h"
#include <commonlib/commonlib.h>
#include "LibXMLLexerForFile.h"
#include "../../dm/DataObject.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/LibXMLLexerForFile.h"
#include "../../dm/xml/LibXMLLexerForMemory.h"
#include "../../dm/xml/LibXMLLexerForStream.h"
#include "../../dm/xml/LibXMLWriterForFile.h"
#include "../../dm/xml/LibXMLWriterForMemory.h"
#include "../../dm/xml/LibXMLWriterForStream.h"
#include "../../dm/xml/XMLDocument.h"
#include "../../dm/xml/XMLParser.h"
#include "../../dm/xml/XMLSerializer.h"

namespace IAS {
namespace DM {
namespace XML {

const String XMLHelper::CEnvNULLAction("IAS_DM_XML_SKIPNULL");
const String XMLHelper::CEnvFirstNS("IAS_DM_XML_NS0");
const String XMLHelper::CXMLPayloadElement("xmlPayload");


struct XMLHelperDefaults {

	XMLHelperDefaults():
		bSkipNullElements(false),
		bEmptyFirstNS(false),
		bPrefixElements(false){

		String strNULLAction;

		bSkipNullElements = EnvTools::GetEnv(XMLHelper::CEnvNULLAction,strNULLAction) &&
								(!strNULLAction.compare("Y") || !strNULLAction.compare("y"));

		String strFirstNS;

		if(EnvTools::GetEnv(XMLHelper::CEnvFirstNS,strFirstNS))
			bEmptyFirstNS =	(!strFirstNS.compare("N") || !strFirstNS.compare("n"));

	};

	bool bSkipNullElements;
	bool bEmptyFirstNS;
	bool bPrefixElements;

};

static XMLHelperDefaults TheXMLHelperDefaults;

/*************************************************************************/
XMLHelper::XMLHelper(const ::IAS::DM::DataFactory *pDataFactory):
		pDataFactory(pDataFactory),
		bSkipNullElements(TheXMLHelperDefaults.bSkipNullElements),
		bEmptyFirstNS(TheXMLHelperDefaults.bEmptyFirstNS),
		bPrefixElements(TheXMLHelperDefaults.bPrefixElements){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);
}
/*************************************************************************/
XMLHelper::~XMLHelper() throw(){
	IAS_TRACER;

}
/*************************************************************************/
void XMLHelper::save(const String& strFileName,
				     const XMLDocument *pDocument){
	IAS_TRACER;

	IAS_DFT_FACTORY<LibXMLWriterForFile>::PtrHolder ptrWriter(IAS_DFT_FACTORY<LibXMLWriterForFile>::Create(strFileName));

	IAS_DFT_FACTORY<XMLSerializer>::PtrHolder ptrXMLSerializer(IAS_DFT_FACTORY<XMLSerializer>::Create(this, ptrWriter.getPointer()));
	ptrXMLSerializer->serialize(pDocument);

}
/*************************************************************************/
void XMLHelper::save(const String& strFileName,
				       const ::IAS::DM::DataObject *pDataObject,
				       const String& strElement,
				       const String& strURI){
	IAS_TRACER;

	//TODO rething this cast/DM API Legacy is painful.
	IAS_DFT_FACTORY<XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<XMLDocument>::Create(const_cast< ::IAS::DM::DataObject*>(pDataObject)));

	save(strFileName,ptrDocument);
}
/*************************************************************************/
void XMLHelper::save(String& strOutput,
				     const XMLDocument *pDocument){
	IAS_TRACER;


	IAS_DFT_FACTORY<LibXMLWriterForMemory>::PtrHolder ptrWriter(IAS_DFT_FACTORY<LibXMLWriterForMemory>::Create());

	IAS_DFT_FACTORY<XMLSerializer>::PtrHolder ptrXMLSerializer(IAS_DFT_FACTORY<XMLSerializer>::Create(this, ptrWriter.getPointer()));
	ptrXMLSerializer->serialize(pDocument);

	strOutput=ptrWriter->getBufferAsCString();
}
/*************************************************************************/
void XMLHelper::save(String& strOutput,
						const ::IAS::DM::DataObject *pDataObject,
						const String& strElement,
						const String& strURI){
	IAS_TRACER;

	//TODO rething this cast/DM API Legacy is painful.
	IAS_DFT_FACTORY<XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<XMLDocument>::Create(const_cast< ::IAS::DM::DataObject*>(pDataObject)));

	ptrDocument->setElement(strElement);
	ptrDocument->setURI(strURI);

	save(strOutput,ptrDocument);
}
/*************************************************************************/
void XMLHelper::save(std::ostream& osOutput,
				     const XMLDocument *pDocument){
	IAS_TRACER;


	IAS_DFT_FACTORY<LibXMLWriterForStream>::PtrHolder ptrWriter(IAS_DFT_FACTORY<LibXMLWriterForStream>::Create<std::ostream&>(osOutput));

	IAS_DFT_FACTORY<XMLSerializer>::PtrHolder ptrXMLSerializer(IAS_DFT_FACTORY<XMLSerializer>::Create(this, ptrWriter.getPointer()));
	ptrXMLSerializer->serialize(pDocument);

}
/*************************************************************************/
void XMLHelper::save(std::ostream& osOutput,
						const ::IAS::DM::DataObject *pDataObject,
						const String& strElement,
						const String& strURI){
	IAS_TRACER;

	//TODO rething this cast/DM API Legacy is painful.
	IAS_DFT_FACTORY<XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<XMLDocument>::Create(const_cast< ::IAS::DM::DataObject*>(pDataObject)));

	ptrDocument->setElement(strElement);
	ptrDocument->setURI(strURI);

	save(osOutput,ptrDocument);
}
/*************************************************************************/
XMLDocument* XMLHelper::readFile(const String& strFileName){
	IAS_TRACER;

	IAS_DFT_FACTORY<XMLParser>::PtrHolder ptrParser(IAS_DFT_FACTORY<XMLParser>::Create(this,
				IAS_DFT_FACTORY<LibXMLLexerForFile>::Create(strFileName)));
	return ptrParser->parse();
}
/*************************************************************************/
XMLDocument* XMLHelper::readString(const String& strXML){
	IAS_TRACER;

	IAS_DFT_FACTORY<XMLParser>::PtrHolder ptrParser(IAS_DFT_FACTORY<XMLParser>::Create(this,
			IAS_DFT_FACTORY<LibXMLLexerForMemory>::Create(strXML)));

	return ptrParser->parse();
}
/*************************************************************************/
XMLDocument* XMLHelper::readStream(std::istream& is){
	IAS_TRACER;

	IAS_DFT_FACTORY<XMLParser>::PtrHolder ptrParser(IAS_DFT_FACTORY<XMLParser>::Create(this,
			IAS_DFT_FACTORY<LibXMLLexerForStream>::Create<std::istream&>(is)));

	return ptrParser->parse();
}
/*************************************************************************/
String XMLHelper::Stringify(const ::IAS::DM::DataFactory *pDataFactory,
							const ::IAS::DM::DataObject  *pDataObject){
	IAS_TRACER;
	String strResult;

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDocument(
		IAS_DFT_FACTORY<DM::XML::XMLDocument>::Create(const_cast< ::IAS::DM::DataObject*>(pDataObject)));

	IAS_DFT_FACTORY<XMLHelper>::PtrHolder ptrXMLHelper(IAS_DFT_FACTORY<XMLHelper>::Create(pDataFactory));
	ptrXMLHelper->save(strResult,ptrDocument);
	return strResult;
}
/*************************************************************************/
void XMLHelper::setEmptyFirstNS(bool bEmptyFirstNS){
	IAS_TRACER;
	this->bEmptyFirstNS=bEmptyFirstNS;
}
/*************************************************************************/
void XMLHelper::setPrefixElements(bool bPrefixElements){
	IAS_TRACER;
	this->bPrefixElements=bPrefixElements;
}
/*************************************************************************/
}
}
}

#include "../../dm/xml/LibXMLWriterForFile.h"
