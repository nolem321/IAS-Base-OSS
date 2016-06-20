/*
 * File: IAS-DataModelLib/src/dm/Impl/DataFactory.cpp
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
#include "../../dm/Impl/DataFactory.h"

#include <commonlib/commonlib.h>

#include "../../dm/Impl/default/Boolean.h"
#include "../../dm/Impl/default/Date.h"
#include "../../dm/Impl/default/DateTime.h"
#include "../../dm/Impl/default/Float.h"
#include "../../dm/Impl/default/Integer.h"
#include "../../dm/Impl/default/String.h"
#include "../../dm/Impl/default/Time.h"
#include "../../dm/Impl/default/Raw.h"
#include "../../dm/Impl/MemoryManager.h"
#include "../../dm/Impl/Type.h"
#include "../../dm/Impl/TypeAny.h"
#include "../../dm/Impl/TypeList.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
const String DataFactory::BuildInTypesNamespace ="IAS/DM/Default";
const String DataFactory::RootTypeName ="RootType";
namespace Impl {


/*************************************************************************/
DataFactory::DataFactory(const DM::DataFactory* pParentFactory)
	:pParentFactory(pParentFactory){

	IAS_TRACER;


	ptrTypeList = ModelAllocator<TypeList>::Create();

	if(!pParentFactory) {

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Initialing");

		declareDefaultType(Impl::Default::Ext::BooleanType::GetInstance());
		declareDefaultType(Impl::Default::Ext::FloatType::GetInstance());
		declareDefaultType(Impl::Default::Ext::IntegerType::GetInstance());
		declareDefaultType(Impl::Default::Ext::StringType::GetInstance());
		declareDefaultType(Impl::Default::Ext::DateTimeType::GetInstance());
		declareDefaultType(Impl::Default::Ext::DateType::GetInstance());
		declareDefaultType(Impl::Default::Ext::TimeType::GetInstance());
		declareDefaultType(Impl::Default::Ext::RawType::GetInstance());
		declareDefaultType(Impl::TypeAny::GetInstance());

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Initialized:"<<(void*)this);
	}
}
/*************************************************************************/
DataFactory::~DataFactory() throw(){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"All types deleted automatically:"<<(void*)this);
}
/*************************************************************************/
::IAS::DM::Type* DataFactory::getType(const String& strURI, const String& strName) const {
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"GetType:"<<strURI<<":"<<strName);

	HashMapKey aKey(strURI, strName);

	TypesHashMap::const_iterator it=hmTypes.find(aKey);

	if(it == hmTypes.end()) {

		if(pParentFactory)
			return pParentFactory->getType(strURI,strName);

		StringStream ssInfo;
		ssInfo<<"Unknown type: "<<strURI<<":"<<strName;
		IAS_THROW(ItemNotFoundException(ssInfo.str()));
	}

	return it->second;

}
/*************************************************************************/
::IAS::DM::Type* DataFactory::defineType(const String& strURI,
											 const String& strName,
											 const ::IAS::DM::Type* pBaseType){
	IAS_TRACER

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"NewType:"<<strURI<<":"<<strName);

	HashMapKey aKey(strURI, strName);
	if(hmTypes.count(aKey) != 0){
		IAS_THROW(BadUsageException(strURI+"#"+strName+" <= defineType: Type already exists."));
	}

	Type::Types iType = Type::DataObjectType;

	if(pBaseType != NULL){
		IAS_CHECK_IF_VALID(pBaseType);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Base:"<<pBaseType->getURI()<<":"<<pBaseType->getName());
		iType=pBaseType->getTypeEnum();
	}

	ModelAllocator< ::IAS::DM::Type >::PtrHolder ptrType(Type::Create(strURI, strName, iType, pBaseType));

	declareUserType(aKey, ptrType);
	return ptrType.pass();
}

/*************************************************************************/
void DataFactory::storeType(const HashMapKey& aKey,
							   ::IAS::DM::Type* pType){
	IAS_TRACER

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Store:"<<pType->getFullName());
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Store:"<<(void*)pType);
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Store:"<<dynamic_cast<void*>(pType));

	if(hmTypes.count(aKey))
		IAS_THROW(BadUsageException("Type already defined: ")<<pType->getFullName());

	hmTypes[aKey]=pType;
	ptrTypeList->insert(pType);

}
/*************************************************************************/
::IAS::DM::Type* DataFactory::getDefaultType(IAS::DM::Type::Types iType) const{
	IAS_TRACER;

	if(pParentFactory)
		return pParentFactory->getDefaultType(iType);

	DefaultTypesMap::const_iterator it=mapDefaultTypes.find(iType);

	if(it == mapDefaultTypes.end()) {
		IAS_THROW(ItemNotFoundException("getBuildInType"));
	}

	return it->second;
}
/*************************************************************************/
const ::IAS::DM::TypeList& DataFactory::getTypes() const{
	return *ptrTypeList;
}
/*************************************************************************/
void DataFactory::declareUserType(const HashMapKey& aKey,::IAS::DM::Type* pType){
   IAS_TRACER;
   storeType(aKey, pType);
   phcTypes.addPointer(pType);
}
/*************************************************************************/
void DataFactory::declareDefaultType(::IAS::DM::Type* pType){
   IAS_TRACER;
   declareBuiltInType(pType);
   mapDefaultTypes[pType->getTypeEnum()]=pType;
}
/*************************************************************************/
void DataFactory::declareBuiltInType(::IAS::DM::Type* pType){
   IAS_TRACER;
   HashMapKey aKey(pType->getURI(), pType->getName());
   storeType(aKey, pType);
}
/*************************************************************************/
}
}
}
