/*
 * File: IAS-DataModelLib/src/dm/xml/XMLDocument.h
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
#ifndef _IAS_DM_XML_XMLDOCUMENT_H_
#define _IAS_DM_XML_XMLDOCUMENT_H_

#include <commonlib/commonlib.h>
#include "../../dm/DataObject.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
/** The class. */
 class XMLDocument {
public:

	virtual ~XMLDocument() throw();

	DataObject *getRootObject() const;

	void setRootObject(DataObject *pDataObject);

	void setVersion(const String& strVersion);
	void setEncoding(const String& strEncoding);

	void setURI(const String& strURI);
	void setElement(const String& strElement);

	inline const String& getVersion() const { return strVersion; };
	inline const String& getEncoding() const { return strEncoding; };
	inline const String& getElement() const { return strElement; };
	inline const String& getURI()const { return strURI; };

protected:
	XMLDocument(DataObject *pDataObject = NULL);

	DataObjectPtr ptrRootObject;

	String strEncoding;
	String strVersion;
	String strElement;
	String strURI;

	void setDefaultElement();

	friend class ::IAS::Factory<XMLDocument>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_XMLDOCUMENT_H_ */
