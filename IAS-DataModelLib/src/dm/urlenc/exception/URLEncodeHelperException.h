/*
 * File: IAS-DataModelLib/src/dm/urlenc/exception/URLEncodeHelperException.h
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

#ifndef _IAS_DM_JSON_Exception_URLEncodeHelperException_H_
#define _IAS_DM_JSON_Exception_URLEncodeHelperException_H_


#include <commonlib/commonlib.h>

#include "../../../dm/RuntimeException.h"

namespace IAS {
namespace DM {
namespace URLEnc {

class Type;

class URLEncodeHelperException :
	public ::IAS::DM::RuntimeException {

public:

	URLEncodeHelperException(const String& str);
	URLEncodeHelperException(const String& str, int iLine);

	virtual ~URLEncodeHelperException() throw();

	virtual const char*  getName();
};


}
}
}

#endif /*_IAS_DM_JSON_Exception_URLEncodeHelperException_H_*/
