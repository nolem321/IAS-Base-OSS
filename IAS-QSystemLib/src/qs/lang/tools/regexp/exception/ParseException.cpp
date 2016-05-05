/*
 * File: IAS-QSystemLib/src/qs/lang/tools/regexp/exception/ParseException.cpp
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
#include "ParseException.h"

#include <commonlib/commonlib.h>

#include<qs/log/LogLevel.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {
namespace RegExp {

/*************************************************************************/
ParseException::ParseException(){
	IAS_TRACER;		
}
/*************************************************************************/
ParseException::ParseException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
ParseException::ParseException(const String& strInfo, int iLine){
	IAS_TRACER;
	this->setInfo(strInfo+" Line: "+TypeTools::IntToString(iLine));
}
/*************************************************************************/
ParseException::~ParseException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* ParseException::getName(){
	IAS_TRACER;
	return "ParseException";
}
/*************************************************************************/
}
}
}
}
} /* namespace IAS */
