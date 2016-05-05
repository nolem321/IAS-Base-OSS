/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Raw.cpp
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
#include "../../../dm/Impl/default/Raw.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Raw* Raw::duplicateRaw() const{
   return Ext::RawType::FromDataObject(duplicate());
}
/*************************************************************************/
Raw::Raw(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectRaw(pType){
	IAS_TRACER;
}
/*************************************************************************/
Raw::~Raw() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
RawList::RawList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void RawList::addDataObject(::IAS::DM::Default::Raw* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void RawList::add(const RawContent* pRawContent){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(pRawContent));
}
/*************************************************************************/
void RawList::at(int iIdx, RawContent* pRawContent)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toRaw(pRawContent);
}
/*************************************************************************/
int RawList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Raw* RawList::getDataObject(int iIdx){
	return RawType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
RawType::RawType():
    ::IAS::DM::Impl::TypeRaw(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Raw", NULL){
	IAS_TRACER;
}
/*************************************************************************/
RawType::RawType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeRaw(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
RawType::~RawType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* RawType::createDataObjectImpl() const{
	return createRawImpl();
}
/*************************************************************************/
Raw* RawType::createRawImpl() const{
	IAS_TRACER;
	return DataAllocator<Raw>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Raw* RawType::createRaw() const{
	IAS_TRACER;
	return createRawImpl();
}
/*************************************************************************/
::IAS::DM::Default::Raw* RawType::createRaw(const RawContent* pRawContent) const{
	IAS_TRACER;
	DataAllocator<Raw>::PtrHolder ptrTmp(createRawImpl());
	ptrTmp->setRaw(pRawContent);
	return ptrTmp.pass();
}
/*************************************************************************/
Raw* RawType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Raw* >(pDataObject);
}
/*************************************************************************/
const Raw* RawType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Raw* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Raw* RawType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Raw*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Raw* RawType::cast(const ::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataObject);
	if(pDataObject->getType()->isAssignableTo(this)){
		return FromDataObject(pDataObject);
	}

	IAS_THROW(IllegalCastException(pDataObject->getType(), this));
}
/*************************************************************************/
}
}
}
} /* DM */
} /* IAS */
