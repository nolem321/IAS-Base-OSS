/*
 * File: IAS-DataModelLib/src/dm/Impl/default/DateTime.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47DateTime_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47DateTime_46H

#include "../../../dm/default/DateTime.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectDateTime.h"
#include "../../../dm/Impl/TypeDateTime.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class DateTimeType; }
/*************************************************************************/
class DateTime:
	public ::IAS::DM::Impl::DataObjectDateTime,
	public virtual ::IAS::DM::Default::DateTime{

public:

	virtual ~DateTime() throw();

	virtual ::IAS::DM::Default::DateTime* duplicateDateTime() const;
protected:
	DateTime(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<DateTime>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<DateTime>::RefCountingPtr DateTimePtr;
/*************************************************************************/
class DateTimeList : public ::IAS::DM::Default::Ext::DateTimeList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    DateTimeList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::DateTime* pValue);
	virtual ::IAS::DM::Default::DateTime* getDataObject(int iIdx);

	virtual void add(const ::IAS::DateTime& aValue);
	virtual ::IAS::DateTime at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<DateTimeList>;
};
/*************************************************************************/

 class DateTimeType :
	public ::IAS::DM::Impl::TypeDateTime,
	public virtual ::IAS::DM::Default::Ext::DateTimeType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<DateTimeType>, DateTimeType >{

public:

	virtual ~DateTimeType() throw();

	virtual ::IAS::DM::Default::DateTime* createDateTime() const;
	virtual ::IAS::DM::Default::DateTime* createDateTime(const ::IAS::DateTime& aValue) const;

	virtual ::IAS::DM::Default::DateTime* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::DateTime* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static DateTime* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const DateTime* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	DateTimeType();
	DateTimeType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	DateTime* createDateTimeImpl() const;

	friend class ::IAS::Factory<DateTimeType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
