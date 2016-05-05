/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Boolean.cpp
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
#include "../../../dm/Impl/default/Boolean.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Boolean* Boolean::duplicateBoolean() const{
   return Ext::BooleanType::FromDataObject(duplicate());
}
/*************************************************************************/
Boolean::Boolean(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectBoolean(pType){
	IAS_TRACER;
}
/*************************************************************************/
Boolean::~Boolean() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
BooleanList::BooleanList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void BooleanList::addDataObject(::IAS::DM::Default::Boolean* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void BooleanList::add(const bool aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
bool BooleanList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toBoolean();
}
/*************************************************************************/
int BooleanList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Boolean* BooleanList::getDataObject(int iIdx){
	return BooleanType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
BooleanType::BooleanType():
    ::IAS::DM::Impl::TypeBoolean(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Boolean", NULL){
	IAS_TRACER;
}
/*************************************************************************/
BooleanType::BooleanType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeBoolean(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
BooleanType::~BooleanType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* BooleanType::createDataObjectImpl() const{
	return createBooleanImpl();
}
/*************************************************************************/
Boolean* BooleanType::createBooleanImpl() const{
	IAS_TRACER;
	return DataAllocator<Boolean>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Boolean* BooleanType::createBoolean() const{
	IAS_TRACER;
	return createBooleanImpl();
}
/*************************************************************************/
::IAS::DM::Default::Boolean* BooleanType::createBoolean(const bool aValue) const{
	IAS_TRACER;
	DataAllocator<Boolean>::PtrHolder ptrTmp(createBooleanImpl());
	ptrTmp->setBoolean(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
Boolean* BooleanType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Boolean* >(pDataObject);
}
/*************************************************************************/
const Boolean* BooleanType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Boolean* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Boolean* BooleanType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Boolean*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Boolean* BooleanType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
