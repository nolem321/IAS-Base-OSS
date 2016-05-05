/*
 * File: IAS-DataModelLib/src/dm/default/Integer.h
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
#ifndef _IAS_DM_Gen_Integer_H_
#define _IAS_DM_Gen_Integer_H_

#include <commonlib/commonlib.h>
#include "../../dm/DataObject.h"

namespace IAS{
namespace DM{
namespace Default{

class Integer : public virtual ::IAS::DM::DataObject {
  public:
	virtual Integer* duplicateInteger() const = 0;
};

namespace Ext{

/*************************************************************************/
typedef Impl::ModelAllocator<Integer>::RefCountingPtr IntegerPtr;
/*************************************************************************/
class IntegerList {
	public:
	virtual ~IntegerList(){};
	virtual void addDataObject(Integer* pValue) = 0;
	virtual Integer* getDataObject(int iIdx) = 0;
	virtual void add(int aValue)=0;
	virtual int at(int iIdx)const=0;
	virtual int size()const=0;
};
/*************************************************************************/
class IntegerType {
	public:
	virtual ~IntegerType(){};
	virtual Integer* cast(::IAS::DM::DataObject* pDataObject) const = 0;
	virtual const Integer* cast(const ::IAS::DM::DataObject* pDataObject) const = 0;

	virtual Integer* createInteger() const=0;
	virtual ::IAS::DM::Default::Integer* createInteger(int aValue) const = 0;
};

}

}
}
}

#endif
