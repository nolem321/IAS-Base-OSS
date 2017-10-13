/*
 * File: IAS-DataModelLib/src/dm/xml/XSDParser.cpp
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
#include "../../dm/xml/XSDParser.h"
#include <commonlib/commonlib.h>

#include "../../dm/DataFactory.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Type.h"
#include "../../dm/PropertyList.h"
#include "../../dm/xml/LibXMLLexer.h"
#include "../../dm/xml/LibXMLWrapper.h"
#include "../../dm/xml/XSDHelper.h"
#include "../../dm/xml/XMLHelper.h"


namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
XSDParser::PropertyInfo::PropertyInfo() throw():
 bIsMulti(false),
 bIsXMLAttribute(false)
{}
/*************************************************************************/
XSDParser::XSDParser(XSDHelper* pXSDHelper, LibXMLLexer *pLibXMLLexer): iInlineCount(1){
	IAS_TRACER;
	this->pXSDHelper=pXSDHelper;
	ptrLibXMLLexer=pLibXMLLexer;
	pDataFactory=pXSDHelper->getDataFactory();
	IAS_CHECK_IF_VALID(pDataFactory);
}
/*************************************************************************/
void XSDParser::PropertyInfo::init(){};
void XSDParser::TypeInfo::init(){};
/*************************************************************************/
XSDParser::~XSDParser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const String XSDParser::StrXSDSchema("http://www.w3.org/2001/XMLSchema");
/*************************************************************************/
const String& XSDParser::getTargetNamespace()const{
	IAS_TRACER;
	return strTargetNamespace;
}
/*************************************************************************/
void XSDParser::popCurrentType(){
	IAS_TRACER;
	stackTypeInfo.pop();
}
/*************************************************************************/
void XSDParser::pushCurrentType(TypeInfo* pTypeInfo){
	IAS_TRACER;

	if(hmTypeInfo.count(pTypeInfo->strName))
		IAS_THROW(BadUsageException("Type alread defined: ["+pTypeInfo->strName+"]"));

	hmTypeInfo[pTypeInfo->strName]=pTypeInfo;

	stackTypeInfo.push(pTypeInfo);
}
/*************************************************************************/
XSDParser::TypeInfo* XSDParser::getCurrentType(){
	IAS_TRACER;

	if(stackTypeInfo.size() == 0)
		IAS_THROW(InternalException("stackTypeInfo.size() == 0"));

	return stackTypeInfo.top();
}

