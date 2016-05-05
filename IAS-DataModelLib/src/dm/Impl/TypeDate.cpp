/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeDate.cpp
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
#include "../../dm/Impl/TypeDate.h"
#include <commonlib/commonlib.h>
#include "../../dm/Impl/DataFactory.h"
#include "../../dm/Impl/DataObjectDate.h"
#include "../../dm/Impl/MemoryManager.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
TypeDate::TypeDate( const String& strURI,
	  	  	const String& strName,
	  	  	const ::IAS::DM::Type *pBaseType) :
::IAS::DM::Impl::TypeBasic(strURI, strName, pBaseType){
	IAS_TRACER;
}
/*************************************************************************/
TypeDate::~TypeDate() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DataObject* TypeDate::createDataObjectImpl() const{
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject");
	return DataAllocator<DataObjectDate>::Create(this);
}
/*************************************************************************/
::IAS::DM::Type::Types TypeDate::getTypeEnum() const{
	IAS_TRACER;
	return ::IAS::DM::Type::DateType;
}
/*************************************************************************/
}
}
}
