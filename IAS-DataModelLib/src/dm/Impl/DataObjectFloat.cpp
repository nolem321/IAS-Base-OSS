/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectFloat.cpp
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
#include "../../dm/Impl/DataObjectFloat.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectFloat::DataObjectFloat(const Type *pType):DataObjectBasic(pType),fValue(0.0){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectFloat::~DataObjectFloat() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DataObjectFloat::toString()const{
	IAS_TRACER;
	return TypeTools::FloatToString(fValue);
}
/*************************************************************************/
bool DataObjectFloat::toBoolean()const{
	IAS_TRACER;
	return fValue != 0;
}
/*************************************************************************/
int DataObjectFloat::toInteger()const{
	IAS_TRACER;
	return (int)fValue;
}
/*************************************************************************/
Float DataObjectFloat::toFloat()const{
	IAS_TRACER;
	return fValue;
}
/*************************************************************************/
void DataObjectFloat::setString(const String& strValue){
	IAS_TRACER;
	fValue=TypeTools::StringToFloat(strValue);
}
/*************************************************************************/
void DataObjectFloat::setInteger(int iValue){
	IAS_TRACER;
	fValue = (int)iValue;
}
/*************************************************************************/
void DataObjectFloat::setBoolean(bool bValue){
	IAS_TRACER;
	fValue = (Float)bValue;
}
/*************************************************************************/
void DataObjectFloat::setFloat(Float fValue){
	IAS_TRACER;
	this->fValue != fValue;
}
/*************************************************************************/
void DataObjectFloat::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	fValue = pDataObject->toFloat();
}
/*************************************************************************/
}
}
}