/*************************************************************************/
void XSDParser::updateInlineTypeName(PropertyInfo* pPropertyInfo){
	StringStream ssTmp;
	ssTmp << "Inline" << iInlineCount++ << pPropertyInfo->strName;
	pPropertyInfo->strTypeName=ssTmp.str();
	pPropertyInfo->strTypeURI=strTargetNamespace;
}
/*************************************************************************/
XSDParser::PropertyInfo* XSDParser::readPropertyInfo(bool bCheckMulti){
	IAS_TRACER;

	IAS_DFT_FACTORY<PropertyInfo>::PtrHolder ptrPropertyInfo( IAS_DFT_FACTORY<PropertyInfo>::Create());

	ptrPropertyInfo->strName = ptrLibXMLLexer->getMandatoryAttribute("name");

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Property:"<<ptrPropertyInfo->strName);

	String strTypePrefix;
	String strType;

	int iMaxOccurs = 1;

	if(bCheckMulti){
		String strMaxOccurs;
		if(ptrLibXMLLexer->getOptionalAttribute("maxOccurs",strMaxOccurs)){
			if(strMaxOccurs.compare("unbounded")==0)
				iMaxOccurs=-1;
			else
				iMaxOccurs=TypeTools::StringToInt(strMaxOccurs);
		}
	}

	if(!ptrLibXMLLexer->getOptionalAttribute("type", strType)){

		while(true) {

			if(!ptrLibXMLLexer->nextElement())
				IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

			if(ptrLibXMLLexer->checkType(XML_READER_TYPE_ELEMENT)) {

				if(ptrLibXMLLexer->checkLocalName("complexType")) {

					updateInlineTypeName(ptrPropertyInfo);
					parse_xsd_complexType(ptrPropertyInfo->strTypeName);
					break;

				} else if(ptrLibXMLLexer->checkLocalName("simpleType")) {

					updateInlineTypeName(ptrPropertyInfo);
					parse_xsd_simpleType(ptrPropertyInfo->strTypeName);
					break;

				}

			}
		}

	}else{

		LibXMLLexer::ChopOffPrefix(strType,
									strTypePrefix,
									ptrPropertyInfo->strTypeName);

		lookupURI(strTypePrefix, ptrPropertyInfo->strTypeURI);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Prefix:"<<strTypePrefix<<" -> "<<ptrPropertyInfo->strTypeURI);
	}



	ptrPropertyInfo->bIsMulti = iMaxOccurs != 1;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Details: "
						<<ptrPropertyInfo->strTypeURI<<":"
						<<ptrPropertyInfo->strTypeName<<" list="
						<<ptrPropertyInfo->bIsMulti);

	return ptrPropertyInfo.pass();
}
/*************************************************************************/
void XSDParser::parse_xsd_element(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	PropertyInfo* pPropertyInfo=readPropertyInfo(true);
	lstTargetNSElements.push_back(pPropertyInfo);

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("annotation")) {
			pPropertyInfo->strDocumentation=parse_xsd_annotation();
		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
				ptrLibXMLLexer->checkLocalName("element"))
		return;

	}

}
/*************************************************************************/
String XSDParser::parse_xsd_annotation(){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start annotation");

	StringStream ssResult;

	if(ptrLibXMLLexer->isEmpty())
		return ssResult.str();

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("documentation")) {
			ssResult<<parse_xsd_documentation();
		}else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
			   ptrLibXMLLexer->checkLocalName("annotation"))
				return ssResult.str();

	}

}
/*************************************************************************/
String XSDParser::parse_xsd_documentation(){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start documentation");

	StringStream ssResult;

	if(ptrLibXMLLexer->isEmpty())
		return ssResult.str();

	bool bFirst=true;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
			   ptrLibXMLLexer->checkLocalName("documentation"))
			return ssResult.str();

		if(ptrLibXMLLexer->hasValue()){
			if(!bFirst)
				ssResult<<", ";
			ssResult<<ptrLibXMLLexer->getValue();
			bFirst=false;
		}
	}

}
/*************************************************************************/
void XSDParser::parse_xsd_complexTypeElement(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	TypeInfo* pCurrentTypeInfo=getCurrentType();
	PropertyInfo* pPropertyInfo=readPropertyInfo(true);
	pCurrentTypeInfo->lstPropertyInfo.push_back(pPropertyInfo);

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("annotation")) {
			pPropertyInfo->strDocumentation=parse_xsd_annotation();
		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
			ptrLibXMLLexer->checkLocalName("element"))
			return;
	}
}
/*************************************************************************/
void XSDParser::parse_xsd_sequence(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("element")){
				parse_xsd_complexTypeElement();
		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
		   ptrLibXMLLexer->checkLocalName("sequence"))
			return;

	}

}
/*************************************************************************/
void XSDParser::parse_xsd_choice(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("element")){
				parse_xsd_complexTypeElement();
		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
		   ptrLibXMLLexer->checkLocalName("choice"))
			return;

	}

}
/*************************************************************************/
void XSDParser::parse_xsd_all(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("element")){
				parse_xsd_complexTypeElement();
		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
		   ptrLibXMLLexer->checkLocalName("all"))
			return;

	}

}
/*************************************************************************/
void XSDParser::parse_xsd_include(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	String strLocation = ptrLibXMLLexer->getMandatoryAttribute("schemaLocation");

	if(strWorkingDir.length() > 0)
		strLocation =  strWorkingDir + "/" +strLocation;

	pXSDHelper->includeTypesFromFile(strLocation, strTargetNamespace);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"End of include.");
}
/*************************************************************************/
void XSDParser::parse_xsd_import(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	String strLocation = ptrLibXMLLexer->getMandatoryAttribute("schemaLocation");

	String strTargetNamespace = ptrLibXMLLexer->getMandatoryAttribute("namespace");


	if(strWorkingDir.length() > 0)
		strLocation =  strWorkingDir + "/" +strLocation;

	pXSDHelper->defineTypesFromFile(strLocation, strTargetNamespace);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"End of include.");
}
/*************************************************************************/
void XSDParser::parse_xsd_complexType(){
	IAS_TRACER;

	parse_xsd_complexType(ptrLibXMLLexer->getMandatoryAttribute("name"));
}
/*************************************************************************/
void XSDParser::parse_xsd_complexType(const String& strName){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Type:"<<strName);

	IAS_DFT_FACTORY<TypeInfo>::PtrHolder ptrTypeInfo(IAS_DFT_FACTORY<TypeInfo>::Create());

	ptrTypeInfo->strName=strName;

	pushCurrentType(ptrTypeInfo.pass());

	if(!ptrLibXMLLexer->isEmpty())
		while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Check:"<<	ptrLibXMLLexer->getLocalName());

		if(ptrLibXMLLexer->checkLocalName("sequence")){
				parse_xsd_sequence();
				IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Check:"<<	ptrLibXMLLexer->getLocalName());

		}else if(ptrLibXMLLexer->checkLocalName("choice")){
				parse_xsd_choice();

		}else if(ptrLibXMLLexer->checkLocalName("all")){
					parse_xsd_all();

		}else if(ptrLibXMLLexer->checkLocalName("complexContent")){
				parse_xsd_complexContent();

		}else if(ptrLibXMLLexer->checkLocalName("simpleContent")){
					parse_xsd_simpleContent();

		}else if(ptrLibXMLLexer->checkLocalName("attribute")){
				parse_xsd_complexTypeAttribute();

		}else if(ptrLibXMLLexer->checkLocalName("annotation")) {
			getCurrentType()->strDocumentation=parse_xsd_annotation();

		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
				   ptrLibXMLLexer->checkLocalName("complexType"))
			break;

	}

	popCurrentType();
}
/*************************************************************************/
void XSDParser::parse_xsd_complexTypeAttribute(){
	IAS_TRACER

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Start.");

	IAS_DFT_FACTORY<PropertyInfo>::PtrHolder ptrPropertyInfo(readPropertyInfo(false));

	ptrPropertyInfo->bIsXMLAttribute=true;
	getCurrentType()->lstPropertyInfo.push_back(ptrPropertyInfo.pass());;

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
		   ptrLibXMLLexer->checkLocalName("attribute"))
			return;
	}

}
/*************************************************************************/
void XSDParser::parse_xsd_simpleType(){
	IAS_TRACER;
	parse_xsd_simpleType(ptrLibXMLLexer->getMandatoryAttribute("name"));
}
/*************************************************************************/
void XSDParser::parse_xsd_simpleType(const String& strName){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");


	IAS_DFT_FACTORY<TypeInfo>::PtrHolder ptrTypeInfo(IAS_DFT_FACTORY<TypeInfo>::Create());

	ptrTypeInfo->strName=strName;
	pushCurrentType(ptrTypeInfo.pass());

	if(!ptrLibXMLLexer->isEmpty())
		while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("restriction")){
				parse_xsd_restriction();
		}else if(ptrLibXMLLexer->checkLocalName("annotation")) {
			getCurrentType()->strDocumentation=parse_xsd_annotation();
		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
				   ptrLibXMLLexer->checkLocalName("simpleType"))
			break;

	}

	popCurrentType();
}

