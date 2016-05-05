/*
 * File: IAS-DataModelLib/src/dm/Impl/Property.cpp
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
#include "../../dm/Impl/Property.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
Property::Property(const String& strName,
		const ::IAS::DM::Type* pType,
		int iIdx,
		bool bIsMulti,
		bool bIsXMLAttribute,
		const String& strDescription){

	IAS_TRACER;

	this->strName=strName;
	this->pType=pType;
	this->bIsMulti=bIsMulti;
	this->iIdx=iIdx;
	this->bIsXMLAttribute=bIsXMLAttribute;
	this->strDescription = strDescription;
}
/*************************************************************************/
Property::~Property() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const String& Property::getName() const{
	IAS_TRACER;
	return strName;
}
/*************************************************************************/
const String& Property::getDescription() const{
	IAS_TRACER;
	return strDescription;
}
/*************************************************************************/
const ::IAS::DM::Type*  Property::getType() const{
	return pType;
}
/*************************************************************************/
bool Property::isMulti() const{
	return bIsMulti;
}
/*************************************************************************/
bool Property::isXMLAttribute() const{
	return bIsXMLAttribute;
}
/*************************************************************************/
int Property::getIdx() const{
	return iIdx;
}
/*************************************************************************/
}
}
}
