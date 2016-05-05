/*
 * File: IAS-DataModelLib/src/dm/Impl/default/String.cpp
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
#include "../../../dm/Impl/default/String.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::String* String::duplicateString() const{
   return Ext::StringType::FromDataObject(duplicate());
}
/*************************************************************************/
String::String(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectString(pType){
	IAS_TRACER;
}
/*************************************************************************/
String::~String() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
StringList::StringList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void StringList::addDataObject(::IAS::DM::Default::String* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void StringList::add(const ::IAS::String& aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
::IAS::String StringList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toString();
}
/*************************************************************************/
int StringList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::String* StringList::getDataObject(int iIdx){
	return StringType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
StringType::StringType():
    ::IAS::DM::Impl::TypeString(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "String", NULL){
	IAS_TRACER;
}
/*************************************************************************/
StringType::StringType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeString(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
StringType::~StringType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* StringType::createDataObjectImpl() const{
	return createStringImpl();
}
/*************************************************************************/
String* StringType::createStringImpl() const{
	IAS_TRACER;
	return DataAllocator<String>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::String* StringType::createString() const{
	IAS_TRACER;
	return createStringImpl();
}
/*************************************************************************/
::IAS::DM::Default::String* StringType::createString(const ::IAS::String& aValue) const{
	IAS_TRACER;
	DataAllocator<String>::PtrHolder ptrTmp(createStringImpl());
	ptrTmp->setString(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
String* StringType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< String* >(pDataObject);
}
/*************************************************************************/
const String* StringType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const String* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::String* StringType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::String*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::String* StringType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
