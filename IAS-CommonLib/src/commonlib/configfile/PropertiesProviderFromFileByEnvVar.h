/*
 * File: IAS-CommonLib/src/commonlib/configfile/PropertiesProviderFromFileByEnvVar.h
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

#ifndef PROPERTIESPROVIDERFROMFILEBYENVVAR_H_
#define PROPERTIESPROVIDERFROMFILEBYENVVAR_H_

#include "PropertiesProviderFromFile.h"

namespace IAS{

/*************************************************************************/
/** The properties provider for a file pointed by an environment variable.
 */

class PropertiesProviderFromFileByEnvVar : public IAS::PropertiesProviderFromFile
{
public:
	PropertiesProviderFromFileByEnvVar(const char *sVariable);
	PropertiesProviderFromFileByEnvVar(const char *sDirVariable, const char *sFileName);
	virtual ~PropertiesProviderFromFileByEnvVar();

	friend class ::IAS::Factory<PropertiesProviderFromFileByEnvVar>;
};

}

#endif /*PROPERTIESPROVIDERFROMFILEBYENVVAR_H_*/
