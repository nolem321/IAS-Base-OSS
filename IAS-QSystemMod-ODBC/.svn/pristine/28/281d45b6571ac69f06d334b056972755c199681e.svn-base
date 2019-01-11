/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/holder/DataObject.cpp 
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
#include <qs/fmt/FmtFactory.h>

#include "../Session.h"

#include "DataObject.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {
namespace Holder {

/*************************************************************************/
DataObject::DataObject(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional):
	Base(pStatement, pSetter, bOptional, CBufferLen, SQL_C_CHAR, SQL_CLOB){
	IAS_TRACER;
}
/*************************************************************************/
DataObject::~DataObject() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DataObject::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(iStrLenOrInd==SQL_NULL_DATA) {

		if(!bOptional)
			pSetter->unset(dm);

	}else{

		DM::DataObjectPtr dmValue;
		QS::Fmt::Formatter *pFormatter=pStatement->getSession()->getFormatter();
		StringStream ssValue((char*)bufData);
		pFormatter->read(dmValue,ssValue);
		pSetter->setDataObject(dm,dmValue);
	}

}
/*************************************************************************/
void DataObject::feed(DM::DataObjectPtr& dm){
	IAS_TRACER;


	if(pSetter->isSet(dm)){

		DM::DataObjectPtr dmValue;
		QS::Fmt::Formatter *pFormatter=pStatement->getSession()->getFormatter();

		StringStream ssValue;
		pFormatter->write(pSetter->getValue(dm),ssValue);

		//TODO avoid this coping.
		String strValue(ssValue.str());
		String::size_type iSize(strValue.length()+1);

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
