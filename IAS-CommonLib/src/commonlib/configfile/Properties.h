/*
 * File: IAS-CommonLib/src/commonlib/configfile/Properties.h
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

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include"../types.h"

#include "commonlib/containers/HashMapStringToPointer.h"

namespace IAS{

/*************************************************************************/
/** The simple properties list.
 *
 */

typedef HashMapWithStringKey<String> TPropertiesMap;
class PropertiesProvider;

class Properties
{
public:

	Properties(PropertiesProvider* ptrProvider);
	virtual ~Properties();

	const String& getProperty(const String& strKey) const;

	int getPropertyAsInt(const String& strKey) const;

protected:
	TPropertiesMap  hmProperties;
	friend class ::IAS::Factory<Properties>;
};

}

#endif /*PROPERTIES_H_*/
