/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/exception/LMDBException.cpp
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
#include "LMDBException.h"

#include <ds/api/exception/ConstraintViolationException.h>

#include <commonlib/commonlib.h>
#include <sqlite3.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace LMDB{

/*************************************************************************/
LMDBException::LMDBException(){
	IAS_TRACER;
}
/*************************************************************************/
LMDBException::LMDBException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
LMDBException::LMDBException(const String& strInfo, int rc){
	IAS_TRACER;
	this->setInfo(strInfo+", Error: ("+TypeTools::IntToString(rc)+") "+GetErrorString(rc));
}
/*************************************************************************/
LMDBException::~LMDBException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* LMDBException::getName(){
	IAS_TRACER;
	return "LMDBException";
}
/*************************************************************************/
/*************************************************************************/
class ConstraintViolationException :
		public virtual LMDBException,
		public virtual ::IAS::DS::API::ConstraintViolationException{
public:
	ConstraintViolationException(const String& strInfo):
		LMDBException(strInfo, SQLITE_CONSTRAINT){};

	/*************************************************************************/
	const char* getName(){
		IAS_TRACER;
		return "ConstraintViolationException";
	}
};
/*************************************************************************/
/*************************************************************************/
void LMDBException::ThrowOnError(const String& strInfo, int rc){
	IAS_TRACER;

	if(rc == 0)
		return;

	IAS_THROW(LMDBException(strInfo,rc));
}
/*************************************************************************/
const char* LMDBException::GetErrorString(int rc){
	IAS_TRACER;

	switch(rc){

    //TODO error list;

	default:
	 return "No description for this error";
	}

}
/*************************************************************************/
}
}
}
} /* namespace IAS */
