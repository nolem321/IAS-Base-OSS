/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/exception/PostgreSQLException.h
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

#ifndef _IAS_DS_API_PostgreSQLException_H_
#define _IAS_DS_API_PostgreSQLException_H_

#include <ds/api/exception/RuntimeException.h>

#include "libpq-fe.h"

namespace IAS{
namespace DS{
namespace Impl{
namespace PostgreSQL{
/*************************************************************************/
/** The PostgreSQLException exception class.
 */

class PostgreSQLException : public virtual ::IAS::DS::API::RuntimeException {

public:
	PostgreSQLException();
	PostgreSQLException(const String& strInfo);
	PostgreSQLException(const String& strInfo, PGconn    *conn);

	virtual ~PostgreSQLException() throw();
	
	virtual const char*  getName();

	static void ThrowOnError(const String& strInfo, PGconn   *conn);
	static void ThrowOnError(const String& strInfo, PGconn   *conn, PGresult *res);

	static const char* GetErrorString(int rc);
};

}
}
}
}

#endif /*_IAS_DS_API_PostgreSQLException_H_*/

