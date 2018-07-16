/*
 * File: IAS-DataModelLib/src/dm/xml/XMLSerializer.h
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
#ifndef _IAS_DM_XML_XMLSERIALIZER_H_
#define _IAS_DM_XML_XMLSERIALIZER_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
class DataFactory;
class DataObject;
class Type;

namespace XML {
class XMLHelper;
class LibXMLWriter;
class XMLDocument;

/*************************************************************************/
/** The class. */
 class XMLSerializer {
public:

	virtual ~XMLSerializer() throw();

	void serialize(const XMLDocument* pDocument);

protected:
	XMLSerializer(const XMLHelper* pXMLHelper, LibXMLWriter *pWriter);

	LibXMLWriter *pWriter;

	DataObject *pRootObject;

	//TODO hash string map to commons !!
	typedef OrderedMapWithStringKey< String > URIMap;
	URIMap hmURI;
	int iCounter;

	const XMLHelper*   pXMLHelper;
	const DataFactory* pDataFactory;

	void addURI(const String& strURI);
	const String& getURIPrefix(const String& strURI);

	void computeURI(DataObject* pDataObject,
					  bool        bAddURI);

	void serializeElement(const DataObject* pDataObject,
							const String& strName,
							bool  bXSIType,
							const String& ="");

	void listURIs();

	friend class ::IAS::Factory<XMLSerializer>;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_XMLSERIALIZER_H_ */
