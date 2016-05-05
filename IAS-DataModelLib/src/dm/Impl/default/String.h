/*
 * File: IAS-DataModelLib/src/dm/Impl/default/String.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47String_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47String_46H

#include "../../../dm/default/String.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectString.h"
#include "../../../dm/Impl/TypeString.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class StringType; }
/*************************************************************************/
class String:
	public ::IAS::DM::Impl::DataObjectString,
	public virtual ::IAS::DM::Default::String{

public:

	virtual ~String() throw();

	virtual ::IAS::DM::Default::String* duplicateString() const;
protected:
	String(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<String>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<String>::RefCountingPtr StringPtr;
/*************************************************************************/
class StringList : public ::IAS::DM::Default::Ext::StringList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    StringList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::String* pValue);
	virtual ::IAS::DM::Default::String* getDataObject(int iIdx);

	virtual void add(const ::IAS::String& aValue);
	virtual ::IAS::String at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<StringList>;
};
/*************************************************************************/

 class StringType :
	public ::IAS::DM::Impl::TypeString,
	public virtual ::IAS::DM::Default::Ext::StringType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<StringType>, StringType >{

public:

	virtual ~StringType() throw();

	virtual ::IAS::DM::Default::String* createString() const;
	virtual ::IAS::DM::Default::String* createString(const ::IAS::String& aValue) const;

	virtual ::IAS::DM::Default::String* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::String* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static String* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const String* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	StringType();
	StringType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	String* createStringImpl() const;

	friend class ::IAS::Factory<StringType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
