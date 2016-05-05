/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Time.cpp
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
#include "../../../dm/Impl/default/Time.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Time* Time::duplicateTime() const{
   return Ext::TimeType::FromDataObject(duplicate());
}
/*************************************************************************/
Time::Time(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectTime(pType){
	IAS_TRACER;
}
/*************************************************************************/
Time::~Time() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
TimeList::TimeList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void TimeList::addDataObject(::IAS::DM::Default::Time* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void TimeList::add(const ::IAS::Time& aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
::IAS::Time TimeList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toTime();
}
/*************************************************************************/
int TimeList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Time* TimeList::getDataObject(int iIdx){
	return TimeType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
TimeType::TimeType():
    ::IAS::DM::Impl::TypeTime(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Time", NULL){
	IAS_TRACER;
}
/*************************************************************************/
TimeType::TimeType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeTime(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
TimeType::~TimeType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* TimeType::createDataObjectImpl() const{
	return createTimeImpl();
}
/*************************************************************************/
Time* TimeType::createTimeImpl() const{
	IAS_TRACER;
	return DataAllocator<Time>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Time* TimeType::createTime() const{
	IAS_TRACER;
	return createTimeImpl();
}
/*************************************************************************/
::IAS::DM::Default::Time* TimeType::createTime(const ::IAS::Time& aValue) const{
	IAS_TRACER;
	DataAllocator<Time>::PtrHolder ptrTmp(createTimeImpl());
	ptrTmp->setTime(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
Time* TimeType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Time* >(pDataObject);
}
/*************************************************************************/
const Time* TimeType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Time* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Time* TimeType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Time*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Time* TimeType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
