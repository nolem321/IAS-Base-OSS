/*
 * File: IAS-CommonLib/src/commonlib/net/http/Header.cpp
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
#include "Header.h"


namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
Header::Header():
		iConentLength(SIZE_MAX),
		iVersion(HV_1_1){
	IAS_TRACER;
}
/*************************************************************************/
Header::~Header() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Header::Version Header::getVersion()const{
	IAS_TRACER;
	return iVersion;
}
/*************************************************************************/
void Header::setVersion(Version iVersion){
	IAS_TRACER;
	this->iVersion=iVersion;
}
/*************************************************************************/
const String& Header::getTransferEncoding()const{
	IAS_TRACER;
	return strTransferEncoding;
}
/*************************************************************************/
void Header::setTransferEncoding(const String& strTransferEncoding){
	IAS_TRACER;
	this->strTransferEncoding=strTransferEncoding;
}
/*************************************************************************/
const String& Header::getContentType()const{
	IAS_TRACER;
	return strContentType;
}
/*************************************************************************/
void Header::setContentType(const String& strContentType){
	IAS_TRACER;
	this->strContentType=strContentType;
}
/*************************************************************************/
size_t Header::getContentLength()const{
	IAS_TRACER;
	return iConentLength;
}
/*************************************************************************/
void Header::setContentLength(size_t iConentLength){
	IAS_TRACER;
	this->iConentLength=iConentLength;
}
/*************************************************************************/
void Header::setContentLength(const String& strContentLength){
	IAS_TRACER;
	this->iConentLength=TypeTools::StringToInt(strContentLength);
}
/*************************************************************************/
bool  Header::isSetContentLength()const{
	IAS_TRACER;
	return iConentLength != SIZE_MAX;
}
/*************************************************************************/
}
}
}
