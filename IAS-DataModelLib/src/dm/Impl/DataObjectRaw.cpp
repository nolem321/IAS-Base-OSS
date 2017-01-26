/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectRaw.cpp
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
#include "../../dm/Impl/DataObjectRaw.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectRaw::DataObjectRaw(const Type *pType):
		DataObjectBasic(pType){
	IAS_TRACER;
	ptrRawContentValue =  DataAllocator<RawContent>::Create(0,Impl::MemoryManager::GetAllocatorForData());
}
/*************************************************************************/
DataObjectRaw::~DataObjectRaw() throw(){
	IAS_TRACER;

}
/*************************************************************************/
::IAS::String DataObjectRaw::toString()const{
	//TODO Base64
	return String(ptrRawContentValue->getBuffer<const char>(),ptrRawContentValue->getSize());
}
/*************************************************************************/
void DataObjectRaw::setString(const ::IAS::String& strValue){
	IAS_TRACER;
	//TODO Base64
	ptrRawContentValue->reserve(strValue.length());
	strncpy(ptrRawContentValue->getBuffer<char>(),strValue.c_str(),strValue.length());
}
/*************************************************************************/
void DataObjectRaw::toRaw( RawContent* pRawContent)const{
	IAS_TRACER;
	//TODO Base64
	pRawContent->reserve(ptrRawContentValue->getSize());
	memcpy(pRawContent->getBuffer<void>(),
			ptrRawContentValue->getBuffer<void>(),
			ptrRawContentValue->getSize());
}
/*************************************************************************/
void DataObjectRaw::setRaw(const RawContent* pRawContent){
	IAS_TRACER;
	ptrRawContentValue->reserve(pRawContent->getSize());
	memcpy(ptrRawContentValue->getBuffer<void>(),
			pRawContent->getBuffer<void>(),
			pRawContent->getSize());
}
/*************************************************************************/
void DataObjectRaw::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	setString(pDataObject->toString());
}
/*************************************************************************/
}
}
}
