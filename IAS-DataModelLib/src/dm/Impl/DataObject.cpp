/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObject.cpp
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
#include "../../dm/Impl/DataObject.h"
#include <commonlib/commonlib.h>
#include "dm/log/LogLevel.h"
#include "../../dm/Impl/exception/IllegalCastException.h"
#include "../../dm/Impl/exception/NotFoundException.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Impl/Property.h"
#include "../../dm/Impl/PropertyList.h"
#include "../../dm/Impl/Type.h"
#include "../../dm/Impl/XPathCursor.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Type.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObject::DataObject(const Type *pType){
	IAS_TRACER;
	TypeRefFeature::init(pType, this);
	pParent=NULL;
}
/*************************************************************************/
DataObject::~DataObject() throw(){
	IAS_TRACER;

	//No exceptions here
	if(this->pParent){
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"this="<<(void*)this<<" has a parent on delete!");
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"this="<<(void*)this<<pType->getName()<<":"<<pType->getURI());
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"parent="<<(void*)pParent);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"parent="<<(void*)this<<pParent->getType()->getName()<<":"<<pParent->getType()->getURI());
		StackContainer::GetThreadStack()->printStack(std::cerr);
	}

}

/*************************************************************************/
bool DataObject::isSet(const String& strXPath)const{
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"isSet:["<<strXPath<<"]:");

	if(strXPath.length() == 0)
		return true;

	const DM::Property* pProperty;
	DM::DataObject* pParent;

	try{
		XPathCursor::FindLastParent(this, strXPath, pParent, pProperty);
	}catch(RuntimeException& e){
		return false;//TODO out of list range exception.
	}

	return pParent->isSet(pProperty);
}
/*************************************************************************/
bool DataObject::isSet(const IAS::DM::Property* pProperty)const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/

/*************************************************************************/
IAS::DM::DataObject* DataObject::getDataObject(const String& strXPath){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"getDataObject:["<<strXPath<<"]:");

	return const_cast<IAS::DM::DataObject*>(static_cast<const IAS::DM::DataObject*>(this)->getDataObject(strXPath) );
}
/*************************************************************************/
const IAS::DM::DataObject* DataObject::getDataObject(const String& strXPath)const {
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"getDataObject:["<<strXPath<<"]:const");

	if(strXPath.length() == 0)
		return this;

	return XPathCursor::GetLastChild(this,strXPath);
}
/*************************************************************************/

