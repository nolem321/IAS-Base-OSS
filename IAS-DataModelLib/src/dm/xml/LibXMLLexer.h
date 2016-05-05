/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLLexer.h
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
#ifndef _IAS_DM_XML_LibXMLLexer_H_
#define _IAS_DM_XML_LibXMLLexer_H_

#include <commonlib/commonlib.h>

#include <libxml/xmlreader.h>

#include "../../dm/xml/exception/XMLHelperException.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
/** The class. */
 class LibXMLLexer {
public:

	virtual ~LibXMLLexer() throw();

	virtual bool nextElement();
	virtual bool nextAttribute();
	virtual bool moveToAttribute(const String& strAttrName);
	virtual bool moveToAttribute(int iIdx);

	inline int getType()      const { return xmlTextReaderNodeType(pXMLTextReader); };

	inline const char* getName()      const { return returnIfNotNull(xmlTextReaderConstName(pXMLTextReader)); };
	inline const char* getLocalName() const { return returnIfNotNull(xmlTextReaderConstLocalName(pXMLTextReader)); };
	inline const char* getPrefix()    const { return returnIfNotNull(xmlTextReaderConstPrefix(pXMLTextReader)); };
	inline const char* getValue()     const { return returnIfNotNull(xmlTextReaderConstValue(pXMLTextReader)); };

	inline void lookupURI(const String& strURI, String& strOutput) const{

		xmlChar *sValue =
				xmlTextReaderLookupNamespace(pXMLTextReader,
						strURI.empty() ? NULL : (const xmlChar*)(strURI.c_str()));

		if(sValue == NULL)
		    	IAS_THROW(XMLHelperException(String("NULL value returned from a lookup of: [")+strURI+"]"));

		strOutput=(const char*)sValue;
		xmlFree(sValue);
	};

	inline bool hasAttributes()     const { return xmlTextReaderHasAttributes(pXMLTextReader); };
	inline bool hasValue()          const { return xmlTextReaderHasValue(pXMLTextReader); };

	bool isEmpty();

	inline int getAttributeCount()          const { return xmlTextReaderAttributeCount(pXMLTextReader); };

	void setSkipSignificantWhiteSpaces(bool bSkipSignificantWhiteSpaces);

	inline bool checkName(const String& strName) const { return strName.compare(getName()) == 0; };
	inline bool checkLocalName(const String& strName) const { return strName.compare(getLocalName()) == 0; };
	inline bool checkType(int iType) const { return getType() == iType; };

	const char* getMandatoryAttribute(const String& strName) ;
	bool getOptionalAttribute(const String& strName,String& strValue) ;

	void getPrefixWithURI(String& strPrefix, String& strURI);

	static void ChopOffPrefix(const String& strValue, String &strPrefix, String& strBaseValue);

protected:
	LibXMLLexer();

	void onError	(const char * sMsg,
					 xmlParserSeverities severity,
					 xmlTextReaderLocatorPtr locator);


	static void _libxml_onError	(void* pArg,
								     const char * sMsg,
								     xmlParserSeverities severity,
							         xmlTextReaderLocatorPtr locator);

	String strFileName;
    xmlTextReaderPtr pXMLTextReader;
    int iXMLRetCode;

    String strError;


    void processNode();
    bool bReadingAttributes;

    bool bSkipSignificantWhiteSpaces;

    inline const char* returnIfNotNull(const xmlChar* sValue) const {
    	const char* s = (const char *)sValue;

    	if(s == NULL)
    		IAS_THROW(XMLHelperException(String("NULL value returned !")));

    	return s;
    }

    void setup(xmlTextReaderPtr pXMLTextReader);

    friend class ::IAS::Factory<LibXMLLexer>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_LEXER_H_ */
