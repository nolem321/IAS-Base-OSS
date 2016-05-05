/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Date.cpp
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
#include "../../../dm/Impl/default/Date.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Date* Date::duplicateDate() const{
   return Ext::DateType::FromDataObject(duplicate());
}
/*************************************************************************/
Date::Date(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectDate(pType){
	IAS_TRACER;
}
/*************************************************************************/
Date::~Date() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
DateList::DateList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void DateList::addDataObject(::IAS::DM::Default::Date* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void DateList::add(const ::IAS::Date& aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
::IAS::Date DateList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toDate();
}
/*************************************************************************/
int DateList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Date* DateList::getDataObject(int iIdx){
	return DateType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
DateType::DateType():
    ::IAS::DM::Impl::TypeDate(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Date", NULL){
	IAS_TRACER;
}
/*************************************************************************/
DateType::DateType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeDate(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
DateType::~DateType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* DateType::createDataObjectImpl() const{
	return createDateImpl();
}
/*************************************************************************/
Date* DateType::createDateImpl() const{
	IAS_TRACER;
	return DataAllocator<Date>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Date* DateType::createDate() const{
	IAS_TRACER;
	return createDateImpl();
}
/*************************************************************************/
::IAS::DM::Default::Date* DateType::createDate(const ::IAS::Date& aValue) const{
	IAS_TRACER;
	DataAllocator<Date>::PtrHolder ptrTmp(createDateImpl());
	ptrTmp->setDate(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
Date* DateType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Date* >(pDataObject);
}
/*************************************************************************/
const Date* DateType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Date* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Date* DateType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Date*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Date* DateType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
