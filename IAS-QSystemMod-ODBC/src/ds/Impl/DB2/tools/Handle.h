/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/tools/Handle.h 
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
#ifndef _IAS_DS_Oracle_Tools_Handle_H_
#define _IAS_DS_Oracle_Tools_Handle_H_

#include <commonlib/commonlib.h>
#include <ds/api/Connection.h>

#include "../exception/DB2Exception.h"

#include <sqlcli1.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {
namespace Tools {
class System;

/*************************************************************************/
/** The Connection class.
 *
 */
template<int _handle_id>
class Handle {
public:

	static const SQLSMALLINT handle_id=_handle_id;

	Handle():pHandle(0){}

	Handle(SQLHANDLE parent):pHandle(0){
		initialize(parent);
	}

	~Handle(){
		free();
	}

	inline void initialize(SQLHANDLE parent){
		free();
		SQLRETURN rc = SQLAllocHandle(handle_id, parent,&pHandle);
		DB2Exception::ThrowOnError("Handle error",rc,SQL_HANDLE_DBC, parent);
	}

	inline void free(){
		if(pHandle)
			SQLFreeHandle(handle_id,pHandle);
		pHandle=0;
	}


	inline operator SQLHANDLE(){ return pHandle; }
	inline operator const SQLHANDLE()const{ return pHandle; }

	inline SQLHANDLE get(){ return pHandle;};
	inline const SQLHANDLE get()const { return pHandle;};

protected:

	inline bool operator!()const{ return !pHandle;}
	//inline handle_type** operator &(){ return &pHandle; }

	SQLHANDLE pHandle;
};
/*************************************************************************/
//typedef Handle<OCIEnv,OCI_HTYPE_ENV>     HandleEnv;
typedef Handle<SQL_HANDLE_STMT>  HandleStatement;
/*************************************************************************/

}
}
}
}
}
#endif /* _IAS_DS_Oracle_Tools_Handle_H_ */
