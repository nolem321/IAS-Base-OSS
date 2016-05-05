/*
 * File: IAS-DataModelLib/src/dm/Impl/XPathCursor.cpp
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
#include "../../dm/Impl/XPathCursor.h"
#include <commonlib/commonlib.h>
#include "DataObject.h"
#include "../../dm/Impl/DataObject.h"
#include "../../dm/Impl/DataObjectList.h"
#include "../../dm/Impl/exception/RuntimeException.h"
#include "../../dm/Impl/Property.h"
#include "../../dm/Impl/PropertyList.h"
#include "../../dm/Impl/Type.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
XPathCursor::XPathCursor(const ::IAS::DM::DataObject *pDataObject, const String& strXPath) throw() :
	pDataObject(pDataObject),
	pCurrent(pDataObject),
	iIdx(-1),
	iLastIdx(0),
	strXPath(strXPath){

	IAS_TRACER;


	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"["<<strXPath<<"]");
}

/*************************************************************************/
XPathCursor::~XPathCursor() throw(){
	IAS_TRACER;
}

/*************************************************************************/
bool XPathCursor::endOfXPath(){
	IAS_TRACER;
	if(iLastIdx == String::npos || iLastIdx >= strXPath.length())
		return true;
	else
		return false;
}
/*************************************************************************/
bool XPathCursor::extractElement(){
	IAS_TRACER;

	iIdx = -1;

	if(endOfXPath())
		return false;

	size_t iSlashPos = strXPath.find_first_of('/',iLastIdx);
	if(iSlashPos != String::npos){
		strElement = strXPath.substr(iLastIdx,iSlashPos-iLastIdx);
		iLastIdx = iSlashPos + 1;
	}else{
		strElement = strXPath.substr(iLastIdx);
		iLastIdx=String::npos;
	}

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"e1:["<<strElement<<"],iLast="<<iLastIdx<<",iSlash="<<iSlashPos);



	size_t iBracket = strElement.find('[');


	if(iBracket != String::npos){
		iIdx = 0;
		const char *sElement = strElement.c_str() + iBracket + 1;

		while(isdigit(*sElement)){
			iIdx*=10;
			iIdx += *sElement - '0';
			sElement++;
		}

		if(*sElement++ != ']' || *sElement++ != 0 )
			IAS_THROW(RuntimeException(String("Bad xpath: ")+=strXPath));

		strElement=strElement.substr(0,iBracket);
	}else
		iIdx = -1;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"e2:["<<strElement<<"]:"<<iIdx);

	return true;
}
/*************************************************************************/
::IAS::DM::Property *XPathCursor::getElementProperty(){
	IAS_TRACER;
	const ::IAS::DM::Type* pType = pCurrent->getType();

	if(! pType->isDataObjectType())
		IAS_THROW(RuntimeException("Complex type expected."));

	const ::IAS::DM::ComplexType* pComplexType = pType->asComplexType();
	return pComplexType->getProperties().getProperty(strElement);
}
/*************************************************************************/
void XPathCursor::moveCurrentToElement(){
	IAS_TRACER;

	const ::IAS::DM::Property* pProperty = getElementProperty();

	if(pProperty->isMulti()){
		const ::IAS::DM::DataObjectList& refList = pDataObject->getList(pProperty);
		if(iIdx < 0)
			IAS_THROW(RuntimeException("xpath error, an index expected !"))
		pCurrent = refList.at(iIdx);
	}else{
	   pCurrent=pCurrent->getDataObject(pProperty);
	}

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"on:["<<pCurrent->getType()->getName()<<"]");
}
/*************************************************************************/
const ::IAS::DM::DataObject *XPathCursor::getLastChild(){
	IAS_TRACER;

	//TODO parent & #

	while(extractElement())
		moveCurrentToElement();

	return pCurrent;
}
/*************************************************************************/
void XPathCursor::findLastParent(const ::IAS::DM::DataObject* &pParent,
								 const ::IAS::DM::Property*   &pProperty){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"parent1:["<<pCurrent->getType()->getName()<<"]");

	if(!extractElement())
		IAS_THROW(RuntimeException("Complex type expected."));

	while(!endOfXPath()){

		moveCurrentToElement();
		extractElement();

		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"parent2:["<<pCurrent->getType()->getName()<<"]");
	}

	pProperty = getElementProperty();
	pParent = pCurrent;

}
/*************************************************************************/
const ::IAS::DM::DataObject* XPathCursor::GetLastChild(const ::IAS::DM::DataObject *pDataObject,
										     const String& strXPath){

	IAS_TRACER;
	XPathCursor aCursor(pDataObject,strXPath);
	return aCursor.getLastChild();
}
/*************************************************************************/
::IAS::DM::DataObject* XPathCursor::GetLastChild(::IAS::DM::DataObject *pDataObject,
										     const String& strXPath){

	IAS_TRACER;
	XPathCursor aCursor(static_cast<IAS::DM::DataObject*>(pDataObject),strXPath);
	return const_cast<IAS::DM::DataObject*>(aCursor.getLastChild());
}
/*************************************************************************/
void XPathCursor::FindLastParent(const ::IAS::DM::DataObject *pDataObject,
									 const String& strXPath,
									 const ::IAS::DM::DataObject*   &pParent,
									 const ::IAS::DM::Property* &pProperty){
	IAS_TRACER;


	XPathCursor aCursor(pDataObject,strXPath);
	aCursor.findLastParent(pParent, pProperty);
}
/*************************************************************************/
void XPathCursor::FindLastParent(const ::IAS::DM::DataObject *pDataObject,
							     const String& strXPath,
								 ::IAS::DM::DataObject*   &pParent,
								  const ::IAS::DM::Property* &pProperty){
	IAS_TRACER;

	XPathCursor aCursor(static_cast<const IAS::DM::DataObject*>(pDataObject),strXPath);
	const ::IAS::DM::DataObject*   pParentTmp;
	aCursor.findLastParent(pParentTmp, pProperty);
	pParent = const_cast<IAS::DM::DataObject*>(pParentTmp);

}
/*************************************************************************/
}
}
}
