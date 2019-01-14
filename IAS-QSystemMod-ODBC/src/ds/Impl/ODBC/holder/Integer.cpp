/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/holder/Integer.cpp
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
#include "Integer.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {
namespace Holder {

/*************************************************************************/
Integer::Integer(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional, CBufferLen, SQL_C_LONG,SQL_INTEGER){
	IAS_TRACER;
}
/*************************************************************************/
Integer::~Integer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Integer::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(iStrLenOrInd==SQL_NULL_DATA) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value=["<<*(bufData.getBuffer<SQLINTEGER>())<<"]");
		pSetter->setInteger(dm,*(bufData.getBuffer<SQLINTEGER>()));
	}

}
/*************************************************************************/
void Integer::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(pSetter->isSet(dm)){

		*(bufData.getBuffer<SQLINTEGER>())=pSetter->getValue(dm)->toInteger();
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value=["<<*(bufData.getBuffer<SQLINTEGER>())<<"]");
		iStrLenOrInd=CBufferLen;
	}else{
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"is NULL");
		iStrLenOrInd=SQL_NULL_DATA;
	}

}
/*************************************************************************/
}
}
}
}
}
