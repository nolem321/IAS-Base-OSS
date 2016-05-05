/*
 * File: IAS-DataModelLib/src/dm/xml/XMLParser.h
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
#ifndef _IAS_DM_XML_XMLPARSER_H_
#define _IAS_DM_XML_XMLPARSER_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
class DataFactory;
class DataObject;

namespace XML {
class XMLHelper;
class LibXMLLexer;
class XMLDocument;

/*************************************************************************/
/** The class. */
 class XMLParser {
public:

	virtual ~XMLParser() throw();


	XMLDocument* parse();

protected:

	XMLParser(XMLHelper* pXMLHelper, LibXMLLexer *pLibXMLLexer);

	XMLHelper*   pXMLHelper;
	const DataFactory* pDataFactory;

	IAS_DFT_FACTORY< ::IAS::DM::XML::LibXMLLexer >::PtrHolder ptrLibXMLLexer;

	IAS_DFT_FACTORY< XMLDocument >::PtrHolder ptrXMLDocument;

	void parse_xml_element(DataObject *pParent);

	friend class ::IAS::Factory<XMLParser>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_XMLPARSER_H_ */
