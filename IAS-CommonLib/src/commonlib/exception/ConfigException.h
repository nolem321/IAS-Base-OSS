/*
 * File: IAS-CommonLib/src/commonlib/exception/ConfigException.h
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
/* ChangeLog:
 * 
 */

#ifndef _IAS_ConfigException_H_
#define _IAS_ConfigException_H_

#include "Exception.h"

namespace IAS{

/*************************************************************************/
/** The ConfigException exception class.
 */

 class ConfigException : public IAS::Exception{
	
public:
	
	ConfigException(const char *sInfo,
					const char *sFileName=NULL,
					int         iLineNo = -1);

	ConfigException(const String& strInfo);
	
	ConfigException(const String& strInfo,
			  		const String& strFileName,
					int iLineNo = -1);
	
	virtual ~ConfigException() throw();
	
	virtual const char*  getName();
};

}

#endif /*CONFIG_EXCEPTION_H_*/
