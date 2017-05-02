/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectList.cpp
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
#include "../../dm/Impl/DataObjectList.h"
#include <commonlib/commonlib.h>

#include "../../dm/DataObject.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Impl/Type.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
DataObjectList::DataObjectList(const IAS::DM::Type *pType,	IAS::DM::DataObject *pParent){
	IAS_TRACER;
	TypeRefFeature::init(pType,pParent);
}

/*************************************************************************/
DataObjectList::~DataObjectList() throw(){
	IAS_TRACER;

	clear();

}
/*************************************************************************/
int  DataObjectList::size() const{
	IAS_TRACER;
	return lstDataObject.size();
}
/*************************************************************************/
const ::IAS::DM::DataObject* DataObjectList::at(int iIdx) const{
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"List["<<iIdx<<":"<<lstDataObject.size()<<"]")

	if(iIdx < 0 || iIdx >= lstDataObject.size()){
		IAS_THROW(RuntimeException()<<"Out of range:"<<iIdx<<" of "<<lstDataObject.size());
	}

	return lstDataObject[iIdx];
}
/*************************************************************************/
::IAS::DM::DataObject* DataObjectList::at(int iIdx){
	IAS_TRACER;
	return const_cast<IAS::DM::DataObject*>(static_cast<const DataObjectList*>(this)->at(iIdx));
}
/*************************************************************************/
void DataObjectList::remove(int iIdx){
	IAS_TRACER;

	::IAS::DM::DataObject* pDataObject = at(iIdx);

	if(pDataObject){
		unsetParentIfEligible(pDataObject);

		if(!ptrHash.isNull())
			ptrHash->remove(pDataObject);
	}

	lstDataObject.erase(lstDataObject.begin()+=iIdx);
}
/*************************************************************************/
void DataObjectList::add(::IAS::DM::DataObject* pDataObject){
	IAS_TRACER;

	if(pDataObject){

		if(! pDataObject->getType()->isAssignableTo(pType)){
			StringStream ssInfo;
			ssInfo<<"Bad type for a list:";
			ssInfo<<pDataObject->getType()->getName()<<":";
			ssInfo<<pDataObject->getType()->getURI();
			IAS_THROW(RuntimeException(ssInfo.str()));
		}

		setParentIfEligible(pDataObject);

		if(ptrHash)
			ptrHash->insert(pDataObject);

	}

	lstDataObject.push_back(pDataObject);
}
/*************************************************************************/
void DataObjectList::set(int iIdx, ::IAS::DM::DataObject* pDataObject){
	IAS_TRACER;

	if(pDataObject && !pDataObject->getType()->isAssignableTo(pType)){
			StringStream ssInfo;
			ssInfo<<"Bad type for a list:";
			ssInfo<<pDataObject->getType()->getName()<<":";
			ssInfo<<pDataObject->getType()->getURI();
			IAS_THROW(RuntimeException(ssInfo.str()));
	}

	if(iIdx < 0 || iIdx >= lstDataObject.size()){
		IAS_THROW(RuntimeException("Out of range."));
	}

	if(lstDataObject[iIdx]){
		unsetParentIfEligible(lstDataObject[iIdx]);

		if(!ptrHash.isNull())
			ptrHash->remove(lstDataObject[iIdx]);

	}

	if(pDataObject){
		setParentIfEligible(pDataObject);

		if(!ptrHash.isNull())
			ptrHash->insert(pDataObject);

	}

	lstDataObject[iIdx]=pDataObject;
}
/*************************************************************************/
void DataObjectList::clear(){
	IAS_TRACER;

	ptrHash = NULL;

	if(bIsParentEligible)
		for(DataObjectVector::iterator it=lstDataObject.begin();
		it != lstDataObject.end();
		it++)
			if(*it)
				unsetParentIfEligible(*it);

	lstDataObject.clear();

}
/*************************************************************************/
::IAS::DM::DataObject* DataObjectList::operator [](int iIdx){
	IAS_TRACER;
	return at(iIdx);
}
/*************************************************************************/
const ::IAS::DM::DataObject* DataObjectList::operator [](int iIdx)const{
	IAS_TRACER;
	return at(iIdx);
}
/*************************************************************************/
const ::IAS::DM::Type* DataObjectList::getType() const{
	IAS_TRACER;
	return pType;
}
/*************************************************************************/
DataObjectList::Hash::Hash():strHashXPath(""){};
DataObjectList::Hash::~Hash(){};
/*************************************************************************/
void DataObjectList::hashWith(const String& strXPath){
	IAS_TRACER;

	ptrHash = DataAllocator<Hash>::Create();
	ptrHash->strHashXPath = strXPath;

	for(DataObjectVector::iterator it=lstDataObject.begin();
			it != lstDataObject.end();
			it++)
		ptrHash->insert(*it);
}
/*************************************************************************/
::IAS::DM::DataObject* DataObjectList::at(const ::IAS::DM::DataObject* pKey){
	IAS_TRACER;

	String strKey = pKey->toString();

	HashMap::iterator it = ptrHash->hmObjects.find(strKey);

	if(it == ptrHash->hmObjects.end())
		IAS_THROW(RuntimeException("Hash: " + strKey));

	return it->second;
}
/*************************************************************************/
const ::IAS::DM::DataObject* DataObjectList::at(const ::IAS::DM::DataObject* pKey)const{
	IAS_TRACER;
	return const_cast< ::IAS::DM::DataObject* >(static_cast<const IAS::DM::DataObjectList*>(this)->at(pKey) );
}
/*************************************************************************/
void DataObjectList::Hash::insert(::IAS::DM::DataObject* pDataObject){
	IAS_TRACER;

	if(pDataObject == NULL || !pDataObject->isSet(strHashXPath))
		return;

	hmObjects[pDataObject->getString(strHashXPath)] = pDataObject;

}
/*************************************************************************/
void DataObjectList::Hash::remove(::IAS::DM::DataObject* pDataObject){
	IAS_TRACER;

	if(pDataObject == NULL || !pDataObject->isSet(strHashXPath))
			return;

	HashMap::iterator it = hmObjects.find(pDataObject->getString(strHashXPath));

	if(it == hmObjects.end() || it->second != pDataObject)
		return;

	hmObjects.erase(it);
}
/*************************************************************************/
}
}
}
