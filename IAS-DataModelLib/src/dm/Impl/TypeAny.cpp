/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeAny.cpp
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
#include "../../dm/Impl/TypeAny.h"
#include <commonlib/commonlib.h>

#include "../../dm/Impl/DataFactory.h"
#include "../../dm/log/LogLevel.h"

#include "DataObjectAnyType.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
TypeAny::TypeAny():
	Type(::IAS::DM::Impl::DataFactory::BuildInTypesNamespace, "AnyType", NULL){
	IAS_TRACER;
}
/*************************************************************************/
TypeAny::TypeAny(const String& strURI,
					 const String& strName,
					 const ::IAS::DM::Type    *pBaseType):
	Type(strURI,strName, pBaseType){
	IAS_TRACER;
}
/*************************************************************************/
TypeAny::~TypeAny() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool TypeAny::isDataObjectType() const{
	return false;
}
/*************************************************************************/
bool TypeAny::isBaseTypeRestriction() const{
	return false;
}
/*************************************************************************/
const ::IAS::DM::ComplexType* TypeAny::asComplexType() const{
	IAS_TRACER;
	IAS_THROW(BadUsageException("Cannot convert to a complex type."));
}
/*************************************************************************/
DataObject* TypeAny::createDataObjectImpl() const{
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject");

	return DataAllocator<Impl::DataObjectAnyType>::Create(this);
}
/*************************************************************************/
::IAS::DM::ComplexType* TypeAny::asComplexType(){
	IAS_TRACER;
	IAS_THROW(BadUsageException("Cannot convert to a complex type."));
}
/*************************************************************************/
::IAS::DM::Type::Types TypeAny::getTypeEnum() const{
	IAS_TRACER;
	return ::IAS::DM::Type::AnyType;
}
/*************************************************************************/
}
}
}