/*************************************************************************/
void XSDParser::parse_xsd_complexContent(){
	IAS_TRACER;

	if(ptrLibXMLLexer->isEmpty())
		return;

	if(!ptrLibXMLLexer->nextElement())
		IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

	if(ptrLibXMLLexer->checkLocalName("extension")){
		parse_xsd_extension(true);

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))
	}

	if(ptrLibXMLLexer->checkLocalName("restriction")){
		parse_xsd_restriction();

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))
	}

	if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
	   ptrLibXMLLexer->checkLocalName("complexContent"))
		return;

	IAS_THROW(XMLHelperException("XSD Error in a complex type."));
}
/*************************************************************************/
void XSDParser::parse_xsd_simpleContent(){
	IAS_TRACER;

	if(ptrLibXMLLexer->isEmpty())
		return;

	if(!ptrLibXMLLexer->nextElement())
		IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

	if(ptrLibXMLLexer->checkLocalName("extension")){
		parse_xsd_extension(false);

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))
	}

	if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
	   ptrLibXMLLexer->checkLocalName("simpleContent"))
		return;

	IAS_THROW(XMLHelperException("XSD Error in a complex type."));
}


/*************************************************************************/

void XSDParser::lookupURI(const String& strTypePrefix, String& strResult) {
	ptrLibXMLLexer->lookupURI(strTypePrefix, strResult);
}

