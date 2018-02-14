/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectTime.cpp
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
#include "../../dm/Impl/DataObjectTime.h"
#include <commonlib/commonlib.h>
#include "../../dm/Type.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectTime::DataObjectTime(const Type *pType):DataObjectBasic(pType),tValue(){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectTime::~DataObjectTime() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DataObjectTime::toString()const{
	IAS_TRACER;
	return tValue.toString();
}
/*************************************************************************/
int DataObjectTime::toInteger()const{
	IAS_TRACER;
	time_t iValue;
	tValue.toPosixTime(iValue);
	return (int)iValue;
}
/*************************************************************************/
IAS::DateTime DataObjectTime::toDateTime()const{
	IAS_TRACER;
	return DateTime(tValue);
}
/*************************************************************************/
IAS::Time DataObjectTime::toTime()const{
	IAS_TRACER;
	return tValue;
}
/*************************************************************************/
void DataObjectTime::setString(const String& strValue){
	IAS_TRACER;
	tValue.fromString(strValue);
}
/*************************************************************************/
void DataObjectTime::setInteger(int iValue){
	IAS_TRACER;
	time_t tmpValue(iValue);
	tValue.fromPosixTime(tmpValue);
}
/*************************************************************************/
void DataObjectTime::setDateTime(const IAS::DateTime& tValue){
	IAS_TRACER;
	//TODO zero date
	this->tValue = tValue;
}
/*************************************************************************/
void DataObjectTime::setTime(const IAS::Time& tValue){
	IAS_TRACER;
	this->tValue = tValue;
}
/*************************************************************************/
void DataObjectTime::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	tValue = pDataObject->toTime();
}
/*************************************************************************/
bool DataObjectTime::equals(const IAS::DM::DataObject* pDataObject)const{

	IAS_TRACER;

	if(!pDataObject)
		return false;

	if(!pDataObject->getType()->equals(pType))
		return false;

	return tValue == pDataObject->toTime();
}
/*************************************************************************/
}
}
}
