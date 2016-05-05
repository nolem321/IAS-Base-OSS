/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Time.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Time_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Time_46H

#include "../../../dm/default/Time.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectTime.h"
#include "../../../dm/Impl/TypeTime.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class TimeType; }
/*************************************************************************/
class Time:
	public ::IAS::DM::Impl::DataObjectTime,
	public virtual ::IAS::DM::Default::Time{

public:

	virtual ~Time() throw();

	virtual ::IAS::DM::Default::Time* duplicateTime() const;
protected:
	Time(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Time>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Time>::RefCountingPtr TimePtr;
/*************************************************************************/
class TimeList : public ::IAS::DM::Default::Ext::TimeList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    TimeList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Time* pValue);
	virtual ::IAS::DM::Default::Time* getDataObject(int iIdx);

	virtual void add(const ::IAS::Time& aValue);
	virtual ::IAS::Time at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<TimeList>;
};
/*************************************************************************/

 class TimeType :
	public ::IAS::DM::Impl::TypeTime,
	public virtual ::IAS::DM::Default::Ext::TimeType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<TimeType>, TimeType >{

public:

	virtual ~TimeType() throw();

	virtual ::IAS::DM::Default::Time* createTime() const;
	virtual ::IAS::DM::Default::Time* createTime(const ::IAS::Time& aValue) const;

	virtual ::IAS::DM::Default::Time* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Time* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Time* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Time* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	TimeType();
	TimeType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Time* createTimeImpl() const;

	friend class ::IAS::Factory<TimeType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