/*************************************************************************/
void XSDParser::parse_xsd_extension(bool bComplexType){
	IAS_TRACER;



	if(bComplexType) {

		TypeInfo* pCurrentTypeInfo=getCurrentType();

		String strTypePrefix;
		LibXMLLexer::ChopOffPrefix(ptrLibXMLLexer->getMandatoryAttribute("base"),
				strTypePrefix,
				pCurrentTypeInfo->strBaseTypeName);

		lookupURI(strTypePrefix, pCurrentTypeInfo->strBaseTypeURI);

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"BaseType: "
				<<pCurrentTypeInfo->strBaseTypeURI<<":"
				<<pCurrentTypeInfo->strBaseTypeName);

	} else {

		TypeInfo* pCurrentTypeInfo=getCurrentType();

		IAS_DFT_FACTORY<PropertyInfo>::PtrHolder ptrPropertyInfo( IAS_DFT_FACTORY<PropertyInfo>::Create());

		ptrPropertyInfo->strName=XMLHelper::CXMLPayloadElement;

		String strTypePrefix;

		LibXMLLexer::ChopOffPrefix(ptrLibXMLLexer->getMandatoryAttribute("base"),
					strTypePrefix,
					ptrPropertyInfo->strTypeName);

		lookupURI(strTypePrefix, ptrPropertyInfo->strTypeURI);

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Check simpleContent: "<<strTargetNamespace<<"#"<<pCurrentTypeInfo->strName);

		pCurrentTypeInfo->lstPropertyInfo.push_back(ptrPropertyInfo.pass());
	}


	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){
		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

			if(ptrLibXMLLexer->checkLocalName("sequence")){
				parse_xsd_sequence();

			}else if(ptrLibXMLLexer->checkLocalName("choice")){
				parse_xsd_choice();

			}else if(ptrLibXMLLexer->checkLocalName("attribute")){
				parse_xsd_complexTypeAttribute();
			}

	if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
	   ptrLibXMLLexer->checkLocalName("extension"))
		return;

	}

	IAS_THROW(XMLHelperException("XSD Error in an extension."));
}
/*************************************************************************/
void XSDParser::parse_xsd_maxLength(){

	IAS_TRACER;

	TypeInfo* pCurrentTypeInfo=getCurrentType();
	String strValue = ptrLibXMLLexer->getMandatoryAttribute("value");
	pCurrentTypeInfo->iMaxLength = TypeTools::StringToInt(strValue);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),pCurrentTypeInfo->strName<<", maxLength: "<<pCurrentTypeInfo->iMaxLength);

}
/*************************************************************************/
void XSDParser::parse_xsd_restriction(){
	IAS_TRACER;

	TypeInfo* pCurrentTypeInfo=getCurrentType();

	String strTypePrefix;
	LibXMLLexer::ChopOffPrefix(ptrLibXMLLexer->getMandatoryAttribute("base"),
							   strTypePrefix,
							   pCurrentTypeInfo->strBaseTypeName);

	lookupURI(strTypePrefix, pCurrentTypeInfo->strBaseTypeURI);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"RestrictionType: "
				<<pCurrentTypeInfo->strBaseTypeURI<<":"
				<<pCurrentTypeInfo->strBaseTypeName);

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkLocalName("maxLength")){
			parse_xsd_maxLength();
		}

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
			ptrLibXMLLexer->checkLocalName("restriction"))
		return;
	}

	IAS_THROW(XMLHelperException("XSD Error in a restriction."));
}

