/*
 * File: IAS-QSystemLib/src/qs/Impl/base/Attributes.cpp
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
#include "Attributes.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Base {

/*************************************************************************/
Attributes::Attributes(){
	IAS_TRACER;
}/*************************************************************************/
Attributes::Attributes(const API::Attributes& other){
	IAS_TRACER;

	for(API::Attributes::const_iterator it=other.begin();
		it != other.end(); it++)
	hmValues[it->first]=it->second;
}
/*************************************************************************/
Attributes::~Attributes() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Attributes::read(std::istream& inStream){
	IAS_TRACER;

	String strName;
	String strValue;

	while(!inStream.eof()){

		getline(inStream,strName,'\t');
		getline(inStream,strValue,'\n');

		if(!inStream.eof() && !strName.empty())
			setValue(strName,strValue);
	}
}
/*************************************************************************/
void Attributes::write(std::ostream& outStream) const{
	IAS_TRACER;

	for(ValuesMap::const_iterator it=hmValues.begin();
		it != hmValues.end();
		it++) if(it->first[0] != '.') {

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"["<<it->first<<"]=["<<it->second<<"]");
		outStream<<it->first<<'\t'<<it->second<<'\n';
	}
	outStream.flush();
}
/*************************************************************************/

}
}
}
