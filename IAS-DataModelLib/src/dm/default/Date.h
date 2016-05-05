/*
 * File: IAS-DataModelLib/src/dm/default/Date.h
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
#ifndef _IAS_DM_Gen_Date_H_
#define _IAS_DM_Gen_Date_H_

#include <commonlib/commonlib.h>
#include <time.h>
#include "../../dm/DataObject.h"

namespace IAS{
namespace DM{
namespace Default{

class Date : public virtual ::IAS::DM::DataObject {
  public:
	virtual Date* duplicateDate() const = 0;
};

namespace Ext{

/*************************************************************************/
typedef Impl::ModelAllocator<Date>::RefCountingPtr DatePtr;
/*************************************************************************/
class DateList {
	public:
	virtual ~DateList(){};
	virtual void addDataObject(Date* pValue) = 0;
	virtual Date* getDataObject(int iIdx) = 0;
	virtual void add(IAS::Time aValue)=0;
	virtual IAS::Date at(int iIdx)const=0;
	virtual int size()const=0;
};
/*************************************************************************/
class DateType {
	public:
	virtual ~DateType(){};
	virtual Date* cast(::IAS::DM::DataObject* pDataObject) const = 0;
	virtual const Date* cast(const ::IAS::DM::DataObject* pDataObject) const = 0;

	virtual Date* createDate() const=0;
	virtual ::IAS::DM::Default::Date* createDate(const IAS::Date& aValue) const = 0;
};

}

}
}
}

#endif