/*************************************************************************/
void XSDParser::parse_xsd_schemaAttribute(){
	IAS_TRACER;

	String strName(ptrLibXMLLexer->getLocalName());
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Attribute:"<<strName);

	String strValue(ptrLibXMLLexer->getValue());
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"AttributeValue:"<<strValue);
	String strPrefix;
	String strURI;
	ptrLibXMLLexer->getPrefixWithURI(strPrefix, strURI);
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Attribute URI:"<<strURI);

	if(strName.compare("targetNamespace")==0){

		if(!strTargetNamespace.empty() && strValue.compare(strTargetNamespace) != 0)
			IAS_THROW(BadUsageException("Target namespace already set to: "+strTargetNamespace+", new: "+strValue));
		strTargetNamespace = strValue;
	}
}
/*************************************************************************/
void XSDParser::parse_xsd_schema(){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Start.");

	String strPrefix;
	String strURI;
	bool getPrefixWithURI(String& strPrefix, String& strURI);
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Schema URI:"<<strURI);

	while(ptrLibXMLLexer->nextAttribute()){
		parse_xsd_schemaAttribute();
	}

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("xsd:schema definition or at least close tag expected."))

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
		   ptrLibXMLLexer->checkLocalName("schema"))
			return;

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_ELEMENT)){

			if(ptrLibXMLLexer->checkLocalName("include")) {
				parse_xsd_include();
			}else if(ptrLibXMLLexer->checkLocalName("import")) {
				parse_xsd_import();
			}else if(ptrLibXMLLexer->checkLocalName("complexType")) {
				parse_xsd_complexType();
			}else if(ptrLibXMLLexer->checkLocalName("simpleType")) {
				parse_xsd_simpleType();
			}else if(ptrLibXMLLexer->checkLocalName("element")){
				parse_xsd_element();
			}

			continue;
		}

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_TEXT))
			continue;

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT))
			continue;

		IAS_THROW(XMLHelperException(String("XML_READER_TYPE_ELEMENT/XML_READER_TYPE_TEXT expected in <xsd:schema>, got: ")+=
				(LibXMLWrapper::GetInstance()->getNodeName(ptrLibXMLLexer->getType()))));

	}/* WHILE */;

}
/*************************************************************************/
void XSDParser::parse(){
	IAS_TRACER;
	ptrLibXMLLexer->setSkipSignificantWhiteSpaces(true);

	if(!ptrLibXMLLexer->nextElement() ||
		!ptrLibXMLLexer->checkType(XML_READER_TYPE_ELEMENT) ||
		!ptrLibXMLLexer->checkLocalName("schema"))
			IAS_THROW(XMLHelperException("XSD begin ?? expected;"))

	parse_xsd_schema();


}
/*************************************************************************/
void XSDParser::define(){
	IAS_TRACER;

	defineTypes();
	defineTargetNSElements();
}
/*************************************************************************/
void XSDParser::setWorkingDir(const String& strDir){
	IAS_TRACER;
	this->strWorkingDir=strDir;
}
/*************************************************************************/
bool XSDParser::verfifyExisting(const ::IAS::DM::Type* pBaseType,
		TypeInfo* pTypeInfo) {

	IAS_TRACER;

	try{
		pTypeInfo->pType=getConvertedType(strTargetNamespace, pTypeInfo->strName);
	}catch(ItemNotFoundException& e){
		return false;
	};

	if (pTypeInfo->pType->isRootType() != (pBaseType == NULL))
		IAS_THROW(BadUsageException(
					strTargetNamespace + "#" + pTypeInfo->strName
					+ " alread defined with different specification (is root type)"));

	if (!pTypeInfo->pType->isRootType()
			&& (pBaseType->getURI().compare(pTypeInfo->strBaseTypeURI) != 0
					|| pBaseType->getName().compare(pTypeInfo->strBaseTypeName)!= 0))
			IAS_THROW(BadUsageException(
					strTargetNamespace + "#" + pTypeInfo->strName
					+ " alread defined with different specification (base type name)"));


	if(pTypeInfo->pType->isDataObjectType()){

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Verify props1: "<<pTypeInfo->lstPropertyInfo.size());

		//IAS_MY_STACK().printStack(std::cerr);

		int iExpected = pTypeInfo->pType->asComplexType()->getProperties().getSize();
		if(pBaseType)
			iExpected -= pBaseType->asComplexType()->getProperties().getSize();

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Verify props2: "<<iExpected);

	   if(iExpected != pTypeInfo->lstPropertyInfo.size())
			IAS_THROW(BadUsageException(strTargetNamespace + "#" + pTypeInfo->strName
					+ " alread defined with different specification (properties), expected:  "
					+ TypeTools::IntToString(iExpected) + ", got: "
	   	   	   	    + TypeTools::IntToString(pTypeInfo->lstPropertyInfo.size())));
	}

	return true;
}

