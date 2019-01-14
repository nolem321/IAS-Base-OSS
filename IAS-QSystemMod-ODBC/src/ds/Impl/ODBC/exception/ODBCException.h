/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/exception/ODBCException.h
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License.
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 *
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 *
 */
/* ChangeLog:
 *
 */

#ifndef _IAS_DS_API_ODBCException_H_
#define _IAS_DS_API_ODBCException_H_

#include <ds/api/exception/Exception.h>

#include <sql.h>
#include <sqlext.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace ODBC{
/*************************************************************************/
/** The ODBCException exception class.
 */

class ODBCException : public ::IAS::DS::API::Exception {

public:
	ODBCException();
	ODBCException(const String& strInfo);
	ODBCException(const String& strInfo, int rc);
	virtual ~ODBCException() throw();

	virtual const char*  getName();

	static void ThrowOnError(const String& strInfo,
                           SQLRETURN rc,
                           SQLHANDLE handle,
                           SQLSMALLINT type);

	//static const char* GetErrorString(int rc);
};

}
}
}
}

#endif /*_IAS_DS_API_ODBCException_H_*/

