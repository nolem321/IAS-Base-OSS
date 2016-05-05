/*
 * File: IAS-DataModelLib/src/dm/xml/XSDParserForInclude.cpp
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
#include "../../dm/xml/XSDParserForInclude.h"
#include <commonlib/commonlib.h>

#include "../../dm/DataFactory.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Type.h"
#include "../../dm/xml/LibXMLLexer.h"
#include "../../dm/xml/LibXMLWrapper.h"
#include "../../dm/xml/XSDHelper.h"


namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
XSDParserForInclude::XSDParserForInclude(XSDHelper* pXSDHelper, LibXMLLexer *pLibXMLLexer, const String &strTargetNamespace):
		XSDParser(pXSDHelper, pLibXMLLexer){
	IAS_TRACER;
	this->strTargetNamespace=strTargetNamespace;
}
/*************************************************************************/
XSDParserForInclude::~XSDParserForInclude() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XSDParserForInclude::lookupURI(const String& strTypePrefix, String& strResult) {
	IAS_TRACER;

	//TODO check targetNamespace from XSD file

	if(strTypePrefix.empty())
		strResult = strTargetNamespace;
	ptrLibXMLLexer->lookupURI(strTypePrefix, strResult);
}
/*************************************************************************/
}
}
}
