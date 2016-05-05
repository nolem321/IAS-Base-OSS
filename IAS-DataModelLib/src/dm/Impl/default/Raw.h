/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Raw.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Raw_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Raw_46H

#include "../../../dm/default/Raw.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectRaw.h"
#include "../../../dm/Impl/TypeRaw.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class RawType; }
/*************************************************************************/
class Raw:
	public ::IAS::DM::Impl::DataObjectRaw,
	public virtual ::IAS::DM::Default::Raw{

public:

	virtual ~Raw() throw();

	virtual ::IAS::DM::Default::Raw* duplicateRaw() const;
protected:
	Raw(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Raw>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Raw>::RefCountingPtr RawPtr;
/*************************************************************************/
class RawList : public ::IAS::DM::Default::Ext::RawList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    RawList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Raw* pValue);
	virtual ::IAS::DM::Default::Raw* getDataObject(int iIdx);

	virtual void add(const RawContent* pRawContent);
	virtual void at(int iIdx, RawContent* pRawContent)const;
	virtual int size()const;

	friend class ::IAS::Factory<RawList>;
};
/*************************************************************************/

 class RawType :
	public ::IAS::DM::Impl::TypeRaw,
	public virtual ::IAS::DM::Default::Ext::RawType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<RawType>, RawType >{

public:

	virtual ~RawType() throw();

	virtual ::IAS::DM::Default::Raw* createRaw() const;
	virtual ::IAS::DM::Default::Raw* createRaw(const RawContent* pRawContent) const;

	virtual ::IAS::DM::Default::Raw* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Raw* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Raw* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Raw* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	RawType();
	RawType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Raw* createRawImpl() const;

	friend class ::IAS::Factory<RawType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
