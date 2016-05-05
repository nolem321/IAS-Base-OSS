/*
 * File: IAS-CommonLib/src/commonlib/tools/EnvTools.cpp
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
#include "EnvTools.h"

#include <commonlib/commonlib.h>

#include <stdlib.h>

namespace IAS {

/*************************************************************************/
bool EnvTools::GetEnv(const String& strName, String& strValue){
	IAS_TRACER;

	const char* sValue = getenv(strName.c_str());

	if(sValue == NULL)
		return false;

	strValue=sValue;
	return true;
}
/*************************************************************************/
String EnvTools::GetEnv(const String& strName){
	IAS_TRACER;
	String strValue;

	if(!GetEnv(strName,strValue))
		IAS_THROW(ItemNotFoundException(strName));

	return strValue;
}
/*************************************************************************/
void EnvTools::GetEnvTokenized(const String& strName,
							   StringList& lstValues,
							   char cDelimiter ){
	IAS_TRACER;

	String strValue;
	if(GetEnv(strName,strValue))
		TypeTools::Tokenize(strValue, lstValues, cDelimiter);
}
/*************************************************************************/
}
