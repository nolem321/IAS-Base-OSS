/*
 * File: IAS-DataModelLib/src/dm/Impl/PropertyList.h
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
#ifndef _IAS_DM_Impl_PROPERTYLIST_H_
#define _IAS_DM_Impl_PROPERTYLIST_H_

#include "../../dm/PropertyList.h"

#include <commonlib/commonlib.h>
#include <unordered_map>
#include "../../dm/Impl/MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
class PropertyList : public ::IAS::DM::PropertyList{
public:

	virtual ~PropertyList() throw();

	virtual ::IAS::DM::Property* getProperty(int iIdx)const;
	virtual ::IAS::DM::Property* getProperty(const String& strName)const;

	virtual void append(::IAS::DM::Property *pProperty);

	virtual int getSize() const;



protected:
	PropertyList();

	struct HashMapKey : public String{
		HashMapKey(const String& strValue);
		size_t iHash;
	};

	struct HashMapKeyHash{
		size_t operator()(const HashMapKey& k1) const;
	};

	struct HashMapKeyEq{
		bool operator()(const HashMapKey& k1, const HashMapKey& k2) const;
	};

	typedef ias_std_unordered_map<String,
							   ::IAS::DM::Property*,
							    HashMapKeyHash,
							    HashMapKeyEq,
							    ModelAllocator< ::IAS::DM::Property* >
	                         >TypesHashMap;

	TypesHashMap hmPropertiesByName;

	typedef std::vector< ::IAS::DM::Property*,
				 	   ModelAllocator< ::IAS::DM::Property* >
					   > PropertiesTab;

	PropertiesTab tabProperties;

	friend class ::IAS::Factory<PropertyList>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_PropertyList_H_ */
