/*
 * File: IAS-DataModelLib/src/dm/xml/XSDParser.h
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
#ifndef _IAS_DM_XML_XSDPARSER_H_
#define _IAS_DM_XML_XSDPARSER_H_

#include <commonlib/commonlib.h>

#include "../Type.h"

namespace IAS {
namespace DM {
class ComplexType;
class DataFactory;


namespace XML {

class XSDHelper;
class LibXMLLexer;

/*************************************************************************/
/** The class. */
 class XSDParser {
public:

	virtual ~XSDParser() throw();

	void parse();
	void define();
	void setWorkingDir(const String& strDir);

	const String& getTargetNamespace()const;

	static const String StrXSDSchema;

protected:

	XSDParser(XSDHelper* pXSDHelper, LibXMLLexer *pLibXMLLexer);

	void parse_xsd_element();
	void parse_xsd_complexTypeElement();
	void parse_xsd_include();
	void parse_xsd_import();
	void parse_xsd_sequence();
	void parse_xsd_choice();
	void parse_xsd_all();
	void parse_xsd_complexType(const String& strName);
	void parse_xsd_complexType();
	void parse_xsd_complexTypeAttribute();
	void parse_xsd_simpleType();
	void parse_xsd_simpleType(const String& strName);
	void parse_xsd_complexContent();
	void parse_xsd_simpleContent();
	void parse_xsd_extension(bool bComplexType);
	void parse_xsd_restriction();
	void parse_xsd_maxLength();
	void parse_xsd_schema();
	void parse_xsd_schemaAttribute();
	String parse_xsd_annotation();
	String parse_xsd_documentation();

	IAS_DFT_FACTORY< ::IAS::DM::XML::LibXMLLexer >::PtrHolder ptrLibXMLLexer;

	String strTargetNamespace;

	XSDHelper*   pXSDHelper;
	DataFactory* pDataFactory;

	String strWorkingDir;

	struct PropertyInfo{
		String strName;
		String strTypeURI;
		String strTypeName;
		bool bIsMulti;
		bool bIsXMLAttribute;
		String strDocumentation;
	public:
		PropertyInfo()throw();
		virtual ~PropertyInfo(){};
		void init();
	};


	PropertyInfo* readPropertyInfo(bool bCheckMulti=false);

	typedef PtrVector<PropertyInfo> PropertyList;

	PropertyList lstTargetNSElements;

	struct TypeInfo{

		enum Stage{
			STAGE_NONE,
			STAGE_DEFINE,
			STAGE_PROPERTIES,
			STAGE_DEFINED,
		};

		virtual ~TypeInfo(){};
		TypeInfo() throw():pType(NULL),iStage(STAGE_NONE),iMaxLength(Type::CDftMaxLength){};

		String strName;
		String strBaseTypeURI;
		String strBaseTypeName;
		String strDocumentation;

		PropertyList lstPropertyInfo;

		Type* pType;
		Stage iStage;

		Type::MaxLenghtType iMaxLength;
		void init();
	};

	typedef HashMapStringToPointer<TypeInfo> TypeInfoMap;
	TypeInfoMap hmTypeInfo;

	void popCurrentType();
	void pushCurrentType(TypeInfo* pTypeInfo);
	TypeInfo* getCurrentType();

	typedef std::stack<TypeInfo*> TypeInfoStack;

	TypeInfoStack stackTypeInfo;
	unsigned int  iInlineCount;

	DM::Type* defineType(TypeInfo* pTypeInfo, bool bSkipProperties = false);
	void createProperties(TypeInfo* pTypeInfo);
	void defineTypes();
	void defineTargetNSElements();

	::IAS::DM::Type* getConvertedType(const String& strURI, const String& strName);

	virtual void lookupURI(const String& strTypePrefix, String& strResult);
	void updateInlineTypeName(PropertyInfo* pPropertyInfo);
	bool verfifyExisting(const ::IAS::DM::Type* pBaseType, TypeInfo* pTypeInfo);


	friend class ::IAS::Factory<XSDParser>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_XSDPARSER_H_ */
