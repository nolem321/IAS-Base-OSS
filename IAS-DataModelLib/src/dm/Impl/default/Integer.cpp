/*
 * File: IAS-DataModelLib/src/dm/Impl/default/Integer.cpp
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
#include "../../../dm/Impl/default/Integer.h"

#include "../../../dm/Impl/DataFactory.h"
#include "../../../dm/Impl/exception/IllegalCastException.h"
#include "../MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {
namespace Default {

/*************************************************************************/
::IAS::DM::Default::Integer* Integer::duplicateInteger() const{
   return Ext::IntegerType::FromDataObject(duplicate());
}
/*************************************************************************/
Integer::Integer(const ::IAS::DM::Impl::Type* pType):
   Impl::DataObjectInteger(pType){
	IAS_TRACER;
}
/*************************************************************************/
Integer::~Integer() throw(){
}
/*************************************************************************/
namespace Ext{
/*************************************************************************/
IntegerList::IntegerList(::IAS::DM::DataObjectList& refList) throw():
	::IAS::DM::Gen::DataObjectListProxy(refList){};
/*************************************************************************/
void IntegerList::addDataObject(::IAS::DM::Default::Integer* pValue){
	refDataObjectList.add(pValue);
}
/*************************************************************************/
void IntegerList::add(const int aValue){
	IAS_TRACER;
	refDataObjectList.add(refDataObjectList.getType()->createDataObject(aValue));
}
/*************************************************************************/
int IntegerList::at(int iIdx)const{
	IAS_TRACER;
	return refDataObjectList.at(iIdx)->toInteger();
}
/*************************************************************************/
int IntegerList::size()const{
	IAS_TRACER;
	return refDataObjectList.size();
}
/*************************************************************************/
::IAS::DM::Default::Integer* IntegerList::getDataObject(int iIdx){
	return IntegerType::FromDataObject(refDataObjectList.at(iIdx));
}
/*************************************************************************/
/*************************************************************************/
IntegerType::IntegerType():
    ::IAS::DM::Impl::TypeInteger(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "Integer", NULL){
	IAS_TRACER;
}
/*************************************************************************/
IntegerType::IntegerType(const ::IAS::String& strURI, const ::IAS::String& strName,
			  	  	   const ::IAS::DM::Type    *pBaseType):
		  ::IAS::DM::Impl::TypeInteger(strURI,strName, pBaseType ? pBaseType :  (::IAS::DM::Type*)GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
IntegerType::~IntegerType() throw(){
}
/*************************************************************************/
::IAS::DM::Impl::DataObject* IntegerType::createDataObjectImpl() const{
	return createIntegerImpl();
}
/*************************************************************************/
Integer* IntegerType::createIntegerImpl() const{
	IAS_TRACER;
	return DataAllocator<Integer>::Create(this);
}
/*************************************************************************/
::IAS::DM::Default::Integer* IntegerType::createInteger() const{
	IAS_TRACER;
	return createIntegerImpl();
}
/*************************************************************************/
::IAS::DM::Default::Integer* IntegerType::createInteger(const int aValue) const{
	IAS_TRACER;
	DataAllocator<Integer>::PtrHolder ptrTmp(createIntegerImpl());
	ptrTmp->setInteger(aValue);
	return ptrTmp.pass();
}
/*************************************************************************/
Integer* IntegerType::FromDataObject(::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< Integer* >(pDataObject);
}
/*************************************************************************/
const Integer* IntegerType::FromDataObject(const ::IAS::DM::DataObject* pDataObject){
	return dynamic_cast< const Integer* >(pDataObject);
}
/*************************************************************************/
::IAS::DM::Default::Integer* IntegerType::cast(::IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::Default::Integer*>(cast(static_cast<const ::IAS::DM::DataObject*>(pDataObject)));
}
/*************************************************************************/
const ::IAS::DM::Default::Integer* IntegerType::cast(const ::IAS::DM::DataObject* pDataObject) const{
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
