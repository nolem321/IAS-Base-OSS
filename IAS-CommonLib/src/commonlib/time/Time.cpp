/*
 * File: IAS-CommonLib/src/commonlib/time/Time.cpp
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
#include "Time.h"
#include "DateTime.h"


#include <commonlib/commonlib.h>

namespace IAS {

/*************************************************************************/
Time::Time(bool bCurrentSystemDate):Timestamp(bCurrentSystemDate){}
/*************************************************************************/
Time::Time(const Timestamp& other):Timestamp(other){}
Time::Time(const Time& other):Timestamp(other){}
Time::Time(const DateTime& other):Timestamp(other){}
/*************************************************************************/
Time::Time(const char *sValue){
	IAS_TRACER;
	String strValue(sValue);
	fromTimeString(strValue);
}
/*************************************************************************/
Time::Time(const String& strValue){
	IAS_TRACER;
	fromTimeString(strValue);
}
/*************************************************************************/
Time::~Time() throw(){}
/*************************************************************************/
String Time::toString()const{
	return toTimeString();
}
/*************************************************************************/
void Time::fromString(const String& strValue){
	fromTimeString(strValue);
}
/*************************************************************************/

}
