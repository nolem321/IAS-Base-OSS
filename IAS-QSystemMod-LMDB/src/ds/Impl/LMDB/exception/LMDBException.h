/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/exception/LMDBException.h
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

#ifndef _IAS_DS_API_LMDBException_H_
#define _IAS_DS_API_LMDBException_H_

#include <ds/api/exception/RuntimeException.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace LMDB{
/*************************************************************************/
/** The LMDBException exception class.
 */

class LMDBException : public virtual ::IAS::DS::API::RuntimeException {

public:
	LMDBException();
	LMDBException(const String& strInfo);
	LMDBException(const String& strInfo, int rc);
	virtual ~LMDBException() throw();
	
	virtual const char*  getName();

	static void ThrowOnError(const String& strInfo, int rc);

	static const char* GetErrorString(int rc);
};

}
}
}
}

#endif /*_IAS_DS_API_LMDBException_H_*/