/*************************************************************************/
const IAS::DM::DataObject* DataObject::getDataObject(const IAS::DM::Property *pProperty)const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
IAS::DM::DataObject* DataObject::getDataObject(const IAS::DM::Property *pProperty){
	IAS_TRACER;
	return const_cast<IAS::DM::DataObject*>(static_cast<const IAS::DM::DataObject*>(this)->getDataObject(pProperty) );
}
/*************************************************************************/
bool  DataObject::getBoolean(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
int   DataObject::getInteger(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
Float  DataObject::getFloat(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
IAS::DateTime  DataObject::getDateTime(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
IAS::Date  DataObject::getDate(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
IAS::Time  DataObject::getTime(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
String  DataObject::getString(const IAS::DM::Property* pProperty)const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void DataObject::getRaw(const IAS::DM::Property* pProperty, RawContent* pRawContent)const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/

/*************************************************************************/
const IAS::DM::DataObjectList& DataObject::getList(const ::IAS::DM::Property *pProperty)const{
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a list.")));
}
/*************************************************************************/
IAS::DM::DataObjectList& DataObject::getList(const ::IAS::DM::Property *pProperty){
	IAS_TRACER;
	return const_cast< IAS::DM::DataObjectList& >(static_cast<const IAS::DM::DataObject*>(this)->getList(pProperty) );
}
/*************************************************************************/

/*************************************************************************/
const ::IAS::DM::DataObjectList& DataObject::getList(const String& strXPath) const{
	IAS_TRACER;

	const IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	return pParent->getList(pProperty);
}
/*************************************************************************/
::IAS::DM::DataObjectList& DataObject::getList(const String& strXPath){
	IAS_TRACER;
	return const_cast< IAS::DM::DataObjectList& >(static_cast<const IAS::DM::DataObject*>(this)->getList(strXPath) );
}
/*************************************************************************/

/*************************************************************************/
IAS::DM::DataObject* DataObject::createDataObject(const String& strXPath){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"createDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	return pParent->createDataObject(pProperty);
}
/*************************************************************************/
IAS::DM::DataObject* DataObject::createDataObject(const IAS::DM::Property *pProperty){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void DataObject::setDataObject(const String& strXPath, IAS::DM::DataObject* pDataObject){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setDataObject(pProperty,pDataObject);
}
/*************************************************************************/
void  DataObject::setInteger(const String& strXPath, int aValue){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setInteger(pProperty,aValue);

}
/*************************************************************************/
void  DataObject::setFloat(const String& strXPath, Float fValue){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setFloat(pProperty,fValue);
}
/*************************************************************************/
void  DataObject::setDateTime(const String& strXPath,const IAS::DateTime& tValue){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setDateTime(pProperty,tValue);
}
/*************************************************************************/
void  DataObject::setDate(const String& strXPath,const IAS::Date& tValue){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setDate(pProperty,tValue);
}
/*************************************************************************/
void  DataObject::setTime(const String& strXPath,const IAS::Time& tValue){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setTime(pProperty,tValue);
}
/*************************************************************************/
void  DataObject::setBoolean(const String& strXPath, bool bValue){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setBoolean(pProperty,bValue);

}
/*************************************************************************/
void  DataObject::setString(const String& strXPath, const String& strValue){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"]:"<<strValue);

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setString(pProperty,strValue);
}
/*************************************************************************/
void  DataObject::setRaw(const String& strXPath, const RawContent* pRawContent){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"setDataObject:["<<strXPath<<"], Raw, data len:"<<pRawContent->getSize());

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->setRaw(pProperty,pRawContent);
}
/*************************************************************************/
void DataObject::unset(const String& strXPath){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"unset["<<strXPath<<"]:");

	IAS::DM::DataObject* pParent;
	const ::IAS::DM::Property *pProperty;
	XPathCursor::FindLastParent(this,strXPath,pParent, pProperty);

	pParent->unset(pProperty);
}
/*************************************************************************/
void DataObject::unset(const ::IAS::DM::Property* pProperty){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void DataObject::setDataObject(const IAS::DM::Property *pProperty,
								  IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")+pType->getName()+":"+pType->getURI()));
}
/*************************************************************************/
void  DataObject::setInteger(const IAS::DM::Property* pProperty, int aValue){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void  DataObject::setFloat(const IAS::DM::Property* pProperty, Float fValue){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void  DataObject::setDateTime(const IAS::DM::Property* pProperty,const IAS::DateTime& tValue){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void  DataObject::setDate(const IAS::DM::Property* pProperty,const IAS::Date& tValue){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void  DataObject::setTime(const IAS::DM::Property* pProperty,const IAS::Time& tValue){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void  DataObject::setBoolean(const IAS::DM::Property* pProperty, bool bValue){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void  DataObject::setString(const IAS::DM::Property* pProperty, const String& strValue){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/
void DataObject::setRaw(const IAS::DM::Property* pProperty, const RawContent* pRawContent){
	IAS_TRACER;
	IAS_THROW(RuntimeException(String("Not a complex type.")));
}
/*************************************************************************/

/*************************************************************************/
bool DataObject::getBoolean(const String& strXPath)const{
	IAS_TRACER;
	return getDataObject(strXPath)->toBoolean();
}
/*************************************************************************/
int DataObject::getInteger(const String& strXPath) const{
	IAS_TRACER;
	return getDataObject(strXPath)->toInteger();
}
/*************************************************************************/
Float DataObject::getFloat(const String& strXPath) const{
	IAS_TRACER;
	return getDataObject(strXPath)->toFloat();
}
/*************************************************************************/
IAS::DateTime DataObject::getDateTime(const String& strXPath) const{
	IAS_TRACER;
	return getDataObject(strXPath)->toDateTime();
}
/*************************************************************************/
IAS::Date DataObject::getDate(const String& strXPath) const{
	IAS_TRACER;
	return getDataObject(strXPath)->toDate();
}
/*************************************************************************/
IAS::Time DataObject::getTime(const String& strXPath) const{
	IAS_TRACER;
	return getDataObject(strXPath)->toTime();
}
/*************************************************************************/
String DataObject::getString(const String& strXPath) const{
	IAS_TRACER;
	return getDataObject(strXPath)->toString();
}
/*************************************************************************/
void DataObject::getRaw(const String& strXPath, RawContent* pRawContent) const{
	IAS_TRACER;
	return getDataObject(strXPath)->toRaw(pRawContent);
}
/*************************************************************************/
String DataObject::toString() const{
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion to string not available."));
}
/*************************************************************************/
void DataObject::toRaw(RawContent* pRawContent) const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isError(),"toRaw not allowed:  ["<<pType->getName()<<"]");
	IAS_THROW(IllegalCastException(pType,"Conversion to Raw content not available."));
}
/*************************************************************************/
bool DataObject::toBoolean()const{
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"toBoolean not allowed:  ["<<pType->getName()<<"]");
	IAS_THROW(IllegalCastException(pType,"Conversion to boolean not available."));
}
/*************************************************************************/
int DataObject::toInteger()const{
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion to integer not available."));
}
/*************************************************************************/
Float DataObject::toFloat()const{
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion to float not available."));
}
/*************************************************************************/
IAS::DateTime DataObject::toDateTime()const{
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion to datetime not available."));
}
/*************************************************************************/
IAS::Date DataObject::toDate()const{
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion to datetime not available."));
}
/*************************************************************************/
IAS::Time DataObject::toTime()const{
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion to datetime not available."));
}
/*************************************************************************/
void DataObject::setString(const String& strValue){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from string not available."));
}
/*************************************************************************/
void DataObject::setRaw(const RawContent* pRawContent){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from Raw content not available."));
}
/*************************************************************************/
void DataObject::setInteger(int iValue){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from integer not available."));
}
/*************************************************************************/
void DataObject::setBoolean(bool bValue){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from boolean not available."));
}
/*************************************************************************/
void DataObject::setFloat(Float fValue){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from float not available."));
}
/*************************************************************************/
void DataObject::setDateTime(const IAS::DateTime& tValue){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from datetime not available."));
}
/*************************************************************************/
void DataObject::setDate(const IAS::Date& tValue){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from date not available."));
}
/*************************************************************************/
void DataObject::setTime(const IAS::Time& tValue){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from time not available."));
}
/*************************************************************************/
void DataObject::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_THROW(IllegalCastException(pType,"Conversion from data object not available."));
}
/*************************************************************************/
const ::IAS::DM::Type* DataObject::getType() const{
	IAS_TRACER;
	const ::IAS::DM::Type* pReturn = pType;
	return pReturn;
}
/*************************************************************************/
IAS::DM::DataObject* DataObject::getParent() const{
	IAS_TRACER;

	if(pParent == NULL)
		IAS_THROW(NotFoundException());

	return pParent;
}
/*************************************************************************/
IAS::DM::DataObject* DataObject::getParentRoot() const{
	IAS_TRACER;

	if(pParent == NULL)
		IAS_THROW(NotFoundException());

	IAS::DM::DataObject* pCursor = pParent;

	bool bFound=false;
	while(bFound)
		try{
			pCursor =  pCursor->getParent();
		}catch(NotFoundException& e){
			bFound=true;
		}

	return pCursor;
}
/*************************************************************************/
void DataObject::setParent(IAS::DM::DataObject* pParent){
	IAS_TRACER;

	if(this->pParent)
		IAS_THROW(RuntimeException("Object already has a parent."));

	IAS_CHECK_IF_VALID(pParent);
	this->pParent=pParent;
}
/*************************************************************************/
void DataObject::unsetParent(){
	IAS_TRACER;

	if(!this->pParent)
		IAS_THROW(RuntimeException("Object hasn't got a parent !"));

	this->pParent=NULL;
}
/*************************************************************************/
::IAS::DM::DataObject* DataObject::duplicate() const{
	IAS_TRACER;
	return pType->createDataObject(this);
}
/*************************************************************************/
}
}
}
