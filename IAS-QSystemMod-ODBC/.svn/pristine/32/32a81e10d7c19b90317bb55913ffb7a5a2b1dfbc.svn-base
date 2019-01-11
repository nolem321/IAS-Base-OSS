/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/holder/Base.cpp 
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
#include "Base.h"

#include "../exception/DB2Exception.h"

#include "Text.h"
#include "Float.h"
#include "Integer.h"
#include "Date.h"
#include "Time.h"
#include "DateTime.h"
#include "DataObject.h"

#include "../Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {
namespace Holder {
/*************************************************************************/
Base::Base(Statement* pStatement,
		 DM::Tools::Setter* pSetter,
		 bool bOptional,
		 size_t iBufferSize,
		 SQLSMALLINT     iCType,
		 SQLSMALLINT     iSQLType):
		pStatement(pStatement),
		bOptional(bOptional),
		pSetter(pSetter),
		iPos(0),
		iPrec(0),
		iScale(0),
		iCType(iCType),
		iSQLType(iSQLType),
		bufData(iBufferSize),
		iBindType(SQL_PARAM_TYPE_UNKNOWN),
		bRedefine(false),
		bRebind(false),
		iStrLenOrInd(0){
	IAS_TRACER;
}
/*************************************************************************/
Base::~Base() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Base* Base::Create(Statement* pStatement, DM::Tools::Setter* pSetter, bool bOptional){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"enum: "<<pSetter->getTargetTypeEnum());

	switch(pSetter->getTargetTypeEnum()){

	case DM::Type::TextType:
	case DM::Type::BooleanType:
		return IAS_DFT_FACTORY<Holder::Text>::Create(pStatement,pSetter,bOptional);

	case DM::Type::DateType:
		return IAS_DFT_FACTORY<Holder::Date>::Create(pStatement,pSetter,bOptional);
	case DM::Type::TimeType:
		return IAS_DFT_FACTORY<Holder::Time>::Create(pStatement,pSetter,bOptional);
	case DM::Type::DateTimeType:
		return IAS_DFT_FACTORY<Holder::DateTime>::Create(pStatement,pSetter,bOptional);

	case DM::Type::IntegerType:
		return IAS_DFT_FACTORY<Holder::Integer>::Create(pStatement,pSetter,bOptional);

	case DM::Type::FloatType:
		return IAS_DFT_FACTORY<Holder::Float>::Create(pStatement,pSetter,bOptional);

	case DM::Type::DataObjectType:
	case DM::Type::AnyType:
		return IAS_DFT_FACTORY<Holder::DataObject>::Create(pStatement,pSetter,bOptional);

	default:
		return IAS_DFT_FACTORY<Holder::Text>::Create(pStatement,pSetter,bOptional);

	}
}
/*************************************************************************/
void Base::define(int iPos){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"define: "<<iPos<<", len="<<bufData.getSize());

	SQLRETURN rc = SQLBindCol((SQLHANDLE)*pStatement,
							   iPos,
							   iCType,
							   (SQLPOINTER)bufData.getBuffer<void>(),
							   (SQLINTEGER)bufData.getSize(),
							   &iStrLenOrInd);

	DB2Exception::ThrowOnError(pStatement->getSQLText()+", def="+TypeTools::IntToString(iPos),
								rc,SQL_HANDLE_STMT, (SQLHANDLE)*pStatement);

	this->iPos=iPos;
	bRedefine=true;

}
/*************************************************************************/
void Base::bind(int iPos,SQLSMALLINT iBindType){
	IAS_TRACER;

	if(this->iBindType != iBindType)
		this->iBindType=iBindType;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"bind: "<<iPos<<", len="<<bufData.getSize());

	SQLRETURN rc = SQLBindParameter((SQLHANDLE)*pStatement,
									iPos,
									iBindType,
									iCType,
									iSQLType,
									iPrec,
									0,
								    (SQLPOINTER)bufData.getBuffer<void>(),
								    (SQLINTEGER)bufData.getSize(),
								    &iStrLenOrInd);

	DB2Exception::ThrowOnError(pStatement->getSQLText()+", def="+TypeTools::IntToString(iPos),
								rc,SQL_HANDLE_STMT, (SQLHANDLE)*pStatement);

	bRebind=true;
}
/*************************************************************************/
void  Base::assureBufferSize(size_t iRequestedSize){
	IAS_TRACER;

	//TODO decrease size in some cases.

	if(bufData.getSize() >= iRequestedSize)
		return;

	bufData.reserve(iRequestedSize);

	if(bRebind)
		bind(iPos,iBindType);

	if(bRedefine)
		define(iPos);

}
/*************************************************************************/
}
}
}
}
}


