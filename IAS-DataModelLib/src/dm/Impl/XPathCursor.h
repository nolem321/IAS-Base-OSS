/*
 * File: IAS-DataModelLib/src/dm/Impl/XPathCursor.h
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
#ifndef _IAS_DM_Impl_XPATHCURSOR_H_
#define _IAS_DM_Impl_XPATHCURSOR_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
class DataObject;
class Property;
namespace Impl {

/*************************************************************************/
class XPathCursor {
public:


	static ::IAS::DM::DataObject* GetLastChild(::IAS::DM::DataObject *pDataObject,
												   const String& strXPath);

	static const ::IAS::DM::DataObject* GetLastChild(const ::IAS::DM::DataObject *pDataObject,
													   const String& strXPath);


	static void FindLastParent(const ::IAS::DM::DataObject *pDataObject,
								  const String& strXPath,
								  const ::IAS::DM::DataObject*   &pParent,
								  const ::IAS::DM::Property* &pProperty);

	static void FindLastParent(const ::IAS::DM::DataObject *pDataObject,
							   const String& strXPath,
							   ::IAS::DM::DataObject*   &pParent,
							   const ::IAS::DM::Property* &pProperty);
protected:

	XPathCursor(const ::IAS::DM::DataObject *pDataObject, const String& strXPath)throw();
	virtual ~XPathCursor() throw();


	inline const String& getElement() const { return strElement; };
	inline int getElementIdx() const { return iIdx; };
	inline bool isList() const { return iIdx > 0; };

	bool extractElement();
	bool endOfXPath();
	::IAS::DM::Property* getElementProperty(); //TODO const ?
	void moveCurrentToElement();

	const ::IAS::DM::DataObject *getLastChild();

	void findLastParent(const ::IAS::DM::DataObject*   &pParent,
						  const ::IAS::DM::Property* &pProperty);


	String strElement;

	int    				iIdx;
	String::size_type   iLastIdx;

	const String& strXPath;
	const ::IAS::DM::DataObject *pDataObject;
	const ::IAS::DM::DataObject *pCurrent;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_XPATHCURSOR_H_ */
