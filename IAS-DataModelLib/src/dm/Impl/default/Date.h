/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Date.h
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
#ifndef IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Date_46H
#define IAS_DM_AG_Impl_IMPL_47EXAMPLES_47ORG_47AKC_47Date_46H

#include "../../../dm/default/Date.h"

#include <commonlib/commonlib.h>
#include "../../../dm/gen/DataObjectList.h"
#include "../../../dm/Impl/DataObjectDate.h"
#include "../../../dm/Impl/TypeDate.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
namespace Ext{ class DateType; }
/*************************************************************************/
class Date:
	public ::IAS::DM::Impl::DataObjectDate,
	public virtual ::IAS::DM::Default::Date{

public:

	virtual ~Date() throw();

	virtual ::IAS::DM::Default::Date* duplicateDate() const;
protected:
	Date(const ::IAS::DM::Impl::Type* pType);

	friend class ::IAS::Factory<Date>;
};

namespace Ext{

/*************************************************************************/
typedef ModelAllocator<Date>::RefCountingPtr DatePtr;
/*************************************************************************/
class DateList : public ::IAS::DM::Default::Ext::DateList,
 public ::IAS::DM::Gen::DataObjectListProxy {
	public:
    DateList(::IAS::DM::DataObjectList& refList) throw();

	virtual void addDataObject(::IAS::DM::Default::Date* pValue);
	virtual ::IAS::DM::Default::Date* getDataObject(int iIdx);

	virtual void add(const ::IAS::Date& aValue);
	virtual ::IAS::Date at(int iIdx)const;
	virtual int size()const;

	friend class ::IAS::Factory<DateList>;
};
/*************************************************************************/

 class DateType :
	public ::IAS::DM::Impl::TypeDate,
	public virtual ::IAS::DM::Default::Ext::DateType,
	public IAS::InstanceFeatureWithFactory< IAS::DM::Impl::ModelAllocator<DateType>, DateType >{

public:

	virtual ~DateType() throw();

	virtual ::IAS::DM::Default::Date* createDate() const;
	virtual ::IAS::DM::Default::Date* createDate(const ::IAS::Date& aValue) const;

	virtual ::IAS::DM::Default::Date* cast(::IAS::DM::DataObject* pDataObject) const;
	virtual const ::IAS::DM::Default::Date* cast(const ::IAS::DM::DataObject* pDataObject) const;

	static Date* FromDataObject(::IAS::DM::DataObject* pDataObject);
	static const Date* FromDataObject(const ::IAS::DM::DataObject* pDataObject);

protected:

	DateType();
	DateType(const ::IAS::String& strURI, const ::IAS::String& strName,
			   const ::IAS::DM::Type    *pBaseType);

	virtual ::IAS::DM::Impl::DataObject* createDataObjectImpl() const;

	Date* createDateImpl() const;

	friend class ::IAS::Factory<DateType>;
};

/*************************************************************************/
}

}
}
} /* DM */
} /* IAS */
#endif
