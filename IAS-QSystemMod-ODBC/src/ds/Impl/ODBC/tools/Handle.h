/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/tools/Handle.h
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
#ifndef _IAS_DS_ODBC_Tools_Handle_H_
#define _IAS_DS_ODBC_Tools_Handle_H_

#include <commonlib/commonlib.h>
#include <ds/api/Connection.h>

#include "../exception/ODBCException.h"

#include <sql.h>
#include <sqlext.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {
namespace Tools {

/*************************************************************************/
/** The Connection class.
 *
 */
template<typename _handle_type, int _handle_id>
class Handle {
public:

	typedef _handle_type handle_type;
	static const int handle_id=_handle_id;

	Handle():pHandle(0){
    initialize(SQL_NULL_HANDLE);
  }

	Handle(SQLHANDLE parent):pHandle(0){
		initialize(parent);
	}

	~Handle(){
		free();
	}

	inline void initialize(SQLHANDLE parent){
		free();
		SQLINTEGER rc=SQLAllocHandle(handle_id, parent, (handle_type*) &pHandle);
    IAS_LOG(true,"Handle: "<<(void*)pHandle);
		//ODBCException::ThrowOnError("AllocateHandle",0,0,0);
	}

	inline void free(){
		if(pHandle)
			SQLFreeHandle(handle_id, pHandle);
		pHandle=0;
	}

  void checkForErrors(const String& strInfo, SQLRETURN rc) {
    ODBCException::ThrowOnError(strInfo,rc, pHandle, handle_id);
  }

	inline operator handle_type(){ return pHandle; }
	inline operator const handle_type()const{ return pHandle; }

	inline handle_type get(){ return pHandle;};
	inline const handle_type get()const { return pHandle;};

protected:

	inline bool operator!()const{ return !pHandle;}
	//inline handle_type** operator &(){ return &pHandle; }

	handle_type pHandle;
};

/*************************************************************************/
typedef Handle<SQLHDBC, SQL_HANDLE_DBC>   HandleDBC;
typedef Handle<SQLHENV, SQL_HANDLE_ENV>   HandleEnv;
typedef Handle<SQLHSTMT, SQL_HANDLE_STMT>  HandleStatement;
/*************************************************************************/

}
}
}
}
}
#endif /* _IAS_DS_ODBC_Tools_Handle_H_ */
