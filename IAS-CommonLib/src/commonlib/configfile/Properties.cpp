/*
 * File: IAS-CommonLib/src/commonlib/configfile/Properties.cpp
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#include "Properties.h"

#include "../logger/logger.h"
#include "../exception/ConfigException.h"
#include "../exception/ItemNotFoundException.h"
#include "../memory/memory.h"

#include "../tools/TypeTools.h"

#include "PropertiesProvider.h"


namespace IAS
{
/*************************************************************************/
 Properties::Properties(PropertiesProvider* ptrProvider){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(ptrProvider);

	String strName;
	String strValue;

	try{
		while(true){

			ptrProvider->getNextProperty(strName,strValue);
			hmProperties[strName]=strValue;

			IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),
					"["<<strName<<"]=["<<strValue<<"]")
		}

	}catch(ItemNotFoundException& e){
		/* nothing more to do */
	}catch(std::exception& e){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Some error while reading properties:"<<e.what());
	}
}

/*************************************************************************/
Properties::~Properties(){
	IAS_TRACER;
}

/*************************************************************************/
const String& Properties::getProperty(const String& strKey) const{
	IAS_TRACER;

	TPropertiesMap::const_iterator it=hmProperties.find(strKey);

	if(it == hmProperties.end()){
		IAS_THROW(ItemNotFoundException(strKey));
	}

	return it->second;
}
/*************************************************************************/
int Properties::getPropertyAsInt(const String& strKey) const{
	IAS_TRACER;
	return TypeTools::StringToInt(getProperty(strKey));
}


}
