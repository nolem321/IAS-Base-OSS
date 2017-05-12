/*
 * File: IAS-DataModelLib/src/dm/Impl/DataFactory.h
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
#ifndef _IAS_DM_Impl_DATAFACTORY_H_
#define _IAS_DM_Impl_DATAFACTORY_H_

#include "../../dm/DataFactory.h"
#include <unordered_map>

#include "../../dm/Impl/MemoryManager.h"
namespace IAS {
namespace DM {
namespace Impl {

class Type;
class TypeList;

/*************************************************************************/
class DataFactory :
	public virtual ::IAS::DM::DataFactory{

public:

	virtual ~DataFactory() throw();

	virtual ::IAS::DM::Type* getType(const String& strURI, const String& strName) const ;

	virtual ::IAS::DM::Type* defineType(const String& strURI,
										   const String& strName,
										   const ::IAS::DM::Type* pBaseType);

	virtual ::IAS::DM::Type* getDefaultType(IAS::DM::Type::Types iType) const;

	virtual const ::IAS::DM::TypeList& getTypes() const;

protected:

	DataFactory(const DM::DataFactory* pParentFactory = NULL);


	typedef _HashMapStringPairKey HashMapKey;

	typedef ::IAS::HashMap< HashMapKey,
							::IAS::DM::Type*,
							_Hash<HashMapKey>,
							_EqualsTo<_HashMapStringPairKey>,
							 ModelAllocator<std::pair<const HashMapKey, ::IAS::DM::Type*> >  > TypesHashMap;

	TypesHashMap hmTypes;
	ModelAllocator< ::IAS::DM::Type >::PtrHoldersCollection phcTypes;

	typedef std::map<int, ::IAS::DM::Type* > DefaultTypesMap;
	DefaultTypesMap mapDefaultTypes;

	ModelAllocator< TypeList >::PtrHolder   ptrTypeList;

	void storeType(const HashMapKey& aKey, ::IAS::DM::Type* pType);

	void declareUserType(const HashMapKey& aKey, ::IAS::DM::Type* pType);
	void declareXSDType(::IAS::DM::Type* pType, const String& strXSDType);

	void declareDefaultType(::IAS::DM::Type* pType);
	void declareBuiltInType(::IAS::DM::Type* pType);

	const DM::DataFactory* pParentFactory;

	friend class ::IAS::Factory<DataFactory>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAFACTORY_H_ */
