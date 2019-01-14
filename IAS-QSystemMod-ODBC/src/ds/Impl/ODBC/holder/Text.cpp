/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/holder/Text.cpp 
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
#include "Text.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {
namespace Holder {

/*************************************************************************/
Text::Text(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	 Base(pStatement, pSetter, bOptional,CBufferLen,SQL_C_CHAR,SQL_VARCHAR){
	IAS_TRACER;
}
/*************************************************************************/
Text::~Text() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Text::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(iStrLenOrInd==SQL_NULL_DATA) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		bufData.getBuffer<char>()[iStrLenOrInd]=0;
		String strValue((const char*)bufData);
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<strValue<<", len="<<iStrLenOrInd);
		pSetter->setString(dm,strValue);
	}

}
/*************************************************************************/
void Text::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;


	if(pSetter->isSet(dm)){

		String strValue(pSetter->getValue(dm)->toString());

		//TODO consider resize & rebind ?
		String::size_type iSize(strValue.length()+1);

		//TODO remove if resize works. if(iSize + 1 > bufData.getSize())
		//	IAS_THROW(BadUsageException("String value too long for oracle text place holder."));

		assureBufferSize(iSize);

		memcpy((char*)bufData,strValue.c_str(),iSize);

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"value="<<(char*)bufData);
		iStrLenOrInd=SQL_NTS;

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
