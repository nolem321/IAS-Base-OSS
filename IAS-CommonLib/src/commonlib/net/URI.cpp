/*
 * File: IAS-CommonLib/src/commonlib/net/URI.cpp
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
#include "URI.h"
#include <commonlib/commonlib.h>

#include <commonlib/tools/TypeTools.h>

namespace IAS {

/*************************************************************************/
URI::URI(const String& strValue):
		iPort(0),
		strValue(strValue),
		ssValue(strValue){
	IAS_TRACER;

	if(!strValue.empty())
		parse();
}
/*************************************************************************/
void URI::copy(const URI& other){
	IAS_TRACER;

	this->strProtocol=other.strProtocol;
	this->strHost=other.strHost;
	this->iPort=other.iPort;
	this->strPath=other.strPath;
	this->strUser=other.strUser;
	this->strPassword=other.strPassword;

	if(!other.strValue.empty())
		this->strValue=other.strValue;
	else
		strValue.clear();

}
/*************************************************************************/
void URI::setProtocol(const String& strProtocol){
	IAS_TRACER;
	this->strProtocol=strProtocol;
	strValue.clear();
}
/*************************************************************************/
void URI::setHost(const String& strHost){
	IAS_TRACER;
	this->strHost=strHost;
	strValue.clear();
}
/*************************************************************************/
void URI::setPath(const String& strPath){
	IAS_TRACER;
	this->strPath=strPath;
	strValue.clear();
}
/*************************************************************************/
void URI::setPort(unsigned int iPort){
	IAS_TRACER;
	this->iPort=iPort;
	strValue.clear();
}
/*************************************************************************/
void URI::setUser(const String& strUser){
	IAS_TRACER;
	this->strUser=strUser;
	strValue.clear();
}
/*************************************************************************/
void URI::setPassword(const String& strPassword){
	IAS_TRACER;
	this->strPassword=strPassword;
	strValue.clear();
}
/*************************************************************************/
const String& URI::getURIString()const{
	IAS_TRACER;

	if(strValue.empty()){

		StringStream ssValue;
		ssValue<<strProtocol<<"://";
		if(!strUser.empty()){
			ssValue<<strUser;
			if(!strPassword.empty()){
				ssValue<<":"<<strPassword;
			}
			ssValue<<"@";
		}

		ssValue<<strHost;
		if(iPort>0)
			ssValue<<":"<<iPort;

		ssValue<<"/"<<strPath;

		if(hmValues.size() > 0){
			for(ValuesMap::const_iterator it=hmValues.begin(); it != hmValues.end(); it++){
				ssValue<<(it == hmValues.begin() ? '?' : '&');
				ssValue<<it->first<<"="<<it->second;
			}
		}

		//No one will should know that we update the cache.
		const_cast<URI*>(this)->strValue=ssValue.str();
	}

	return strValue;
}
/*************************************************************************/
void URI::parse(){
	IAS_TRACER;

	parseProtocol();
	asset(":");
	asset("/");
	asset("/");
	parseDomain();

	if(ssValue.eof())
		return;

	char c=ssValue.get();

	if(c == '@'){
		strUser=strHost;
		strHost.clear();
		parseDomain();
		c=ssValue.get();
	}

	if(c == ':')
		parsePort();
	else{
		setDefaultPort();
		ssValue.unget();
	}

	asset("/");

	parsePath();

	if(!ssValue.eof()){
		asset("?");
		parseQuery();
	}

}
/*************************************************************************/
void URI::asset(const String& strAllowed){
	IAS_TRACER;

	char c=ssValue.get();

	if(strAllowed.find(c)==String::npos)
		IAS_THROW(ItemNotFoundException(String("Parse error when reading URL, pattern=[")
				+strAllowed+"] got: ["+c+"] in "+strValue));

}
/*************************************************************************/
void URI::parseProtocol(){
	IAS_TRACER;

	char c;

	while( !ssValue.eof() && (isalpha(c=ssValue.get()) || isdigit(c)) ){
		strProtocol+=c;
	}

	if(ssValue.eof())
		IAS_THROW(ItemNotFoundException(strValue+":Parse error when reading URL."));

	ssValue.unget();
}
/*************************************************************************/
void URI::parseDomain(){
	IAS_TRACER;

	char c;

	while( !ssValue.eof() &&
		(isalnum(c=ssValue.get()) || c == '.' || c == '_') ){
		strHost+=c;
	}

	if(!ssValue.eof())
		ssValue.unget();
}
/*************************************************************************/
void URI::parsePort(){
	IAS_TRACER;

	char c;
	//TODO (M) numbers <= service name ??
	String strValue;
	while( !ssValue.eof() &&
		isdigit(c=ssValue.get()) ){
		strValue+=c;
	}

	if(ssValue.eof())
		IAS_THROW(ItemNotFoundException(this->strValue+":Parse error when reading URL."));

	iPort=TypeTools::StringToInt(strValue);
	ssValue.unget();

}/*************************************************************************/
void URI::parsePath(){
	IAS_TRACER;

	char c;

	while( c=ssValue.get(), !ssValue.eof() && c != '?' ){
		strPath+=c;
	}

	if(c == '?')
		ssValue.unget();
}
/*************************************************************************/
void URI::parseQuery(){
	IAS_TRACER;

	char c;

	do{

		String strName;
		String strValue;

		while( c=ssValue.get(), !ssValue.eof() && c != '=' ){

			if(c == '%'){
				char c1=ssValue.get();
				char c2=ssValue.get();
				c = MiscTools::HexValue(c1)*16+MiscTools::HexValue(c2);
			}else if(c == '+'){
				c = ' ';
			}

			strName+=c;
		}

		if(ssValue.eof())
			IAS_THROW(ItemNotFoundException("Parse error when reading URL."));

		while( c=ssValue.get(), !ssValue.eof() && c != '&' ){

			if(c == '%'){
				char c1=ssValue.get();
				char c2=ssValue.get();
				c = MiscTools::HexValue(c1)*16+MiscTools::HexValue(c2);
			}else if(c == '+'){
				c = ' ';
			}

			strValue+=c;

		}

		hmValues[strName]=strValue;

		IAS_LOG(LogLevel::INSTANCE.isInfo(),strName<<"="<<strValue);

	}while(c == '&');

}
/*************************************************************************/
bool URI::hasValue(const String& strName)const{
  return hmValues.find(strName) != hmValues.end();
}
/*************************************************************************/
const String& URI::getValue(const String& strName)const{
	IAS_TRACER;

	ValuesMap::const_iterator it=hmValues.find(strName);

	if(it == hmValues.end()) {
		IAS_THROW(ItemNotFoundException(String("Query value:[")+strName+"] not found."));
	}

	return it->second;

}
/*************************************************************************/
void URI::addValue(const String& strName, const String& strValue){
	IAS_TRACER;

	ValuesMap::const_iterator it=hmValues.find(strName);
	if(it != hmValues.end()) {
		IAS_THROW(AlreadyExists(String("Query value:[")+strName+String("] already exists with value:[")+it->second+String("], multivalues not supported.")));
	}

  hmValues[strName] = strValue;
}
/*************************************************************************/
void URI::setDefaultPort(){
	IAS_TRACER;

	//TODO (M) more efficient and/or use service list with getaddrinfo ?

	std::string s;


	if(strProtocol.compare("shm"))
		iPort=50000;
}
/*************************************************************************/

}
