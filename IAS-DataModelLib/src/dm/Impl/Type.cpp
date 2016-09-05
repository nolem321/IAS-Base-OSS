/*
 * File: IAS-DataModelLib/src/dm/Impl/Type.cpp
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
#include "../../dm/Impl/Type.h"
#include <commonlib/commonlib.h>
#include "DataObject.h"
#include "../../dm/Impl/DataFactory.h"
#include "../../dm/Impl/DataObject.h"
#include "../../dm/Impl/exception/NotFoundException.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Impl/MemoryManager.h"
#include "../../dm/Impl/Property.h"
#include "../../dm/Impl/TypeAny.h"
#include "../../dm/Impl/TypeBoolean.h"
#include "../../dm/Impl/TypeComplex.h"
#include "../../dm/Impl/TypeDate.h"
#include "../../dm/Impl/TypeDateTime.h"
#include "../../dm/Impl/TypeFloat.h"
#include "../../dm/Impl/TypeInteger.h"
#include "../../dm/Impl/TypeString.h"
#include "../../dm/Impl/TypeTime.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
Type::Type(const String& strURI,
		   const String& strName,
		   const ::IAS::DM::Type    *pBaseType):
    strURI(strURI),
    strName(strName),
	pBaseType(pBaseType),
	bIsNSElementsType(false),
	strDescription(""),
	iMaxLength(CDftMaxLength){

		IAS_TRACER;

		if(pBaseType != NULL)
			IAS_CHECK_IF_VALID(pBaseType);

}

/*************************************************************************/
Type::~Type() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const String Type::getName() const{
	return strName;
}
/*************************************************************************/
const String Type::getURI()  const{
	return strURI;
}
/*************************************************************************/
const String Type::getDescription()  const{
	return strDescription;
}
/*************************************************************************/
void Type::setDescription(const String& strDescription){
	this->strDescription=strDescription;
}
/*************************************************************************/
const String Type::getFullName()  const{
	String strResult(strURI.c_str());
	strResult+="#";
	strResult+=strName;
	return strResult;
}
/*************************************************************************/
bool Type::equals(const ::IAS::DM::Type* pType) const{
	return this == pType ||
			(strName.compare(pType->getName().c_str())==0 &&
			 strURI.compare(pType->getURI().c_str())==0 );
}
/*************************************************************************/
void Type::setRestrictionMaxLength(const Type::MaxLenghtType iMaxLength){
	this->iMaxLength = iMaxLength;
}
/*************************************************************************/
Type::MaxLenghtType Type::getRestrictionMaxLenght()const{
	return iMaxLength;
}
/*************************************************************************/
bool Type::isRootType() const{
	return pBaseType == NULL;
}
/*************************************************************************/
bool Type::isNSElementsType() const{
	IAS_TRACER;
	return bIsNSElementsType;
}
/*************************************************************************/
void Type::setIsNSElementsType(bool bIsNSElementsType){
	IAS_TRACER;
	this->bIsNSElementsType=bIsNSElementsType;
}
/*************************************************************************/
void Type::setBaseType(const ::IAS::DM::Type* pBaseType){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pBaseType);
	this->pBaseType = pBaseType;
}
/*************************************************************************/
const ::IAS::DM::Type* Type::getBaseType() const{
	if(pBaseType == NULL)
		IAS_THROW(NotFoundException("getBaseType"));
	return pBaseType;
}
/*************************************************************************/
bool Type::isAssignableTo(const ::IAS::DM::Type* pType) const{
	IAS_TRACER;

	if(pType == this)
		return true;

	if(pType->getTypeEnum() == AnyType)
		return true;

	if(pType->getName().compare(strName) == 0 &&
	   pType->getURI().compare(strURI) == 0)
		return true;

	if(pBaseType == NULL)
		return false;

	return pBaseType->isAssignableTo(pType);
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject() const{
	IAS_TRACER;
	return createDataObjectImpl();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(const char* sValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject:"<<sValue);
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setString(sValue);
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject:"<<(void*)ptrObj.getPointer());
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(const String& strValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject:"<<strValue);
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setString(strValue);
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(int iValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject: "<<iValue);
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setInteger(iValue);
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(bool  bValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject: "<<bValue);
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setBoolean(bValue);
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(Float fValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject: "<<fValue);
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setFloat(fValue);
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(const IAS::Time& tsValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject: "<<tsValue.toString());
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setTime(tsValue);
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(const IAS::Date& tsValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject: "<<tsValue.toString());
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setDate(tsValue);
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(const IAS::DateTime& tsValue) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject: "<<tsValue.toString());
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setDateTime(tsValue);
	return ptrObj.pass();
}
/*************************************************************************/
IAS::DM::DataObject* Type::createDataObject(const IAS::DM::DataObject* pDataObject) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject: "<<(void*)pDataObject);
	Type::PtrHolder ptrObj(createDataObjectImpl());
	ptrObj->setDataObject(pDataObject);
	return ptrObj.pass();
}
/*************************************************************************/
::IAS::DM::Type*  Type::Create(const String& strURI,
								const String& strName,
								::IAS::DM::Type::Types iType,
								const ::IAS::DM::Type    *pBaseType){
	IAS_TRACER;

	if(pBaseType != NULL &&
	   pBaseType->getTypeEnum() != iType){
		IAS_THROW(RuntimeException("Base type enum does not match."));
	}

	Allocator *pAllocator=MemoryManager::GetAllocatorForTypes();

	ModelAllocator<Type>::PtrHolder ptrNewType;
	switch(iType){

		case ::IAS::DM::Type::BooleanType:
			ptrNewType=ModelAllocator<TypeBoolean>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::IntegerType:
			ptrNewType=ModelAllocator<TypeInteger>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::TextType:
			ptrNewType=ModelAllocator<TypeString>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::FloatType:
			ptrNewType=ModelAllocator<TypeFloat>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::DateTimeType:
			ptrNewType=ModelAllocator<TypeDateTime>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::DateType:
			ptrNewType=ModelAllocator<TypeDate>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::TimeType:
			ptrNewType=ModelAllocator<TypeTime>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::DataObjectType:
			ptrNewType=ModelAllocator<TypeComplex>::Create(strURI, strName, pBaseType);
		break;
		case ::IAS::DM::Type::AnyType:
			ptrNewType=ModelAllocator<TypeAny>::Create(strURI, strName, pBaseType);
			break;

		default:
			StringStream ssText;
			ssText<<"Type::Create("<<iType<<")";
			IAS_THROW(ItemNotFoundException(ssText.str()));
			break;
	}

	return ptrNewType.pass();
}
/*************************************************************************/
}
}
}

