/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/cache/Context.cpp
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
#include "Context.h"

#include <qs/log/LogLevel.h>

#include "../../GlobalContext.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace Storage {

/*************************************************************************/
Context::Context(GlobalContext *pGlobalContext)throw(){
	IAS_TRACER;
}

/*************************************************************************/
Context::~Context() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Context::clear(){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Clearing local storage ... ");
	hmLocalValues.clear();
}
/*************************************************************************/
void Context::setLocalValue(const String& strKey, DM::DataObject* dm){
	IAS_TRACER;

	hmLocalValues[strKey]=dm;
}
/*************************************************************************/
DM::DataObject* Context::getLocalValue(const String& strKey){
	IAS_TRACER;

	if(hmLocalValues.count(strKey) == 0)
		IAS_THROW(ItemNotFoundException(String("Storage value not found for: "+strKey)));

	return hmLocalValues.at(strKey);
}
/*************************************************************************/
void Context::setGlobalValue(const String& strKey, DM::DataObject* dm){
	IAS_TRACER;

	hmGlobalValues[strKey]=dm;
}
/*************************************************************************/
DM::DataObject* Context::getGlobalValue(const String& strKey){
	IAS_TRACER;

	if(hmGlobalValues.count(strKey) == 0)
		IAS_THROW(ItemNotFoundException(String("Storage value not found for: "+strKey)));

	return hmGlobalValues.at(strKey);
}
/*************************************************************************/
}
}
}
}
}
}
