/*
 * File: IAS-CommonLib/src/commonlib/tools/SerializationHelper.cpp
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
#include "SerializationHelper.h"

#include "../logger/logger.h"
#include "commonlib/exception/DataException.h"
#include "../exception/BadUsageException.h"
#include "string.h"

namespace IAS {

//TODO (M) real serialization - this is just a mock up
/*************************************************************************/
void SerializationHelper::write(int iValue, std::ostream& os)const{
	IAS_TRACER;

	os<<iValue;
}
/*************************************************************************/
void SerializationHelper::write(const String& strValue, std::ostream& os)const{
	IAS_TRACER;
	os<<strValue;
	os.put(0);
}
/*************************************************************************/
void SerializationHelper::read(int &iValue,  std::istream& is)const{
	IAS_TRACER;
	is>>iValue;
}
/*************************************************************************/
void SerializationHelper::read(String &strValue, std::istream& is)const{
	IAS_TRACER;

	int c;

	strValue.clear();

	while((c=is.get()) != EOF && c != 0){
		strValue+=(char)c;
	}

}
/*************************************************************************/
}
