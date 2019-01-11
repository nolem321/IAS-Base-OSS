/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/StatementDelete.cpp 
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
#include "StatementDelete.h"
#include "exception/DB2Exception.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
StatementDelete::StatementDelete(Session* pSession):
		DB2::Statement(pSession),
		Input(*(DB2::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementDelete::~StatementDelete() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
