/*
 * File: IAS-DataModelLib/src/dm/PropertyList.h
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
#ifndef _IAS_DM_PROPERTYLIST_H_
#define _IAS_DM_PROPERTYLIST_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {

class Property;

/*************************************************************************/
/** The class. */
 class PropertyList {
public:

	virtual ~PropertyList() throw(){};

	virtual ::IAS::DM::Property* getProperty(int iIdx)const=0;
	virtual ::IAS::DM::Property* getProperty(const String& strName)const=0;
	virtual int getSize() const = 0;

	inline const ::IAS::DM::Property* operator[] (unsigned int iIdx) const { return getProperty(iIdx);};
};

/*************************************************************************/
}
}

#endif /* _IAS_DM_PropertyList_H_ */
