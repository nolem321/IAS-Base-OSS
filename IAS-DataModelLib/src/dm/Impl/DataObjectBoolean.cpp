/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectBoolean.cpp
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
#include "../../dm/Impl/DataObjectBoolean.h"
#include <commonlib/commonlib.h>

#include "../../dm/Impl/exception/IllegalCastException.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Impl/TypeBoolean.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectBoolean::DataObjectBoolean(const Type *pType):DataObjectBasic(pType),bValue(false){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectBoolean::~DataObjectBoolean() throw(){
	IAS_TRACER;

}
/*************************************************************************/
String DataObjectBoolean::toString()const{
	IAS_TRACER;
	return TypeTools::BoolToString(bValue);
}
/*************************************************************************/
bool DataObjectBoolean::toBoolean()const{
	IAS_TRACER;
	return bValue;
}
/*************************************************************************/
int DataObjectBoolean::toInteger()const{
	IAS_TRACER;
	return bValue;
}
/*************************************************************************/
Float DataObjectBoolean::toFloat()const{
	IAS_TRACER;
	return bValue;
}
/*************************************************************************/
void DataObjectBoolean::setString(const String& strValue){
	IAS_TRACER;
	bValue = TypeTools::StringToBoolean(strValue,true);
}
/*************************************************************************/
void DataObjectBoolean::setInteger(int iValue){
	IAS_TRACER;
	bValue = iValue != 0;
}
/*************************************************************************/
void DataObjectBoolean::setBoolean(bool bValue){
	IAS_TRACER;
	this->bValue = bValue;
}
/*************************************************************************/
void DataObjectBoolean::setFloat(Float fValue){
	IAS_TRACER;
	bValue = fValue != 0.0;
}
/*************************************************************************/
void DataObjectBoolean::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	bValue = pDataObject->toBoolean();
}
/*************************************************************************/
}
}
}
