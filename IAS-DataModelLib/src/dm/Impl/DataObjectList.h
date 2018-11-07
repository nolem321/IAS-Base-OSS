/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectList.h
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
#ifndef _IAS_DM_Impl_DATAOBJECTLIST_H_
#define _IAS_DM_Impl_DATAOBJECTLIST_H_

#include "../../dm/DataObjectList.h"

#include "../../dm/Impl/DataObject.h"
#include "../../dm/Impl/MemoryManager.h"
#include "../../dm/Impl/TypeRefFeature.h"

#include "StringContent.h"

namespace IAS {
namespace DM {
namespace Impl {

class Type;

/*************************************************************************/
class DataObjectList :
	public RefCountingPointee,
	public ::IAS::DM::DataObjectList,
	protected TypeRefFeature {
public:

	virtual ~DataObjectList() throw();

	virtual int        size() const;
	virtual ::IAS::DM::DataObject* at(int iIdx);
	virtual const ::IAS::DM::DataObject* at(int iIdx)const;

	virtual void  remove(int iIdx);
	virtual void  clear();

	virtual void  add(::IAS::DM::DataObject* pDataObject);
	virtual void  set(int iIdx, ::IAS::DM::DataObject* pDataObject);

	virtual ::IAS::DM::DataObject* operator [](int iIdx);
	virtual const ::IAS::DM::DataObject* operator [](int iIdx) const;

	virtual const ::IAS::DM::Type*   getType() const;

	virtual void hashWith(const String& strXPath);
	virtual ::IAS::DM::DataObject* at(const ::IAS::DM::DataObject* pKey);
	virtual const ::IAS::DM::DataObject* at(const ::IAS::DM::DataObject* pKey) const;

protected:
	DataObjectList(const IAS::DM::Type *pType, 	IAS::DM::DataObject *pParent);

	typedef std::vector< ::IAS::DM::DataObjectPtr,
			DataAllocator< ::IAS::DM::DataObjectPtr >  >DataObjectVector;

	DataObjectVector lstDataObject;

	typedef HashMapWithStringKey<::IAS::DM::DataObject*> HashMap;

	struct Hash{
		StringContent strHashXPath;
		HashMap hmObjects;

		void insert(::IAS::DM::DataObject*);
		void remove(::IAS::DM::DataObject*);
		Hash();
		virtual ~Hash();
	};

	DataAllocator< Hash >::PtrHolder ptrHash;


	friend class ::IAS::Factory<DataObjectList>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAOBJECTLIST_H_ */
