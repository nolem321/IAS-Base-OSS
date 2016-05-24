/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectInteger.cpp
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
#include "../../dm/Impl/DataObjectInteger.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectInteger::DataObjectInteger(const Type *pType):DataObjectBasic(pType),iValue(0){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectInteger::~DataObjectInteger() throw(){
	IAS_TRACER;

}
/*************************************************************************/
String DataObjectInteger::toString()const{
	IAS_TRACER;
	return TypeTools::IntToString(iValue);
}
/*************************************************************************/
bool DataObjectInteger::toBoolean()const{
	IAS_TRACER;
	return iValue != 0;
}
/*************************************************************************/
int DataObjectInteger::toInteger()const{
	IAS_TRACER;
	return iValue;
}
/*************************************************************************/
Float DataObjectInteger::toFloat()const{
	IAS_TRACER;
	return (Float)iValue;
}
/*************************************************************************/
IAS::Date DataObjectInteger::toDate()const{
	IAS_TRACER;
	Date tsValue;
	time_t tmpValue(iValue);
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
IAS::Time DataObjectInteger::toTime()const{
	IAS_TRACER;
	Time tsValue;
	time_t tmpValue(iValue);
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
IAS::DateTime DataObjectInteger::toDateTime()const{
	IAS_TRACER;
	DateTime tsValue;
	time_t tmpValue(iValue);
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
void DataObjectInteger::setString(const String& strValue){
	IAS_TRACER;
	iValue = TypeTools::StringToInt(strValue);
}
/*************************************************************************/
void DataObjectInteger::setInteger(int iValue){
	IAS_TRACER;
	this->iValue = iValue;
}
/*************************************************************************/
void DataObjectInteger::setBoolean(bool bValue){
	IAS_TRACER;
	iValue = (Float)bValue;
}
/*************************************************************************/
void DataObjectInteger::setFloat(Float fValue){
	IAS_TRACER;
	iValue = (int)fValue;
}
/*************************************************************************/
void DataObjectInteger::setDateTime(const IAS::DateTime& tValue){
	IAS_TRACER;
	time_t tmpValue;
	tValue.toPosixTime(tmpValue);
	this->iValue=tmpValue;
}
/*************************************************************************/
void DataObjectInteger::setDate(const IAS::Date& tValue){
	IAS_TRACER;
	time_t tmpValue;
	tValue.toPosixTime(tmpValue);
	this->iValue=tmpValue;
}
/*************************************************************************/
void DataObjectInteger::setTime(const  IAS::Time& tValue){
	IAS_TRACER;
	time_t tmpValue;
	tValue.toPosixTime(tmpValue);
	this->iValue=tmpValue;
}
/*************************************************************************/
void DataObjectInteger::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	iValue = pDataObject->toInteger();
}
/*************************************************************************/
}
}
}
