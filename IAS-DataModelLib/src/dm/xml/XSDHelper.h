/*
 * File: IAS-DataModelLib/src/dm/xml/XSDHelper.h
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
#ifndef _IAS_DM_XML_XSDHELPER_H_
#define _IAS_DM_XML_XSDHELPER_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
class DataFactory;
namespace XML {

class LibXMLLexer;
class XSDParser;

/*************************************************************************/
/** The class. */
 class XSDHelper {
public:

	virtual ~XSDHelper() throw();

	void defineTypesFromFile(const String& strFileName, const String& strTargetNamespace = "");
	void includeTypesFromFile(const String& strFileName, const String& strTargetNamespace);

protected:

	inline ::IAS::DM::DataFactory *getDataFactory() { return pDataFactory;};

	friend class XSDParser;

	bool fileLookup(const String& strFileName, const String& strTargetNamespace) const;
	void registerFile(const String& strFileName, const String& strTargetNamespace);

	XSDHelper(::IAS::DM::DataFactory *pDataFactory);
	String buildKey(const String& strFileName, const String& strTargetNamespace)const;

private:

	::IAS::DM::DataFactory *pDataFactory;
	std::map<String, int> hmLoadedFiles;

	friend class ::IAS::Factory<XSDHelper>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_XSDHELPER_H_ */
