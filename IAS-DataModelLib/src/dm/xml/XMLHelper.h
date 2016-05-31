/*
 * File: IAS-DataModelLib/src/dm/xml/XMLHelper.h
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
#ifndef _IAS_DM_XML_XMLHELPER_H_
#define _IAS_DM_XML_XMLHELPER_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
class DataFactory;
class DataObject;
namespace XML {
class XMLDocument;

/*************************************************************************/
/** The class. */
 class XMLHelper {
public:

	virtual ~XMLHelper() throw();

	inline const ::IAS::DM::DataFactory *getDataFactory()const { return pDataFactory;};

	void save(const String& strFileName,
			   const ::IAS::DM::DataObject *pDataObject,
			   const String& strElement,
			   const String& strURI);

	void save(const String& strFileName,
			   const XMLDocument* pDocument);

	void save(String& strOutput,
			  const ::IAS::DM::DataObject *pDataObject,
			  const String& strElement,
			  const String& strURI);

	void save(String& strOutput,
			  const XMLDocument* pDocument);

	void save(std::ostream& osOutput,
			  const ::IAS::DM::DataObject *pDataObject,
			  const String& strElement,
			  const String& strURI);

	void save(std::ostream& osOutput,
			  const XMLDocument* pDocument);

	XMLDocument* readFile(const String& strFileName);
	XMLDocument* readString(const String& strXML);
	XMLDocument* readStream(std::istream& is);

	/*
	 * This one is not very efficient but convenient (e.g. for error handling).
	 */
	static String Stringify(const ::IAS::DM::DataFactory *pDataFactory,
							const ::IAS::DM::DataObject *pDataObject);

	inline bool isSkipNullElements()const{
		return bSkipNullElements;
	}

	inline bool isEmptyFirstNS()const{
		return bEmptyFirstNS;
	}

	void setEmptyFirstNS(bool bEmptyFirstNS);

	static const String XMLPayloadElement;

protected:
	XMLHelper(const ::IAS::DM::DataFactory *pDataFactory);

	const ::IAS::DM::DataFactory *pDataFactory;

	static const String CEnvNULLAction;
	static const String CEnvFirstNS;

	bool bSkipNullElements;
	bool bEmptyFirstNS;

	friend class ::IAS::Factory<XMLHelper>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_XMLHELPER_H_ */
