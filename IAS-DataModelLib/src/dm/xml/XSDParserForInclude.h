/*
 * File: IAS-DataModelLib/src/dm/xml/XSDParserForInclude.h
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
#ifndef _IAS_DM_XML_XSDParserForInclude_H_
#define _IAS_DM_XML_XSDParserForInclude_H_

#include <commonlib/commonlib.h>

#include "XSDParser.h"

namespace IAS {
namespace DM {
class Type;
class ComplexType;
class DataFactory;


namespace XML {

class XSDHelper;
class LibXMLLexer;

/*************************************************************************/
/** The class. */
 class XSDParserForInclude : public XSDParser{
public:

	virtual ~XSDParserForInclude() throw();

protected:

	XSDParserForInclude(XSDHelper* pXSDHelper, LibXMLLexer *pLibXMLLexer, const String &strTargetNamespace);

	virtual void lookupURI(const String& strTypePrefix, String& strResult);

	friend class ::IAS::Factory<XSDParserForInclude>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_XSDPARSER_H_ */
