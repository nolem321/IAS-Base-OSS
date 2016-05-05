/*
 * File: IAS-DataModelLib/src/dm/default/String.h
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
#ifndef _IAS_DM_Gen_String_H_
#define _IAS_DM_Gen_String_H_

#include <commonlib/commonlib.h>
#include "../../dm/DataObject.h"

namespace IAS{
namespace DM{
namespace Default{

class String : public virtual ::IAS::DM::DataObject {
  public:
	virtual String* duplicateString() const = 0;
};

namespace Ext{

/*************************************************************************/
typedef Impl::ModelAllocator<String>::RefCountingPtr StringPtr;
/*************************************************************************/
class StringList {
	public:
	virtual ~StringList(){};
	virtual void addDataObject(String* pValue) = 0;
	virtual String* getDataObject(int iIdx) = 0;
	virtual void add(const ::IAS::String& aValue)=0;
	virtual ::IAS::String at(int iIdx)const=0;
	virtual int size()const=0;
};
/*************************************************************************/
class StringType {
	public:
	virtual ~StringType(){};
	virtual String* cast(::IAS::DM::DataObject* pDataObject) const = 0;
	virtual const String* cast(const ::IAS::DM::DataObject* pDataObject) const = 0;

	virtual String* createString() const=0;
	virtual ::IAS::DM::Default::String* createString(const ::IAS::String& aValue) const = 0;
};

}

}
}
}

#endif
