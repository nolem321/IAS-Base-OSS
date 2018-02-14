/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectDateTime.cpp
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
#include "../../dm/Impl/DataObjectDateTime.h"
#include <commonlib/commonlib.h>
#include "../../dm/Type.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectDateTime::DataObjectDateTime(const Type *pType):DataObjectBasic(pType),tValue(){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectDateTime::~DataObjectDateTime() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DataObjectDateTime::toString()const{
	IAS_TRACER;
	return tValue.toString();
}
/*************************************************************************/
int DataObjectDateTime::toInteger()const{
	IAS_TRACER;
	time_t iValue;
	tValue.toPosixTime(iValue);
	return (int)iValue;
}
/*************************************************************************/
IAS::DateTime DataObjectDateTime::toDateTime()const{
	IAS_TRACER;
	return tValue;
}
/*************************************************************************/
IAS::Time DataObjectDateTime::toTime()const{
	IAS_TRACER;
	return tValue;
}

/*************************************************************************/
IAS::Date DataObjectDateTime::toDate()const{
	IAS_TRACER;
	return tValue;
}
/*************************************************************************/
void DataObjectDateTime::setString(const String& strValue){
	IAS_TRACER;
	tValue.fromString(strValue);
}
/*************************************************************************/
void DataObjectDateTime::setInteger(int iValue){
	IAS_TRACER;
	time_t tmpValue(iValue);
	tValue.fromPosixTime(tmpValue);
}
/*************************************************************************/
void DataObjectDateTime::setDateTime(const IAS::DateTime& tValue){
	IAS_TRACER;
	this->tValue = tValue;
}
/*************************************************************************/
void DataObjectDateTime::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	tValue = pDataObject->toDateTime();
}
/*************************************************************************/
bool DataObjectDateTime::equals(const IAS::DM::DataObject* pDataObject)const{

	IAS_TRACER;

	if(!pDataObject)
		return false;

	if(!pDataObject->getType()->equals(pType))
		return false;

	return tValue == pDataObject->toDateTime();
}
/*************************************************************************/
}
}
}
