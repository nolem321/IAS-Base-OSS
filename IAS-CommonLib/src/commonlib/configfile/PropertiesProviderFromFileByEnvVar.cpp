/*
 * File: IAS-CommonLib/src/commonlib/configfile/PropertiesProviderFromFileByEnvVar.cpp
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

#include "PropertiesProviderFromFileByEnvVar.h"
#include "../memory/memory.h"
#include "../logger/logger.h"
#include "../exception/ConfigException.h"

#include <stdlib.h>

namespace IAS{

/*************************************************************************/
PropertiesProviderFromFileByEnvVar::PropertiesProviderFromFileByEnvVar(const char *sVariable)
{
	IAS_TRACER;

	IAS_CHECK_IF_NULL(sVariable);

	const char *sValue = getenv(sVariable);

	if(sValue == NULL){
		String sText=sVariable;
		sText+="=?";
		IAS_THROW(ConfigException(sText));
	}

	openFile(sValue);
}

/*************************************************************************/
PropertiesProviderFromFileByEnvVar::PropertiesProviderFromFileByEnvVar(const char *sDirVariable, const char *sFileName)
{
	IAS_TRACER;

	IAS_CHECK_IF_NULL(sDirVariable);
	IAS_CHECK_IF_NULL(sFileName);

	const char *sDirValue = getenv(sDirVariable);

	if(sDirValue == NULL){
		String sText=sDirVariable;
		sText+="=?";
		IAS_THROW(ConfigException(sText));
	}

	String strPath=sDirValue;
	strPath+='/';
	strPath+=sFileName;
	openFile(strPath.c_str());
}

/*************************************************************************/
PropertiesProviderFromFileByEnvVar::~PropertiesProviderFromFileByEnvVar()
{
	IAS_TRACER;
}

}
