/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeComplex.cpp
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
#include "../../dm/Impl/TypeComplex.h"
#include <commonlib/commonlib.h>
#include "exception/RuntimeException.h"

#include "../../dm/Impl/DataFactory.h"
#include "../../dm/Impl/DataObjectComplex.h"
#include "../../dm/Impl/DataObjectList.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Impl/MemoryManager.h"
#include "../../dm/Impl/Property.h"
#include "../../dm/Impl/PropertyList.h"
#include "../../dm/Impl/PropertyListWithParent.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
TypeComplex::TypeComplex(const String& strURI,
						const String& strName,
						const ::IAS::DM::Type *pBaseType):
Type(strURI, strName, pBaseType)
{
	IAS_TRACER;

	setIsNSElementsType(strName.compare(DataFactory::RootTypeName) == 0);

	if(pBaseType == NULL) {
		ptrProperties=ModelAllocator< ::IAS::DM::Impl::PropertyList >::Create(this);
	} else {
		const DM::ComplexType* pComplexType = pBaseType->asComplexType();
		ptrProperties=ModelAllocator< ::IAS::DM::Impl::PropertyListWithParent >::Create(&(pComplexType->getProperties()), this);
	}


}
/*************************************************************************/
TypeComplex::~TypeComplex() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DataObject* TypeComplex::createDataObjectImpl() const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject");

	return DataAllocator<DataObjectComplex>::Create(this);
}
/*************************************************************************/
const ::IAS::DM::ComplexType* TypeComplex::asComplexType() const{
	return this;
}
/*************************************************************************/
::IAS::DM::ComplexType* TypeComplex::asComplexType(){
	return this;
}
/*************************************************************************/
bool TypeComplex::isDataObjectType() const{
	return true;
}
/*************************************************************************/
bool TypeComplex::isBaseTypeRestriction() const{
	return false;
}
/*************************************************************************/
::IAS::DM::Type::Types TypeComplex::getTypeEnum() const{
	IAS_TRACER;
	return ::IAS::DM::Type::DataObjectType;
}
/*************************************************************************/
const ::IAS::DM::PropertyList& TypeComplex::getProperties() const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"getProperties:["<<strURI<<":"<<strName<<"]");
	return *ptrProperties;
}
/*************************************************************************/
const ::IAS::DM::Property* TypeComplex::defineProperty(const String& strName,
								    const ::IAS::DM::Type* pType,
								    bool bIsMulti,
								    bool bIsXMLAttribute,
									const String& strDescription){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pType);

	int iIdx = ptrProperties->getSize();

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"NewProperty:["<<strURI<<":"<<strName<<"]"<<iIdx<<":"<<strName<<":"<<pType->getURI()<<":"<<pType->getName());


	ModelAllocator<Property>::PtrHolder ptrProperty(ModelAllocator<Property>::Create(strName, pType, iIdx, bIsMulti, bIsXMLAttribute, strDescription));
	ptrProperties->append(ptrProperty);
	return ptrProperty.pass();
}
/*************************************************************************/
}
}
}
