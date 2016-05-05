/*
 * File: IAS-CommonLib/src/commonlib/configfile/PropertiesProvider.h
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

#ifndef PROPERTIESPROVIDER_H_
#define PROPERTIESPROVIDER_H_

#include"../types.h"

namespace IAS{

/*************************************************************************/
/** The properties provider class.
 *
 */
class PropertiesProvider
{
public:
	PropertiesProvider();
	virtual ~PropertiesProvider();
	
	virtual void getNextProperty(String& strName, String& strValue) = 0;
	virtual void reset() = 0;
	
};

}/* namespace IAS */

#endif /*PROPERTIESPROVIDER_H_*/
