/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/exception/DB2Exception.h 
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

#ifndef _IAS_DS_API_DB2Exception_H_
#define _IAS_DS_API_DB2Exception_H_

#include <ds/api/exception/Exception.h>

#include <sqlcli.h>
#include <sqlda.h>
#include <sqlca.h>


namespace IAS{
namespace DS{
namespace Impl{
namespace DB2{
/*************************************************************************/
/** The DB2Exception exception class.
 */

class DB2Exception : public ::IAS::DS::API::Exception {

public:
	DB2Exception();
	DB2Exception(const String& strInfo);
	DB2Exception(const String& strInfo, int rc);
	virtual ~DB2Exception() throw();
	
	virtual const char*  getName();

	static void ThrowOnError(const String& strInfo, int rc, SQLSMALLINT htype, SQLHANDLE hndl);

	//static const char* GetErrorString(int rc);
};

}
}
}
}

#endif /*_IAS_DS_API_DB2Exception_H_*/

