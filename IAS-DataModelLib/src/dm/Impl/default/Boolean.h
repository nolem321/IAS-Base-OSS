/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Boolean.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Boolean_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Boolean_46H

#include "../../../dm/default/Boolean.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectBoolean.h"
#include "../../../dm/Impl/TypeBoolean.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class BooleanType; }
/*************************************************************************/
class Boolean:
	public ::IAS::DM::Impl::DataObjectBoolean,
	public virtual ::IAS::DM::Default::Boolean{

public:

	virtual ~Boolean() throw();

	virtual ::IAS::DM::Default::Boolean* duplicateBoolean() const;
protected:
	Boolean(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Boolean>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Boolean>::RefCountingPtr BooleanPtr;
/*************************************************************************/
class BooleanList : public ::IAS::DM::Default::Ext::BooleanList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    BooleanList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Boolean* pValue);
	virtual ::IAS::DM::Default::Boolean* getDataObject(int iIdx);

	virtual void add(const bool aValue);
	virtual bool at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<BooleanList>;
};
/*************************************************************************/

 class BooleanType :
	public ::IAS::DM::Impl::TypeBoolean,
	public virtual ::IAS::DM::Default::Ext::BooleanType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<BooleanType>, BooleanType >{

public:

	virtual ~BooleanType() throw();

	virtual ::IAS::DM::Default::Boolean* createBoolean() const;
	virtual ::IAS::DM::Default::Boolean* createBoolean(const bool aValue) const;

	virtual ::IAS::DM::Default::Boolean* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Boolean* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Boolean* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Boolean* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	BooleanType();
	BooleanType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Boolean* createBooleanImpl() const;

	friend class ::IAS::Factory<BooleanType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
