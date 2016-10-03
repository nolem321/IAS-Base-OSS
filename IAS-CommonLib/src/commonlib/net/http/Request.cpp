/*
 * File: IAS-CommonLib/src/commonlib/net/http/Request.cpp
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
#include "Request.h"

#include <commonlib/logger/logger.h>

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
Request::Request():
	iMethod(HM_NONE){
	IAS_TRACER;
}
/*************************************************************************/
Request::~Request() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Request::Method Request::getMethod()const{
	IAS_TRACER;
	return iMethod;
}
/*************************************************************************/
void Request::setMethod(Method iMethod){
	IAS_TRACER;
	this->iMethod=iMethod;
}
/*************************************************************************/
const String& Request::getResource()const{
	IAS_TRACER;
	return strResource;
}
/*************************************************************************/
void Request::setResource(const String& strResource){
	IAS_TRACER;
	this->strResource=strResource;
}
/*************************************************************************/
const String& Request::getFrom()const{
	IAS_TRACER;
	return strFrom;
}
/*************************************************************************/
void Request::setFrom(const String& strFrom){
	IAS_TRACER;
	this->strFrom=strFrom;
}
/*************************************************************************/
const String& Request::getUserAgent()const{
	IAS_TRACER;
	return strUserAgent;
}
/*************************************************************************/
void Request::setUserAgent(const String& strUserAgent){
	IAS_TRACER;
	this->strUserAgent=strUserAgent;
}
/*************************************************************************/
const String& Request::getHost()const{
	IAS_TRACER;
	return strHost;
}
/*************************************************************************/
void Request::setHost(const String& strHost){
	IAS_TRACER;
	this->strHost=strHost;
}
/*************************************************************************/
const String& Request::getAccept()const{
	IAS_TRACER;
	return strAccept;
}
/*************************************************************************/
void Request::setAccept(const String& strAccept){
	IAS_TRACER;
	this->strAccept=strAccept;
}
/*************************************************************************/
const String& Request::getAcceptLanguage()const{
	IAS_TRACER;
	return strAcceptLanguage;
}
/*************************************************************************/
void Request::setAcceptLanguage(const String& strAcceptLanguage){
	IAS_TRACER;
	this->strAcceptLanguage=strAcceptLanguage;
}
/*************************************************************************/
void Request::addCookie(const String& strName, const String& strValue){
	lstCookies.push_back(Cookie(strName,strValue));
}
/*************************************************************************/
const Request::CookiesList& Request::getCookies()const{
	return lstCookies;
}
/*************************************************************************/
void Request::parse(std::istream& is){
	IAS_TRACER;
	Parser parser(*this,is);
	parser.parse();
}
/*************************************************************************/
void Request::serialize(std::ostream& os){
	IAS_TRACER;

	os<<MethodToString(iMethod)<<" "<<strResource<<" HTTP/1."<<getVersion()<<"\r\n";

	if(!strFrom.empty())
		os<<"From: "<<strFrom<<"\r\n";

	if(!strAuthorizationMethod.empty())
		os<<"Authorization: "<<strAuthorizationMethod<<" "<<strAuthorizationParameter<<"\r\n";

	if(!strUserAgent.empty())
		os<<"User-Agent: "<<strUserAgent<<"\r\n";

	if(!strHost.empty())
		os<<"Host: "<<strHost<<"\r\n";

	if(!strAccept.empty())
		os<<"Accept: "<<strAccept<<"\r\n";

	if(!strAcceptLanguage.empty())
		os<<"Accept-Language: "<<strAcceptLanguage<<"\r\n";

	if(!strTransferEncoding.empty())
		os<<"Transfer-Encoding: "<<strTransferEncoding<<"\r\n";

	if(!strContentType.empty())
		os<<"Content-Type: "<<strContentType<<"\r\n";

	if(!strSOAPAction.empty())
			os<<"SOAPAction: "<<strSOAPAction<<"\r\n";

	if(iConentLength != SIZE_MAX)
		os<<"Content-Length: "<<iConentLength<<"\r\n";

	if(lstCookies.size()){
		os<<"Cookie: ";

	for (CookiesList::const_iterator it=lstCookies.begin(); it != lstCookies.end(); ++it){
		if(it != lstCookies.begin())
			os<<"; ";
		os<<(*it).first<<"="<<(*it).second;
		}

	os<<"\r\n";
	}

	os<<"\r\n";
}
/*************************************************************************/
/*                              P A R S E R	                             */
/*************************************************************************/
Request::Parser::Parser(Request& request, std::istream& is):
	request(request),
	is(is){
}
/*************************************************************************/
void Request::Parser::parse(){
	IAS_TRACER;

	const int iBufSize=4096;
	char sBuffer[iBufSize];

	is.getline(sBuffer,iBufSize,'\r');
	if(is.get() != '\n')
		IAS_THROW(BadUsageException("HTTP Request Parser Error: LF expected after CR."))

	if(!is.good())
		IAS_THROW(BadUsageException("HTTP Request Parser Error: content reader failed."))

	char *s=sBuffer;
	char *c=sBuffer;

	while(isalpha(*c))
		c++;

	if(*c == 0)
		IAS_THROW(BadUsageException("HTTP Request Parser Error: unexpected end of line after the method name."))

	*c++=0;
	request.setMethod(Request::StringToMethod(s));

	while(isblank(*c))
		c++;

	s=c;

	while(*c != 0 && !isblank(*c))
		c++;

	if(*c == 0)
		IAS_THROW(BadUsageException("HTTP Request Parser Error: unexpected end of line after the resource."))

	*c++=0;
	request.setResource(s);

	while(isblank(*c))
		c++;

	s=c;

	while(*c != 0 && !isblank(*c))
		c++;

	*c++=0;

	if(String("HTTP/1.1").compare(s) == 0){
		request.setVersion(HV_1_1);
	}else if(String("HTTP/1.0").compare(s) == 0){
		request.setVersion(HV_1_0);
	}else
		IAS_THROW(BadUsageException("HTTP Request Parser Error: http version [")<<s<<"]");



	while(is.good()){
		is.getline(sBuffer,iBufSize,'\r');

		if(is.get() != '\n')
			IAS_THROW(BadUsageException("HTTP Request Parser Error: LF expected after CR."))

		if(!is.good())
			IAS_THROW(BadUsageException("HTTP Request Parser Error: content reader failed."))

		if(*sBuffer == 0){

			if(!strName.empty())
				processNameValuePair();

			return;

		}else if(isblank(*sBuffer)){

			if(strName.empty())
				IAS_THROW(BadUsageException("HTTP Request Parser Error: the line start with a blank but no header value earlier."))
			strValue+=sBuffer+1;

		} else {

			if(!strName.empty())
				processNameValuePair();

			parseNameValue(sBuffer);
		}

	}
}
/*************************************************************************/
static inline String &_trim(String &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}
/*************************************************************************/
void Request::Parser::processNameValuePair(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),strName<<"="<<strValue)
	if(!strName.compare("From")){ request.setFrom(strValue); }
	else if(!strName.compare("User-Agent")){ request.setUserAgent(strValue); }
	else if(!strName.compare("Host")){ request.setHost(strValue); }
	else if(!strName.compare("Accept")){ request.setAccept(strValue); }
	else if(!strName.compare("Accept-Language")){ request.setAcceptLanguage(strValue); }
	else if(!strName.compare("Transfer-Encoding")){ request.setTransferEncoding(strValue); }
	else if(!strName.compare("Authorization")){

		String strMethod;
		String strParameter;

		StringStream ssTmp(strValue);

		ssTmp>>strMethod>>strParameter;

		request.setAuthorization(strMethod,strParameter);

	}else if(!strName.compare("Content-Type")){ request.setContentType(strValue); }
	else if(!strName.compare("Content-Length")){ request.setContentLength(strValue); }
	else if(!strName.compare("Content-type")){ request.setContentType(strValue); }
	else if(!strName.compare("Content-length")){ request.setContentLength(strValue); }
	else if(!strName.compare("Cookie")){

		StringList lstCookies;
		TypeTools::Tokenize(strValue,lstCookies,';');
		for (StringList::const_iterator it=lstCookies.begin(); it != lstCookies.end(); ++it) {

			size_t iCursor = (*it).find('=');

			String strName;
			String strValue;

			if (iCursor == String::npos){
				strName=(*it);
			}else{
				strName  = (*it).substr(0,iCursor);
				strValue = (*it).substr(iCursor+1);
			}

			_trim(strName);
			request.addCookie(strName,strValue);

		}
	}
	else if(!strName.compare("SOAPAction")){ request.setSOAPAction(strValue); }

	strName.clear();
	//TODO (H) do not ignore
}
/*************************************************************************/
void Request::Parser::parseNameValue(char* sBuffer){
	IAS_TRACER;

	char *s=sBuffer;
	char *c=sBuffer;

	while(*c && *c != ':')
		c++;

	if(*c != ':')
		IAS_THROW(BadUsageException("HTTP Request Parser Error: missing ':'"));

	*c++=0;
	strName=s;

	while(isblank(*c))
		c++;

	strValue=c;
}
/*************************************************************************/
bool Request::isSetAuthorization()const{
	return !strAuthorizationMethod.empty();
}
/*************************************************************************/
void Request::getAuthoriation(String& strMethod, String& strParameter)const{
	IAS_TRACER;

	strMethod     = strAuthorizationMethod;
	strParameter  = strAuthorizationParameter;

}
/*************************************************************************/
void Request::setAuthorization(const String& strMethod, const String& strParameter){
	IAS_TRACER;
	strAuthorizationMethod=strMethod;
	strAuthorizationParameter=strParameter;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Authorization: "<<strAuthorizationMethod<<" "<<strAuthorizationParameter);

}
/*************************************************************************/
bool Request::isSetSOAPAction()const{
	return !strSOAPAction.empty();
}
/*************************************************************************/
void Request::getSOAPAction(String& strParameter)const{
	IAS_TRACER;

	strParameter  = strSOAPAction;

}
/*************************************************************************/
void Request::setSOAPAction(const String& strParameter){
	IAS_TRACER;
	strSOAPAction=strParameter;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"SOAPAction: "<<strSOAPAction);

}
/*************************************************************************/
const String& Request::MethodToString(Method iMethod){

	static const String strGET("GET");
	static const String strDELETE("DELETE");
	static const String strPOST("POST");
	static const String strHEADER("HEADER");

	switch(iMethod){
		case HM_GET:    return strGET;
		case HM_DELETE: return strDELETE;
		case HM_POST:   return strPOST;
		case HM_HEADER: return strHEADER;
	}

	IAS_THROW(BadUsageException("Unknown HTTP method code:")<<iMethod);
}
/*************************************************************************/
Request::Method Request::StringToMethod(const String& strMethod){

	switch(strMethod[0]){
		case 'G':
			if(strMethod.compare("GET"))
				IAS_THROW(BadUsageException("Unknown HTTP method: ")<<strMethod);
			return HM_GET;
			break;

		case 'D':
			if(strMethod.compare("DELETE"))
				IAS_THROW(BadUsageException("Unknown HTTP method: ")<<strMethod);
			return HM_DELETE;
			break;

		case 'P':
			if(strMethod.compare("POST"))
				IAS_THROW(BadUsageException("Unknown HTTP method: ")<<strMethod);
			return HM_POST;
			break;

		case 'H':
			if(strMethod.compare("HEADER"))
				IAS_THROW(BadUsageException("Unknown HTTP method: ")<<strMethod);
			return HM_HEADER;

		default:
			IAS_THROW(BadUsageException("Unknown HTTP method: ")<<strMethod);
	}
}
/*************************************************************************/
}
}
}
