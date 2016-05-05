/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Float.cpp
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
#include "../../../dm/Impl/default/Float.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Float* Float::duplicateFloat() const{
   return Ext::FloatType::FromDataObject(duplicate());
}
/*************************************************************************/
Float::Float(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectFloat(pType){
	IAS_TRACER;
}
/*************************************************************************/
Float::~Float() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
FloatList::FloatList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void FloatList::addDataObject(::IAS::DM::Default::Float* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void FloatList::add(const ::IAS::Float aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
::IAS::Float FloatList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toFloat();
}
/*************************************************************************/
int FloatList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Float* FloatList::getDataObject(int iIdx){
	return FloatType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
FloatType::FloatType():
    ::IAS::DM::Impl::TypeFloat(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Float", NULL){
	IAS_TRACER;
}
/*************************************************************************/
FloatType::FloatType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeFloat(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
FloatType::~FloatType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* FloatType::createDataObjectImpl() const{
	return createFloatImpl();
}
/*************************************************************************/
Float* FloatType::createFloatImpl() const{
	IAS_TRACER;
	return DataAllocator<Float>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Float* FloatType::createFloat() const{
	IAS_TRACER;
	return createFloatImpl();
}
/*************************************************************************/
::IAS::DM::Default::Float* FloatType::createFloat(const ::IAS::Float aValue) const{
	IAS_TRACER;
	DataAllocator<Float>::PtrHolder ptrTmp(createFloatImpl());
	ptrTmp->setFloat(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
Float* FloatType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Float* >(pDataObject);
}
/*************************************************************************/
const Float* FloatType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Float* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Float* FloatType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Float*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Float* FloatType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
