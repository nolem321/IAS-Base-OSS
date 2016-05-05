/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWriter.h
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
#ifndef _IAS_DM_XML_LIBXMLWRITER_H_
#define _IAS_DM_XML_LIBXMLWRITER_H_

#include <commonlib/commonlib.h>
#include <libxml/xmlwriter.h>

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
/** The class. */
 class LibXMLWriter {
public:

	virtual ~LibXMLWriter() throw();

	void startDocument(const String& strVersion, const String& strEncoding);
	void endDocument();

	void startElement(const String& strElement);

	void startElementNS(const String& strPrefix,
						  const String& strElement,
						  const String& strURI = "");

	void endElement();

	void writeElement(const String& strName,
						const String& strValue);

	void writeElementNS(const String& strPrefix,
						  const String& strElement,
						  const String& strValue,
						  const String& strURI);


	void writeAttribute(const String& strName,
						  const String& strValue);

	void writeAttributeNS(const String& strPrefix,
						    const String& strName,
						    const String& strValue,
						    const String& strURI);

	void writeString(const String& strValue);
protected:
	LibXMLWriter()throw();
	void init(xmlTextWriterPtr pXMLTextWriter);

	xmlTextWriterPtr pXMLTextWriter;

	void cleanUp();
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_LIBXMLWRITER_H_ */
