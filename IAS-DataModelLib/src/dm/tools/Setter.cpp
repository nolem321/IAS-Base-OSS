/*
 * File: IAS-DataModelLib/src/dm/tools/Setter.cpp
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
#include "../../dm/tools/Setter.h"

#include "../../dm/DataObjectList.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Property.h"
#include "../../dm/PropertyList.h"
#include "../../dm/RuntimeException.h"

namespace IAS {
namespace DM {
namespace Tools {

/*************************************************************************/
Setter::Setter(const String& strXPath,
		       const Type* pType):
		strXPath(strXPath),
		pType(pType),
		pTargetType(NULL){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"new: "<<strXPath<<", at ="<<(void*)this);

	buildElementList();

	IAS_CHECK_IF_NULL(pTargetType);
}
/*************************************************************************/
Setter::~Setter() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Setter::buildElementList(){
	IAS_TRACER;

	const char *sCursor=strXPath.c_str();

	if(*sCursor == '#' || *sCursor == '/')
		IAS_THROW(Impl::RuntimeException("Absolute xpaths are not supported."));

	const Type* pTypeCursor=pType;

	while(*sCursor){

		String strProperty;
		int iIdx=Element::CSingle;

		while(*sCursor != 0 && *sCursor != '[' && *sCursor != '/' )
			strProperty+=*sCursor++;

		if(strProperty[0]=='.')
			IAS_THROW(Impl::RuntimeException("Usage of '..' is not supported."));

		if(*sCursor == '['){

			sCursor++;
			iIdx=0;

			while(isdigit(*sCursor))
				iIdx = iIdx * 10 + *sCursor++ - '0';

			if(*sCursor != ']')
				IAS_THROW(Impl::RuntimeException(String("Bad XPath: ")+=strXPath));
		}


		const Property* pProperty=pTypeCursor->asComplexType()->getProperties().getProperty(strProperty);

		pTypeCursor=pProperty->getType();

		if(*sCursor){
			sCursor++;
		}

		lstPath.push_back(Element(pProperty,iIdx));

		if(*sCursor == '/')
			sCursor++;

	}while(*sCursor != 0);

	pTargetType=pTypeCursor;

}
/*************************************************************************/
DM::DataObject* Setter::getParent(DM::DataObject* pCursor, bool bCreateIfNeeded)const{
	IAS_TRACER;

	DM::DataObject* pParent=pCursor;
	IAS_CHECK_IF_NULL(pCursor);

	ElementList::const_iterator itStop=lstPath.end();
	itStop--;
	for(ElementList::const_iterator it=lstPath.begin(); it != itStop; it++){

		if((*it).pProperty->isMulti()){
			DataObjectList& lstCursor(pCursor->getList((*it).pProperty));
			if(lstCursor.size() > (*it).iIdx){
				pCursor=lstCursor.at((*it).iIdx);
			}else if(lstCursor.size() == (*it).iIdx && bCreateIfNeeded){
				pCursor=(*it).pProperty->getType()->createDataObject();
				lstCursor.add(pCursor);
			}else{
				IAS_THROW(Impl::RuntimeException()<<"List index out of range:"<<(*it).iIdx<<" of "<<lstCursor.size());
			}

		}else{
				if(pCursor->isSet((*it).pProperty) ){
					pCursor=pCursor->getDataObject((*it).pProperty);
				}else{

					if(bCreateIfNeeded){
						pCursor=pCursor->createDataObject((*it).pProperty);
					}else{
						IAS_THROW(Impl::RuntimeException(String("Property not set: ")+=(*it).pProperty->getName()));
					}
				}
		}

		pParent=pCursor;
	}

	IAS_CHECK_IF_NULL(pParent);

	return pParent;
}
/*************************************************************************/
void Setter::setDataObject(DataObjectPtr& dm,DM::DataObject* pDMValue)const{
	IAS_TRACER;

	if(lstPath.size())
		getParent(dm,true)->setDataObject(lstPath.back().pProperty,pDMValue);
	else
		dm=pDMValue;
}
/*************************************************************************/
void Setter::setString(DataObjectPtr& dm,const String& strValue)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),strXPath<<"="<<strValue);

	if(lstPath.size())
		getParent(dm,true)->setString(lstPath.back().pProperty,strValue);
	else{

		if(!dm)
			dm=pType->createDataObject(strValue);
		else
			dm->setString(strValue);
	}

}
/*************************************************************************/
void Setter::setDate(DataObjectPtr& dm,const IAS::Date& tsValue)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),strXPath<<"="<<tsValue.toString());

	if(lstPath.size())
		getParent(dm,true)->setDate(lstPath.back().pProperty,tsValue);
	else{
		if(!dm)
			dm=pType->createDataObject(tsValue);
		else
			dm->setDate(tsValue);
	}

}
/*************************************************************************/
void Setter::setTime(DataObjectPtr& dm,const IAS::Time& tsValue)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),strXPath<<"="<<tsValue.toString());

	if(lstPath.size())
		getParent(dm,true)->setTime(lstPath.back().pProperty,tsValue);
	else{
		if(!dm)
			dm=pType->createDataObject(tsValue);
		else
			dm->setTime(tsValue);
	}

}
/*************************************************************************/
void Setter::setDateTime(DataObjectPtr& dm,const IAS::DateTime& tsValue)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),strXPath<<"="<<tsValue.toString());

	if(lstPath.size())
		getParent(dm,true)->setDateTime(lstPath.back().pProperty,tsValue);
	else{
		if(!dm)
			dm=pType->createDataObject(tsValue);
		else
			dm->setDateTime(tsValue);
	}

}
/*************************************************************************/
void Setter::setInteger(DataObjectPtr& dm,int iValue)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),strXPath<<"="<<iValue);

	if(lstPath.size())
		getParent(dm,true)->setInteger(lstPath.back().pProperty,iValue);
	else{
		if(!dm)
			dm=pType->createDataObject(iValue);
		else
			dm->setInteger(iValue);
	}

}
/*************************************************************************/
void Setter::setFloat(DataObjectPtr& dm,Float fValue)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),strXPath<<"="<<fValue);

	if(lstPath.size())
		getParent(dm,true)->setInteger(lstPath.back().pProperty,fValue);
	else{
		if(!dm)
			dm=pType->createDataObject(fValue);
		else
			dm->setInteger(fValue);
	}

}
/*************************************************************************/
void Setter::setBoolean(DataObjectPtr& dm,bool bValue)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),strXPath<<"="<<bValue);

	if(lstPath.size())
		getParent(dm,true)->setInteger(lstPath.back().pProperty,bValue);
	else{
		if(!dm)
			dm=pType->createDataObject(bValue);
		else
			dm->setInteger(bValue);
	}

}
/*************************************************************************/
DM::DataObject* Setter::getValue(DM::DataObject* dm)const{
	IAS_TRACER;

	return const_cast<DM::DataObject*>(getValue(const_cast<const DM::DataObject*>(dm)));
}
/*************************************************************************/
const DM::DataObject* Setter::getValue(const DM::DataObject* dm)const{

	IAS_TRACER;

	if(lstPath.size()){

		for(ElementList::const_iterator it=lstPath.begin(); it != lstPath.end(); it++){


			if((*it).pProperty->isMulti())
				dm=dm->getList((*it).pProperty).at((*it).iIdx);
			else
				dm=dm->getDataObject((*it).pProperty);

		}

	}
	return dm;
}
/*************************************************************************/
bool Setter::isSet(const DM::DataObject* dm)const{

	IAS_TRACER;

	if(lstPath.size()){

		for(ElementList::const_iterator it=lstPath.begin(); it != lstPath.end(); it++){

			if((*it).pProperty->isMulti()){

				const DM::DataObjectList& list(dm->getList((*it).pProperty));

				if((*it).iIdx >= list.size())
					return false;

				dm=list.at((*it).iIdx);

			}else{

				if(!dm->isSet((*it).pProperty))
					return false;

				dm=dm->getDataObject((*it).pProperty);
			}
		}

	}
	return true;
}
/*************************************************************************/
void Setter::unset(DM::DataObjectPtr& dm){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"unset: "<<strXPath);

	// this may be faster than dm=getParent(dm,false);dm->unset(lstPath.back().pProperty);
	if(lstPath.size())
		dm->unset(strXPath);
	else
		dm=0;

}
/*************************************************************************/
DM::DataObject* Setter::create(DM::DataObjectPtr& dm)const{
	IAS_TRACER;

	if(lstPath.size()){
		return getParent(dm,true)->createDataObject(lstPath.back().pProperty);
	}else
		return dm=pTargetType->createDataObject();
}
/*************************************************************************/
const DM::Type*  Setter::getTargetType() const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"type: "<<pTargetType->getName());

	return pTargetType;
}
/*************************************************************************/
const DM::Type::Types Setter::getTargetTypeEnum() const{
	IAS_TRACER;
	return pTargetType->getTypeEnum();
}
/*************************************************************************/
}
}
}
