/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectComplex.cpp
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
#include "../../dm/Impl/DataObjectComplex.h"
#include <commonlib/commonlib.h>

#include "../../dm/Impl/DataObjectList.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Impl/MemoryManager.h"
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
DataObjectComplex::DataObjectComplex(const Type *pType):DataObject(pType){
	IAS_TRACER;
	init();
}
/*************************************************************************/
DataObjectComplex::~DataObjectComplex() throw(){
	IAS_TRACER;

	clear();
}
/*************************************************************************/
void DataObjectComplex::clear(){
	IAS_TRACER;

	const ::IAS::DM::ComplexType* pComplexType = pType->asComplexType();

	const DM::PropertyList& lstProperties = pComplexType->getProperties();
	int iSize = lstProperties.getSize();

	for(int iIdx = 0; iIdx<iSize; iIdx++){

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"P:["
					<<lstProperties.getProperty(iIdx)->getName()<<"]:"
					<<lstProperties.getProperty(iIdx)->isMulti());

		if(lstProperties.getProperty(iIdx)->isMulti()){
			tabDataObjects[iIdx].ptrDataObjectList->clear();
		}else{

			if(!tabDataObjects[iIdx].ptrDataObject.isNull())
				unsetParentIfEligible(tabDataObjects[iIdx].ptrDataObject);
			tabDataObjects[iIdx].ptrDataObject.unset();
			tabDataObjects[iIdx].bSet=false;

	}
	}

}
/*************************************************************************/
::IAS::DM::DataObject* DataObjectComplex::createDataObject(const IAS::DM::Property* pProperty){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pProperty);
	const ::IAS::DM::Type* pType = pProperty->getType();
	DataAllocator<IAS::DM::DataObject>::PtrHolder ptrObject(pType->createDataObject());

	setDataObject(pProperty, ptrObject);
	return ptrObject.pass();
}
/*************************************************************************/
void DataObjectComplex::setDataObject(const IAS::DM::Property *pProperty,
										  IAS::DM::DataObject* pDataObject){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pProperty);

	int iIdx = pProperty->getIdx();

	if(pDataObject && !pDataObject->getType()->isAssignableTo(pProperty->getType())){
		StringStream ssInfo;
		ssInfo<<"Bad type for property:";
		ssInfo<<pProperty->getName()<<" ? ";
		ssInfo<<pDataObject->getType()->getName()<<":";
		ssInfo<<pDataObject->getType()->getURI();
		IAS_THROW(RuntimeException(ssInfo.str()));
	}

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"setDataObject:["<<pProperty->getName()<<":"<<iIdx<<"]:"<<(void*)pDataObject);

	if(pProperty->isMulti()){
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"list address:["<<(void*)(tabDataObjects[iIdx].ptrDataObjectList)<<"]:");
		tabDataObjects[iIdx].ptrDataObjectList->add(pDataObject);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"setMulti:["<<tabDataObjects[iIdx].ptrDataObjectList->size()<<"]:");
	}else{

		if(pDataObject)
			setParentIfEligible(pDataObject);

		if(tabDataObjects[iIdx].bSet && tabDataObjects[iIdx].ptrDataObject)
			unsetParentIfEligible(tabDataObjects[iIdx].ptrDataObject);

		tabDataObjects[iIdx].ptrDataObject = pDataObject;
		tabDataObjects[iIdx].bSet = true;
	}


}
/*************************************************************************/
void  DataObjectComplex::setInteger(const IAS::DM::Property* pProperty, int aValue){
	IAS_TRACER;
	createDataObject(pProperty)->setInteger(aValue);
}
/*************************************************************************/
void  DataObjectComplex::setFloat(const IAS::DM::Property* pProperty, Float fValue){
	IAS_TRACER;
	createDataObject(pProperty)->setFloat(fValue);
}
/*************************************************************************/
void  DataObjectComplex::setDate(const IAS::DM::Property* pProperty,const IAS::Date& tValue){
	IAS_TRACER;
	createDataObject(pProperty)->setDate(tValue);
}
/*************************************************************************/
void  DataObjectComplex::setTime(const IAS::DM::Property* pProperty,const IAS::Time& tValue){
	IAS_TRACER;
	createDataObject(pProperty)->setTime(tValue);
}
/*************************************************************************/
void  DataObjectComplex::setDateTime(const IAS::DM::Property* pProperty,const IAS::DateTime& tValue){
	IAS_TRACER;
	createDataObject(pProperty)->setDateTime(tValue);
}
/*************************************************************************/
void  DataObjectComplex::setBoolean(const IAS::DM::Property* pProperty, bool bValue){
	IAS_TRACER;
	createDataObject(pProperty)->setBoolean(bValue);
}
/*************************************************************************/
void  DataObjectComplex::setString(const IAS::DM::Property* pProperty, const String& strValue){
	IAS_TRACER;
	createDataObject(pProperty)->setString(strValue);
}
/*************************************************************************/
void DataObjectComplex::setRaw(const IAS::DM::Property* pProperty, const RawContent* pRawContent){
	IAS_TRACER;

	createDataObject(pProperty)->setRaw(pRawContent);
}
/*************************************************************************/
void DataObjectComplex::unset(const ::IAS::DM::Property* pProperty){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pProperty);

	int iIdx = pProperty->getIdx();

	if(pProperty->isMulti()){
		tabDataObjects[iIdx].ptrDataObjectList->clear();
	}else{

		if(tabDataObjects[iIdx].bSet){

			if(!tabDataObjects[iIdx].ptrDataObject.isNull())
				unsetParentIfEligible(tabDataObjects[iIdx].ptrDataObject);

			tabDataObjects[iIdx].ptrDataObject.unset();
			tabDataObjects[iIdx].bSet = false;
		}
	}
}
/*************************************************************************/
bool DataObjectComplex::isSet(const IAS::DM::Property* pProperty)const{
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pProperty);

	if(pProperty->isMulti())
		return true;

	int iIdx = pProperty->getIdx();
	return tabDataObjects[iIdx].bSet;
}
/*************************************************************************/
const IAS::DM::DataObject* DataObjectComplex::getDataObject(const IAS::DM::Property *pProperty)const{
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pProperty);
	int iIdx = pProperty->getIdx();

	if(pProperty->isMulti())
		IAS_THROW(RuntimeException("Multi property, ask for a list."));


	if(!tabDataObjects[iIdx].bSet)
		IAS_THROW(RuntimeException(String("Property not set:")+=pProperty->getName()));

	return tabDataObjects[iIdx].ptrDataObject;
}
/*************************************************************************/
bool  DataObjectComplex::getBoolean(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	return getDataObject(pProperty)->toBoolean();
}
/*************************************************************************/
int   DataObjectComplex::getInteger(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	return getDataObject(pProperty)->toInteger();
}
/*************************************************************************/
Float  DataObjectComplex::getFloat(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	return getDataObject(pProperty)->toFloat();
}
/*************************************************************************/
IAS::DateTime DataObjectComplex::getDateTime(const IAS::DM::Property* pProperty) const{
	IAS_TRACER;
	return getDataObject(pProperty)->toDateTime();
}
/*************************************************************************/
String  DataObjectComplex::getString(const IAS::DM::Property* pProperty)const{
	IAS_TRACER;
	return getDataObject(pProperty)->toString();
}
/*************************************************************************/
void DataObjectComplex::getRaw(const IAS::DM::Property* pProperty, RawContent* pRawContent)const{
	IAS_TRACER;

	getDataObject(pProperty)->toRaw(pRawContent);
}
/*************************************************************************/
const ::IAS::DM::DataObjectList& DataObjectComplex::getList(const IAS::DM::Property *pProperty) const{
	IAS_TRACER;

	if(! pProperty->isMulti())
		IAS_THROW(RuntimeException(String("Not a list.")));

	return *(tabDataObjects[pProperty->getIdx()].ptrDataObjectList);
}
/*************************************************************************/
void DataObjectComplex::init(){
	IAS_TRACER;

	const ::IAS::DM::ComplexType* pComplexType = pType->asComplexType();
	tabDataObjects.resize(pComplexType->getProperties().getSize());

	int iSize = pComplexType->getProperties().getSize();

	for(int iIdx = 0; iIdx<iSize; iIdx++){
		const ::IAS::DM::Property *pProperty = pComplexType->getProperties().getProperty(iIdx);
		if(pProperty->isMulti()){
			tabDataObjects[iIdx].ptrDataObjectList =
				DataAllocator<Impl::DataObjectList>::Create((pProperty->getType()), this);
		}
	}
}
/*************************************************************************/
void DataObjectComplex::setDataObject(const IAS::DM::DataObject* pDataObject){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataObject);

	if(!pDataObject->getType()->isAssignableTo(pType)){

		StringStream ssError;
		ssError<<"Type mismatch on a complex object setter.";
		ssError<<"["<<pType->getName()<<":"<<pType->getURI()<<"] => ";
		ssError<<"["<<pDataObject->getType()->getName()<<":"<<pDataObject->getType()->getURI()<<"]";

		IAS_THROW(RuntimeException(ssError.str()));
	}

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"1:["<<pType->getName()<<":"<<pType->getURI()<<"]:");
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"2:["<<pDataObject->getType()->getName()<<":"<<pDataObject->getType()->getURI()<<"]:");

	clear();

	const ::IAS::DM::ComplexType* pComplexType = pType->asComplexType();

	const DM::PropertyList& lstProperties = pComplexType->getProperties();
	int iSize = lstProperties.getSize();

	for(int iIdx = 0; iIdx<iSize; iIdx++){

		const IAS::DM::Property* pProperty = lstProperties.getProperty(iIdx);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"P:["<<
					pProperty->getName()<<":"<<
					pProperty->getType()->getName()<<":"<<
					pProperty->getType()->getURI()<<"]:");

		if(pProperty->isMulti()){

			tabDataObjects[iIdx].ptrDataObjectList->clear();

			const IAS::DM::DataObjectList& lstOriginal = pDataObject->getList(pProperty);

			for(int iListIdx=0; iListIdx<lstOriginal.size(); iListIdx++){

				const IAS::DM::DataObject *pOriginal = lstOriginal.at(iListIdx);
				tabDataObjects[iIdx].ptrDataObjectList->add(pOriginal ? pOriginal->duplicate() : NULL);
			}

		}else{

			if(pDataObject->isSet(pProperty)){
				const IAS::DM::DataObject *pOriginal = pDataObject->getDataObject(pProperty);

				if(pOriginal){
					tabDataObjects[iIdx].ptrDataObject=pOriginal->duplicate();
					setParentIfEligible(tabDataObjects[iIdx].ptrDataObject);
				}else{
					tabDataObjects[iIdx].ptrDataObject=NULL;
				}

				tabDataObjects[iIdx].bSet=true;
			}/*IF: isSet */

		}/* IF: isMulti*/

	}/* FOR: iIdx */

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"E:["<<pType->getName()<<":"<<pType->getURI()<<"]:");

}
/*************************************************************************/
bool DataObjectComplex::equals(const IAS::DM::DataObject* pDataObject)const{

	IAS_TRACER;

	if(!pDataObject)
		return false;

	if(!pDataObject->getType()->equals(pType))
		return false;

	const ::IAS::DM::ComplexType* pComplexType = pType->asComplexType();

	const DM::PropertyList& lstProperties = pComplexType->getProperties();
	int iSize = lstProperties.getSize();

	for(int iIdx = 0; iIdx<iSize; iIdx++){

		const IAS::DM::Property* pProperty = lstProperties.getProperty(iIdx);
		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"P:["<<
					pProperty->getName()<<":"<<
					pProperty->getType()->getName()<<":"<<
					pProperty->getType()->getURI()<<"]:");

		if(pProperty->isMulti()){

			const IAS::DM::DataObjectList& lstOriginal = pDataObject->getList(pProperty);

			if(tabDataObjects[iIdx].ptrDataObjectList->size() != lstOriginal.size())
				return false;

			for(int iListIdx=0; iListIdx<lstOriginal.size(); iListIdx++){

				const IAS::DM::DataObject *pOriginal = lstOriginal.at(iListIdx);
				const IAS::DM::DataObject *pMine     = tabDataObjects[iIdx].ptrDataObjectList->at(iListIdx);

				if(!pOriginal && pMine)
					return false;

				if(!pOriginal->equals(pMine))
					return false;
			}

		}else{

			if(tabDataObjects[iIdx].bSet != pDataObject->isSet(pProperty))
				return false;

			if(pDataObject->isSet(pProperty)){

				const IAS::DM::DataObject *pOriginal = pDataObject->getDataObject(pProperty);

				if(!pOriginal && tabDataObjects[iIdx].ptrDataObject)
					return false;

				if(!pOriginal->equals(tabDataObjects[iIdx].ptrDataObject))
					return false;

			}/*IF: isSet */

		}/* IF: isMulti*/

	}/* FOR: iIdx */

	return true;
}
/*************************************************************************/
}
}
}
