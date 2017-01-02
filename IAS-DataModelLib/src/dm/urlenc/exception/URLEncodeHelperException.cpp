/*
 * File: IAS-DataModelLib/src/dm/urlenc/exception/URLEncodeHelperException.cpp
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
#include "../../../dm/urlenc/exception/URLEncodeHelperException.h"
#include <commonlib/commonlib.h>

namespace IAS{
namespace DM {
namespace URLEnc {

/*************************************************************************/
URLEncodeHelperException::URLEncodeHelperException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
URLEncodeHelperException::URLEncodeHelperException(const String& strInfo, int iLine){
	IAS_TRACER;
	StringStream ssTmp;
	ssTmp<<strInfo<<", line:"<<iLine;
	this->setInfo(ssTmp.str());
}
/*************************************************************************/
URLEncodeHelperException::~URLEncodeHelperException() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const char* URLEncodeHelperException::getName(){
	IAS_TRACER;
	return "URLEncodeHelperException";
}


/*************************************************************************/

} /* namespace Impl */
} /* namespace DM */
} /* namespace IAS */
