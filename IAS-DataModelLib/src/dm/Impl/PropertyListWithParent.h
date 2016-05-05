/*
 * File: IAS-DataModelLib/src/dm/Impl/PropertyListWithParent.h
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
#ifndef _IAS_DM_Impl_PropertyListWithParent_H_
#define _IAS_DM_Impl_PropertyListWithParent_H_

#include <unordered_map>
#include "../../dm/Impl/PropertyList.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
class PropertyListWithParent : public ::IAS::DM::Impl::PropertyList{
public:

	virtual ~PropertyListWithParent() throw();

	virtual ::IAS::DM::Property* getProperty(int iIdx)const;
	virtual ::IAS::DM::Property* getProperty(const String& strName)const;

	virtual int getSize() const;

protected:

	PropertyListWithParent(const ::IAS::DM::PropertyList *pParent);

	int iParentSize;
	const ::IAS::DM::PropertyList *pParent;

	friend class ::IAS::Factory<PropertyListWithParent>;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_PropertyListWithParent_H_ */
