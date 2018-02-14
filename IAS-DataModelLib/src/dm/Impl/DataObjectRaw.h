/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectRaw.h
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
#ifndef _IAS_DM_Impl_DataObjectRaw_H_
#define _IAS_DM_Impl_DataObjectRaw_H_

#include "../../dm/Impl/DataObjectBasic.h"
#include "../../dm/Impl/MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {

class Type;

/*************************************************************************/
class DataObjectRaw :
	public ::IAS::DM::Impl::DataObjectBasic{
public:

	virtual ~DataObjectRaw() throw();

	virtual void setString(const ::IAS::String& strValue);
	virtual void setRaw(const RawContent* pRawContent);
	virtual void setDataObject(const IAS::DM::DataObject* pDataObject);

	virtual ::IAS::String toString()const;
	virtual void toRaw(RawContent* pRawContent)const;

	virtual bool    equals(const IAS::DM::DataObject* dmValue)const;

protected:
	DataObjectRaw(const Type *pType);

	DataAllocator<RawContent>::PtrHolder ptrRawContentValue;

	friend class ::IAS::Factory<DataObjectRaw>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAOBJECTSTRING_H_ */
