/*
 * File: IAS-DataModelLib/src/dm/Impl/default/DateTime.cpp
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
#include "../../../dm/Impl/default/DateTime.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::DateTime* DateTime::duplicateDateTime() const{
   return Ext::DateTimeType::FromDataObject(duplicate());
}
/*************************************************************************/
DateTime::DateTime(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectDateTime(pType){
	IAS_TRACER;
}
/*************************************************************************/
DateTime::~DateTime() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
DateTimeList::DateTimeList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void DateTimeList::addDataObject(::IAS::DM::Default::DateTime* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void DateTimeList::add(const ::IAS::DateTime& aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
::IAS::DateTime DateTimeList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toDateTime();
}
/*************************************************************************/
int DateTimeList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::DateTime* DateTimeList::getDataObject(int iIdx){
	return DateTimeType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
DateTimeType::DateTimeType():
    ::IAS::DM::Impl::TypeDateTime(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "DateTime", NULL){
	IAS_TRACER;
}
/*************************************************************************/
DateTimeType::DateTimeType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeDateTime(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
DateTimeType::~DateTimeType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* DateTimeType::createDataObjectImpl() const{
	return createDateTimeImpl();
}
/*************************************************************************/
DateTime* DateTimeType::createDateTimeImpl() const{
	IAS_TRACER;
	return DataAllocator<DateTime>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::DateTime* DateTimeType::createDateTime() const{
	IAS_TRACER;
	return createDateTimeImpl();
}
/*************************************************************************/
::IAS::DM::Default::DateTime* DateTimeType::createDateTime(const ::IAS::DateTime& aValue) const{
	IAS_TRACER;
	DataAllocator<DateTime>::PtrHolder ptrTmp(createDateTimeImpl());
	ptrTmp->setDateTime(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
DateTime* DateTimeType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< DateTime* >(pDataObject);
}
/*************************************************************************/
const DateTime* DateTimeType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const DateTime* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::DateTime* DateTimeType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::DateTime*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::DateTime* DateTimeType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
