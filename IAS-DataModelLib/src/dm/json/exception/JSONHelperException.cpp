/*
 * File: IAS-DataModelLib/src/dm/json/exception/JSONHelperException.cpp
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
#include "../../../dm/json/exception/JSONHelperException.h"
#include <commonlib/commonlib.h>

namespace IAS{
namespace DM {
namespace JSON {

/*************************************************************************/
JSONHelperException::JSONHelperException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
JSONHelperException::JSONHelperException(const String& strInfo, int iLine){
	IAS_TRACER;
	StringStream ssTmp;
	ssTmp<<strInfo<<", line:"<<iLine;
	this->setInfo(ssTmp.str());
}
/*************************************************************************/
JSONHelperException::~JSONHelperException() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const char* JSONHelperException::getName(){
	IAS_TRACER;
	return "JSONHelperException";
}


/*************************************************************************/

} /* namespace Impl */
} /* namespace DM */
} /* namespace IAS */
