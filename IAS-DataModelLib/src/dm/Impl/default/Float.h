/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Float.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Float_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Float_46H

#include "../../../dm/default/Float.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectFloat.h"
#include "../../../dm/Impl/TypeFloat.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class FloatType; }
/*************************************************************************/
class Float:
	public ::IAS::DM::Impl::DataObjectFloat,
	public virtual ::IAS::DM::Default::Float{

public:

	virtual ~Float() throw();

	virtual ::IAS::DM::Default::Float* duplicateFloat() const;
protected:
	Float(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Float>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Float>::RefCountingPtr FloatPtr;
/*************************************************************************/
class FloatList : public ::IAS::DM::Default::Ext::FloatList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    FloatList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Float* pValue);
	virtual ::IAS::DM::Default::Float* getDataObject(int iIdx);

	virtual void add(const ::IAS::Float aValue);
	virtual ::IAS::Float at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<FloatList>;
};
/*************************************************************************/

 class FloatType :
	public ::IAS::DM::Impl::TypeFloat,
	public virtual ::IAS::DM::Default::Ext::FloatType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<FloatType>, FloatType >{

public:

	virtual ~FloatType() throw();

	virtual ::IAS::DM::Default::Float* createFloat() const;
	virtual ::IAS::DM::Default::Float* createFloat(const ::IAS::Float aValue) const;

	virtual ::IAS::DM::Default::Float* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Float* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Float* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Float* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	FloatType();
	FloatType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Float* createFloatImpl() const;

	friend class ::IAS::Factory<FloatType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
