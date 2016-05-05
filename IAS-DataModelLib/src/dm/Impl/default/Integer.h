/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Integer.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Integer_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Integer_46H

#include "../../../dm/default/Integer.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectInteger.h"
#include "../../../dm/Impl/TypeInteger.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class IntegerType; }
/*************************************************************************/
class Integer:
	public ::IAS::DM::Impl::DataObjectInteger,
	public virtual ::IAS::DM::Default::Integer{

public:

	virtual ~Integer() throw();

	virtual ::IAS::DM::Default::Integer* duplicateInteger() const;
protected:
	Integer(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Integer>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Integer>::RefCountingPtr IntegerPtr;
/*************************************************************************/
class IntegerList : public ::IAS::DM::Default::Ext::IntegerList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    IntegerList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Integer* pValue);
	virtual ::IAS::DM::Default::Integer* getDataObject(int iIdx);

	virtual void add(const int aValue);
	virtual int at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<IntegerList>;
};
/*************************************************************************/

 class IntegerType :
	public ::IAS::DM::Impl::TypeInteger,
	public virtual ::IAS::DM::Default::Ext::IntegerType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<IntegerType>, IntegerType >{

public:

	virtual ~IntegerType() throw();

	virtual ::IAS::DM::Default::Integer* createInteger() const;
	virtual ::IAS::DM::Default::Integer* createInteger(const int aValue) const;

	virtual ::IAS::DM::Default::Integer* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Integer* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Integer* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Integer* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	IntegerType();
	IntegerType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Integer* createIntegerImpl() const;

	friend class ::IAS::Factory<IntegerType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
