/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectDate.cpp
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
#include "../../dm/Impl/DataObjectDate.h"
#include "../../dm/Type.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectDate::DataObjectDate(const Type *pType):DataObjectBasic(pType),tValue(){
	IAS_TRACER;
}
/*************************************************************************/
DataObjectDate::~DataObjectDate() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DataObjectDate::toString()const{
	IAS_TRACER;
	return tValue.toString();
}
/*************************************************************************/
int DataObjectDate::toInteger()const{
	IAS_TRACER;
	time_t iValue;
	tValue.toPosixTime(iValue);
	return (int)iValue;
}
/*************************************************************************/
IAS::DateTime DataObjectDate::toDateTime()const{
	IAS_TRACER;
	return tValue;
}
/*************************************************************************/
IAS::Date DataObjectDate::toDate()const{
	IAS_TRACER;
	return tValue;
}
/*************************************************************************/
void DataObjectDate::setString(const String& strValue){
	IAS_TRACER;
	tValue.fromString(strValue);
}
/*************************************************************************/
void DataObjectDate::setInteger(int iValue){
	IAS_TRACER;
	time_t tmpValue(iValue);
	tValue.fromPosixTime(tmpValue);
}
/*************************************************************************/
void DataObjectDate::setDateTime(const IAS::DateTime& tValue){
	IAS_TRACER;
	this->tValue = tValue;
}
/*************************************************************************/
void DataObjectDate::setDate(const IAS::Date& tValue){
	IAS_TRACER;
	//TODO zero time
	this->tValue = tValue;
}
/*************************************************************************/
void DataObjectDate::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	tValue = pDataObject->toDate();
}
/*************************************************************************/
bool DataObjectDate::equals(const IAS::DM::DataObject* pDataObject)const{

	IAS_TRACER;

	if(!pDataObject)
		return false;

	if(!pDataObject->getType()->equals(pType))
		return false;

	return tValue == pDataObject->toDate();
}
/*************************************************************************/
}
}
}
