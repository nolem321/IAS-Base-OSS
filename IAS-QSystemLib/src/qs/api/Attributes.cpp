/*
 * File: IAS-QSystemLib/src/qs/api/Attributes.cpp
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
#include "Attributes.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#
namespace IAS {
namespace QS {
namespace API {

/*************************************************************************/
const String& Attributes::CA_MID("MID");
const String& Attributes::CA_CID("CID");
const String& Attributes::CA_Format("FMT");
const String& Attributes::CA_ReplyTo("REPLY_TO");
const String& Attributes::CA_Persistance("PERSISTANCE");
const String& Attributes::CA_Expiration("EXPIRATION");
const String& Attributes::CA_Priority("PRIORITY");
/*************************************************************************/
void Attributes::setValue(const String& strName,
						  const String& strValue){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"["<<strName<<"]=["<<strValue<<"]");

	hmValues[strName]=strValue;
}
/*************************************************************************/
bool Attributes::isSet(const String& strName)const{
	IAS_TRACER;
	return hmValues.count(strName);
}
/*************************************************************************/
const String& Attributes::getValue(const String& strName)const{
	IAS_TRACER;

	if(hmValues.count(strName) == 0)
		IAS_THROW(ItemNotFoundException(String("Attribute:[")+strName+"] not found."));

	return hmValues.at(strName);
}
/*************************************************************************/
void Attributes::unset(const String& strName){
	IAS_TRACER;
	hmValues.erase(strName);
}
/*************************************************************************/
}
}
}
