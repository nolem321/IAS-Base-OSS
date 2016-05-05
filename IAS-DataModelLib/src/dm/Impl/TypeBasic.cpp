/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeBasic.cpp
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
#include "../../dm/Impl/TypeBasic.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
TypeBasic::TypeBasic(const String& strURI,
					 const String& strName,
					 const ::IAS::DM::Type    *pBaseType):
	Type(strURI,strName, pBaseType){
	IAS_TRACER;
}

/*************************************************************************/
TypeBasic::~TypeBasic() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool TypeBasic::isDataObjectType() const{
	return false;
}
/*************************************************************************/
bool TypeBasic::isBaseTypeRestriction() const{
	return true;
}
/*************************************************************************/
const ::IAS::DM::ComplexType* TypeBasic::asComplexType() const{
	IAS_TRACER;
	IAS_THROW(BadUsageException("Not a complex type: "+getFullName()));
}
/*************************************************************************/
::IAS::DM::ComplexType* TypeBasic::asComplexType(){
	IAS_TRACER;
	IAS_THROW(BadUsageException("Not a complex type: "+getFullName()));
}
/*************************************************************************/
}
}
}