/*************************************************************************/
DM::Type* XSDParser::defineType(TypeInfo* pTypeInfo, bool bSkipProperties){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pTypeInfo);


	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),
			" New type:"<<pTypeInfo->strName<<" "<<bSkipProperties<<" "<<pTypeInfo->pType);

	if(pTypeInfo->iStage == TypeInfo::STAGE_DEFINE)
		IAS_THROW(XMLHelperException("Cycle detected for a type definition of: "+strTargetNamespace+":"+pTypeInfo->strName));

	if(pTypeInfo->iStage == TypeInfo::STAGE_PROPERTIES){
		if(!bSkipProperties){
			createProperties(pTypeInfo);
			pTypeInfo->iStage=TypeInfo::STAGE_DEFINED;
		}else{
			return pTypeInfo->pType;
		}
	}

	if(pTypeInfo->iStage == TypeInfo::STAGE_DEFINED){
		return pTypeInfo->pType;
	};

	pTypeInfo->iStage=TypeInfo::STAGE_DEFINE;

	const ::IAS::DM::Type *pBaseType = NULL;

	if(!(pTypeInfo->strBaseTypeName.empty())){
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),
						"Base !"<<pTypeInfo->strBaseTypeName);

		if(pTypeInfo->strBaseTypeURI.compare(strTargetNamespace) == 0
				&& hmTypeInfo.count(pTypeInfo->strBaseTypeName) > 0)
			 pBaseType = defineType(hmTypeInfo[pTypeInfo->strBaseTypeName]);

		try{
			 pBaseType = getConvertedType(pTypeInfo->strBaseTypeURI, pTypeInfo->strBaseTypeName);
		}catch(ItemNotFoundException& e){

			if(pTypeInfo->strBaseTypeURI.compare(strTargetNamespace) != 0 || hmTypeInfo.count(pTypeInfo->strBaseTypeName) == 0)
				IAS_THROW(XMLHelperException("Cannot find a type definition for: "+pTypeInfo->strBaseTypeURI+":"+pTypeInfo->strBaseTypeName));
		};

		IAS_CHECK_IF_VALID(pBaseType);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Base:"<<(void*)pBaseType);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Base:"<<pBaseType->getURI());

	}; /* IF: has BaseType */

	DM::Type* pNewType= NULL;

	if(verfifyExisting(pBaseType, pTypeInfo)){

		pNewType = pTypeInfo->pType = getConvertedType(strTargetNamespace, pTypeInfo->strName);
		pTypeInfo->iStage=TypeInfo::STAGE_DEFINED;

	}else{

		pNewType = pTypeInfo->pType=pDataFactory->defineType(strTargetNamespace,
														   pTypeInfo->strName,
														   pBaseType);

		if(!(pTypeInfo->strDocumentation.empty())){
			pNewType->setDescription(pTypeInfo->strDocumentation);
		}

		if(pTypeInfo->iMaxLength != Type::CDftMaxLength)
			pNewType->setRestrictionMaxLength(pTypeInfo->iMaxLength);

		pTypeInfo->iStage=TypeInfo::STAGE_PROPERTIES;

		if(!bSkipProperties){
			createProperties(pTypeInfo);
			pTypeInfo->iStage=TypeInfo::STAGE_DEFINED;
		}

	}

	return pNewType;

}
/*************************************************************************/
void XSDParser::createProperties(TypeInfo* pTypeInfo){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pTypeInfo);
	IAS_CHECK_IF_NULL(pTypeInfo->pType);


	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),
			" Create properties for:"<<":"<<pTypeInfo->strName<<" "<<pTypeInfo->lstPropertyInfo.size());

	if(pTypeInfo->lstPropertyInfo.size() == 0)
		return;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),
			pTypeInfo->lstPropertyInfo[0]->strName);

	ComplexType* pComplexType = pTypeInfo->pType->asComplexType();

	for( PropertyList::iterator it = pTypeInfo->lstPropertyInfo.begin();
		  it != pTypeInfo->lstPropertyInfo.end();
		  it++){

		PropertyInfo* pPropertyInfo = *it;
		IAS_CHECK_IF_NULL(pPropertyInfo);

		if(pPropertyInfo->strTypeURI.compare(this->strTargetNamespace) == 0 &&
			hmTypeInfo.count(pPropertyInfo->strTypeName) > 0)
				defineType(hmTypeInfo[pPropertyInfo->strTypeName],true);


		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),
				"Property for:"<<":"<<pTypeInfo->strName<<" : "<<pPropertyInfo->strName<<" : "<<
						pPropertyInfo->strTypeURI << ":" << pPropertyInfo->strTypeName << ":" << pPropertyInfo->bIsMulti);

		DM::Type* pPropertyType = getConvertedType(pPropertyInfo->strTypeURI, pPropertyInfo->strTypeName);

		pComplexType->defineProperty(pPropertyInfo->strName,
									 pPropertyType,
									 pPropertyInfo->bIsMulti,
									 pPropertyInfo->bIsXMLAttribute,
									 pPropertyInfo->strDocumentation);
	}

}
/*************************************************************************/
void XSDParser::defineTypes(){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Define types for:"<<strTargetNamespace);

	for( TypeInfoMap::iterator it = hmTypeInfo.begin();
		  it != hmTypeInfo.end();
		  it++){

		TypeInfo* pTypeInfo = it->second;
		defineType(pTypeInfo);
	}
}
/*************************************************************************/
void XSDParser::defineTargetNSElements(){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Elements for:"<<strTargetNamespace);

	DM::Type* pElementsType = NULL;

	try{
		 pElementsType=pDataFactory->getType(strTargetNamespace,DM::DataFactory::RootTypeName);
	}catch(ItemNotFoundException& e){
		pElementsType=pDataFactory->defineType(strTargetNamespace,
											   DM::DataFactory::RootTypeName);
	}

	IAS_CHECK_IF_VALID(pElementsType);
	ComplexType* pComplexType = pElementsType->asComplexType();

	for( PropertyList::iterator it=lstTargetNSElements.begin();
		  it != lstTargetNSElements.end();
		  it++){

			PropertyInfo* pPropertyInfo = *it;

			DM::Type* pPropertyType = getConvertedType(pPropertyInfo->strTypeURI, pPropertyInfo->strTypeName);

			pComplexType->defineProperty(pPropertyInfo->strName,
										 pPropertyType,
										 false,false,
										 pPropertyInfo->strDocumentation);

		}
}
/*************************************************************************/
::IAS::DM::Type* XSDParser::getConvertedType(const String& strURI, const String& strName){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Convert:"<<strURI<<":"<<strName);

	if(!strURI.compare(StrXSDSchema)){

		if(!strName.compare("string")){
			return pDataFactory->getDefaultType(DM::Type::TextType);
		}else if(!strName.compare("int")){
			return pDataFactory->getDefaultType(DM::Type::IntegerType);
		}else if(!strName.compare("positiveInteger")){
			return pDataFactory->getDefaultType(DM::Type::IntegerType);
		}else if(!strName.compare("integer")){
			return pDataFactory->getDefaultType(DM::Type::IntegerType);
		}else if(!strName.compare("bool")){
			return pDataFactory->getDefaultType(DM::Type::BooleanType);
		}else if(!strName.compare("boolean")){
			return pDataFactory->getDefaultType(DM::Type::BooleanType);
		}else if(!strName.compare("float")){
			return pDataFactory->getDefaultType(DM::Type::FloatType);
		}else if(!strName.compare("dateTime")){
			return pDataFactory->getDefaultType(DM::Type::DateTimeType);
		}else if(!strName.compare("date")){
			return pDataFactory->getDefaultType(DM::Type::DateType);
		}else if(!strName.compare("time")){
			return pDataFactory->getDefaultType(DM::Type::TimeType);
		}else if(!strName.compare("anyType")){
			return pDataFactory->getDefaultType(DM::Type::AnyType);
		}

		return pDataFactory->getType(DataFactory::BuildInTypesNamespace,"String");

		//StringStream ssInfo;
		//ssInfo<<"Unknown/unregistered xsd type: "<<strURI<<":"<<strName;
		//IAS_THROW(XMLHelperException(ssInfo.str()));
	}

	return pDataFactory->getType(strURI, strName);
}
/*************************************************************************/
}
}
}
