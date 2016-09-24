/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectString.cpp
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
#include "../../dm/Impl/DataObjectString.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"
#include "Type.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectString::DataObjectString(const Type *pType):
		DataObjectBasic(pType),
		strValue(""){
	IAS_TRACER;

	//if(strValue.length() > pType->getRestrictionMaxLenght())
	//	IAS_THROW(BadUsageException("xsi:maxLength exceeded."));

}
/*************************************************************************/
DataObjectString::~DataObjectString() throw(){
	IAS_TRACER;

}
/*************************************************************************/
::IAS::String DataObjectString::toString()const{
	return strValue;
}
/*************************************************************************/
bool DataObjectString::toBoolean()const{
	IAS_TRACER;
	return TypeTools::StringToBoolean(strValue);
}
/*************************************************************************/
int DataObjectString::toInteger()const{
	IAS_TRACER;
	return TypeTools::StringToInt(strValue);
}
/*************************************************************************/
Float DataObjectString::toFloat()const{
	IAS_TRACER;
	return TypeTools::StringToFloat(strValue);
}
/*************************************************************************/
IAS::Date DataObjectString::toDate()const{
	IAS_TRACER;
	return IAS::Date(strValue);
}
/*************************************************************************/
IAS::Time DataObjectString::toTime()const{
	IAS_TRACER;
	return IAS::Time(strValue);
}
/*************************************************************************/
IAS::DateTime DataObjectString::toDateTime()const{
	IAS_TRACER;
	return IAS::DateTime(strValue);
}
/*************************************************************************/
void DataObjectString::setString(const ::IAS::String& strValue){
	IAS_TRACER;

	//if(strValue.length() > pType->getRestrictionMaxLenght())
	//	IAS_THROW(BadUsageException("xsi:maxLength exceeded for: "+strValue));

	this->strValue=strValue;
}
/*************************************************************************/
void DataObjectString::setInteger(int iValue){
	IAS_TRACER;
	String strTmp;
	TypeTools::IntToString(iValue,strTmp);
	strValue=strTmp;
}
/*************************************************************************/
void DataObjectString::setBoolean(bool bValue){
	IAS_TRACER;
	strValue = TypeTools::BoolToString(bValue);
}
/*************************************************************************/
void DataObjectString::setFloat(Float fValue){
	IAS_TRACER;
	strValue = TypeTools::FloatToString(fValue);
}
/*************************************************************************/
void DataObjectString::setDateTime(const IAS::DateTime& tValue){
	IAS_TRACER;
	strValue=tValue.toString();
}
/*************************************************************************/
void DataObjectString::setDate(const IAS::Date& tValue){
	IAS_TRACER;
	strValue=tValue.toString();
}
/*************************************************************************/
void DataObjectString::setTime(const IAS::Time& tValue){
	IAS_TRACER;
	strValue=tValue.toString();
}
/*************************************************************************/
void DataObjectString::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataObject);
	strValue = pDataObject->toString();
}
/*************************************************************************/
}
}
}
