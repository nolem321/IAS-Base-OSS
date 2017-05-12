/*
 * File: IAS-DataModelLib/src/dm/xml/XMLDocument.cpp
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
#include "../../dm/xml/XMLDocument.h"
#include <commonlib/commonlib.h>

#include "../../dm/DataObject.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Type.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
XMLDocument::XMLDocument(DataObject *pRootObject):
		strEncoding("UTF-8"),
		strVersion("1.0"),
		ptrRootObject(pRootObject){

	IAS_TRACER;

	setDefaultElement();
}
/*************************************************************************/
XMLDocument::~XMLDocument() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void XMLDocument::setDefaultElement(){
	IAS_TRACER;

	if(!ptrRootObject)
		return;


	const DM::Type* pType=ptrRootObject->getType();

	strElement=pType->getName();
	strElement[0]=tolower((int)(strElement[0]));

	strURI=pType->getURI();

}
/*************************************************************************/
DataObject *XMLDocument::getRootObject() const{
	IAS_TRACER;
	if(ptrRootObject == NULL)
		IAS_THROW(ItemNotFoundException("XMLDocument/RootObject"));
	return ptrRootObject;
}
/*************************************************************************/
void XMLDocument::setRootObject(DataObject *pRootObject){
	IAS_TRACER;

	if(!pRootObject){
		IAS_THROW(BadUsageException("XMLDocument: RootObject is NULL"));
	}

	if(this->ptrRootObject.isNull() || strElement.length() == 0){
		strElement=pRootObject->getType()->getName();
		strElement[0]=tolower(strElement[0]);
	}

	this->ptrRootObject=pRootObject;
}
/*************************************************************************/
void XMLDocument::setVersion(const String& strVersion){
	IAS_TRACER;
	this->strVersion=strVersion;
}
/*************************************************************************/
void XMLDocument::setEncoding(const String& strEncoding){
	IAS_TRACER;
	this->strEncoding=strEncoding;
}
/*************************************************************************/
void XMLDocument::setElement(const String& strElement){
	IAS_TRACER;
	this->strElement=strElement;
}
/*************************************************************************/
void XMLDocument::setURI(const String& strURI){
	IAS_TRACER;
	this->strURI=strURI;
}
/*************************************************************************/
}
}
}
