/*
 * File: IAS-CommonLib/src/commonlib/net/http/Response.cpp
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
#include "Response.h"

#include <commonlib/logger/logger.h>

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
Response::Response():
	iStatus(HS_NONE){
	IAS_TRACER;

}
/*************************************************************************/
Response::~Response() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Response::Status Response::getStatus()const{
	IAS_TRACER;
	return iStatus;
}
/*************************************************************************/
void Response::setStatus(Status iStatus){
	IAS_TRACER;
	this->iStatus=iStatus;
}
/*************************************************************************/
const String& Response::getServer()const{
	IAS_TRACER;
	return strServer;
}
/*************************************************************************/
void Response::setServer(const String& strServer){
	IAS_TRACER;
	this->strServer=strServer;
}
/*************************************************************************/
const String& Response::getDate()const{
	IAS_TRACER;
	return strDate;
}
/*************************************************************************/
void Response::setDate(const String& strDate){
	IAS_TRACER;
	this->strDate=strDate;
}
/*************************************************************************/
void Response::addCookieSpecification(const String& strValue){
	lstCookies.push_back(strValue);
}
/*************************************************************************/
const Response::CookiesList& Response::getCookies()const{
	return lstCookies;
}
/*************************************************************************/
void Response::parse(std::istream& is){
	IAS_TRACER;
	Parser parser(*this,is);
	parser.parse();
}
/*************************************************************************/
void Response::serialize(std::ostream& os){
	IAS_TRACER;

	os<<"HTTP/1."<<getVersion()<<" "<<iStatus<<" "<<StatusToString(iStatus)<<"\r\n";

	if(!strDate.empty())
		os<<"Date: "<<strDate<<"\r\n";

	if(!strServer.empty())
		os<<"Server: "<<strServer<<"\r\n";

	if(!strTransferEncoding.empty())
		os<<"Transfer-Encoding: "<<strTransferEncoding<<"\r\n";

	if(!strContentType.empty())
		os<<"Content-Type: "<<strContentType<<"\r\n";

	if(iConentLength != SIZE_MAX)
		os<<"Content-Length: "<<iConentLength<<"\r\n";

	for (CookiesList::const_iterator it=lstCookies.begin(); it != lstCookies.end(); ++it)
		os<<"Set-Cookie: "<<(*it)<<"\r\n";

	os<<"\r\n";
}
/*************************************************************************/
/*                              P A R S E R	                             */
/*************************************************************************/
Response::Parser::Parser(Response& response, std::istream& is):
	response(response),
	is(is){
}
/*************************************************************************/
void Response::Parser::parse(){
	IAS_TRACER;

	const int iBufSize=4096;
	char sBuffer[iBufSize];

	is.getline(sBuffer,iBufSize,'\r');
	if(is.get() != '\n')
		IAS_THROW(BadUsageException("HTTP Response Parser Error: LF expected after CR."))

	if(!is.good())
		IAS_THROW(BadUsageException("HTTP Response Parser Error: content reader failed."))

	char *s=sBuffer;
	char *c=sBuffer;

	while(!isblank(*c) && *c)
		c++;

	if(*c == 0)
		IAS_THROW(BadUsageException("HTTP Response Parser Error: unexpected end of line after the version."))

	*c++=0;

	if(String("HTTP/1.1").compare(s) == 0){
		response.setVersion(HV_1_1);
	}else if(String("HTTP/1.0").compare(s) == 0){
		response.setVersion(HV_1_0);
	}else
		IAS_THROW(BadUsageException("HTTP Response Parser Error: http version [")<<s<<"]");

	while(isblank(*c))
		c++;
	s=c;

	while(*c != 0 && !isblank(*c))
		c++;

	if(*c == 0)
		IAS_THROW(BadUsageException("HTTP Response Parser Error: unexpected end of line after the status."))

	*c++=0;

	response.setStatus(static_cast<Response::Status>(TypeTools::StringToInt(s)));

	while(isblank(*c))
		c++;

	s=c;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Status info: "<<s);

	while(is.good()){
		is.getline(sBuffer,iBufSize,'\r');

		if(is.get() != '\n')
			IAS_THROW(BadUsageException("HTTP Response Parser Error: LF expected after CR."))

		if(!is.good())
			IAS_THROW(BadUsageException("HTTP Response Parser Error: content reader failed."))

		if(*sBuffer == 0){

			if(!strName.empty())
				processNameValuePair();

			return;

		}else if(isblank(*sBuffer)){

			if(strName.empty())
				IAS_THROW(BadUsageException("HTTP Response Parser Error: the line start with a blank but no header value earlier."))
			strValue+=sBuffer+1;

		} else {

			if(!strName.empty())
				processNameValuePair();

			parseNameValue(sBuffer);
		}

	}
}
/*************************************************************************/
void Response::Parser::processNameValuePair(){
	IAS_TRACER;

	//TODO (M) more efficient

	IAS_LOG(LogLevel::INSTANCE.isInfo(),strName<<"="<<strValue)
	if(!strName.compare("Date")){ response.setDate(strValue); }
	else if(!strName.compare("User-Agent")){ response.setServer(strValue); }
	else if(!strName.compare("Transfer-Encoding")){ response.setTransferEncoding(strValue); }
	else if(!strName.compare("Content-Type")){ response.setContentType(strValue); }
	else if(!strName.compare("Content-Length")){ response.setContentLength(strValue); }
	else if(!strName.compare("Content-type")){ response.setContentType(strValue); }
	else if(!strName.compare("Content-length")){ response.setContentLength(strValue); }

	strName.clear();
	//TODO (H) do not ignore
}
/*************************************************************************/
void Response::Parser::parseNameValue(char* sBuffer){
	IAS_TRACER;

	char *s=sBuffer;
	char *c=sBuffer;

	while(*c && *c != ':')
		c++;

	if(*c != ':')
		IAS_THROW(BadUsageException("HTTP Response Parser Error: missing ':'"));

	*c++=0;
	strName=s;

	while(isblank(*c))
		c++;

	strValue=c;
}
/*************************************************************************/
class _StatusToStringMapping{

protected:
	   typedef ias_std_unordered_map<int, String> StatusMap;
	   StatusMap hmStatus;
public:
	_StatusToStringMapping(){
	 hmStatus[Response::HS_CONTINUE]=                           "Continue";
	 hmStatus[Response::HS_SWITCHING_PROTOCOLS]=                "Switching Protocols";
	 hmStatus[Response::HS_OK]=                                 "OK";
	 hmStatus[Response::HS_CREATED]=                            "Created";
	 hmStatus[Response::HS_ACCEPTED]=                           "Accepted";
	 hmStatus[Response::HS_NON_AUTHORITATIVE_INFORMATION]=      "Non Authoritative Information";
	 hmStatus[Response::HS_NO_CONTENT]=                         "No Content";
	 hmStatus[Response::HS_RESET_CONTENT]=                      "Reset Content";
	 hmStatus[Response::HS_PARTIAL_CONTENT]=                    "Partial Content";
	 hmStatus[Response::HS_MULTIPLE_CHOICES]=                   "Multiple Choices";
	 hmStatus[Response::HS_MOVED_PERMANENTLY]=                  "Moved Permanently";
	 hmStatus[Response::HS_FOUND]=                              "Found";
	 hmStatus[Response::HS_SEE_OTHER]=                          "See Other";
	 hmStatus[Response::HS_NOT_MODIFIED]=                       "Not Modified";
	 hmStatus[Response::HS_USE_PROXY]=                          "Use Proxy";
	 hmStatus[Response::HS_TEMPORARY_REDIRECT]=                 "Temporary Redirect";
	 hmStatus[Response::HS_BAD_REQUEST]=                        "Bad Request";
	 hmStatus[Response::HS_UNAUTHORIZED]=                       "Unauthorized";
	 hmStatus[Response::HS_PAYMENT_REQUIRED]=                   "Payment Required";
	 hmStatus[Response::HS_FORBIDDEN]=                          "Forbidden";
	 hmStatus[Response::HS_NOT_FOUND]=                          "Not Found";
	 hmStatus[Response::HS_METHOD_NOT_ALLOWED]=                 "Method Not Allowed";
	 hmStatus[Response::HS_NOT_ACCEPTABLE]=                     "Not Acceptable";
	 hmStatus[Response::HS_PROXY_AUTHENTICATION_REQUIRED]=      "Proxy Authentication Required";
	 hmStatus[Response::HS_REQUEST_TIME_OUT]=                   "Request Time out";
	 hmStatus[Response::HS_CONFLICT]=                           "Conflict";
	 hmStatus[Response::HS_GONE]=                               "Gone";
	 hmStatus[Response::HS_LENGTH_REQUIRED]=                    "Length Required";
	 hmStatus[Response::HS_PRECONDITION_FAILED]=                "Precondition Failed";
	 hmStatus[Response::HS_REQUEST_ENTITY_TOO_LARGE]=           "Request Entity Too Large";
	 hmStatus[Response::HS_REQUEST_URI_TOO_LARGE]=              "Request URI Too Large";
	 hmStatus[Response::HS_UNSUPPORTED_MEDIA_TYPE]=             "Unsupported Media Type";
	 hmStatus[Response::HS_REQUESTED_RANGE_NOT_SATISFIABLE]=    "Requested range not satisfiable";
	 hmStatus[Response::HS_EXPECTATION_FAILED]=                 "Expectation Failed";
	 hmStatus[Response::HS_INTERNAL_SERVER_ERROR]=              "Internal Server Error";
	 hmStatus[Response::HS_NOT_IMPLEMENTED]=                    "Not Implemented";
	 hmStatus[Response::HS_BAD_GATEWAY]=                        "Bad Gateway";
	 hmStatus[Response::HS_SERVICE_UNAVAILABLE]=                "Service Unavailable";
	 hmStatus[Response::HS_GATEWAY_TIME_OUT]=                   "Gateway Time out";
	 hmStatus[Response::HS_HTTP_VERSION_NOT_SUPPORTED]=         "HTTP Version not supported";
	}

	static _StatusToStringMapping TheInstance;

	const String& getStatus(Response::Status iStatus)const{

		StatusMap::const_iterator it = hmStatus.find(iStatus);

		if (it == hmStatus.end()) {
			IAS_THROW(BadUsageException("Unknown HTTP status code:") << iStatus);
		}

		return it->second;

	}
};
_StatusToStringMapping _StatusToStringMapping::TheInstance;
/*************************************************************************/
const String& Response::StatusToString(Status iStatus){
	return _StatusToStringMapping::TheInstance.getStatus(iStatus);
}
/*************************************************************************/
}
}
}
