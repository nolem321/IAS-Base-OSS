/*
 * File: IAS-DataModelLib/src/dm/default/Raw.h
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
#ifndef _IAS_DM_Gen_Raw_H_
#define _IAS_DM_Gen_Raw_H_

#include <commonlib/commonlib.h>
#include "../../dm/DataObject.h"

namespace IAS{
namespace DM{
namespace Default{

class Raw : public virtual ::IAS::DM::DataObject {
  public:
	virtual Raw* duplicateRaw() const = 0;
};

namespace Ext{

/*************************************************************************/
typedef Impl::ModelAllocator<Raw>::RefCountingPtr RawPtr;
/*************************************************************************/
class RawList {
	public:
	virtual ~RawList(){};
	virtual void addDataObject(Raw* pValue) = 0;
	virtual Raw* getDataObject(int iIdx) = 0;
	virtual void add(const RawContent* pRawContent)=0;
	virtual void at(int iIdx, RawContent* pRawContent)const=0;
	virtual int size()const=0;
};
/*************************************************************************/
class RawType {
	public:
	virtual ~RawType(){};
	virtual Raw* cast(::IAS::DM::DataObject* pDataObject) const = 0;
	virtual const Raw* cast(const ::IAS::DM::DataObject* pDataObject) const = 0;

	virtual Raw* createRaw() const=0;
	virtual ::IAS::DM::Default::Raw* createRaw(const RawContent* pRawContent) const = 0;
};

}

}
}
}

#endif
