/*
 * File: IAS-CommonLib/src/commonlib/net/http/Response.h
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
#ifndef _IAS_Net_HTTP_Response_H_
#define _IAS_Net_HTTP_Response_H_

#include <commonlib/memory/memory.h>
#include "Header.h"

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
/** The Response class.
 *
 */
class Response : public Header {
public:

	virtual ~Response() throw();

	enum Status{
		HS_NONE=0,

		HS_CONTINUE=100,
		HS_SWITCHING_PROTOCOLS=101,

		HS_OK=200,

		HS_CREATED=201,
		HS_ACCEPTED=202,
		HS_NON_AUTHORITATIVE_INFORMATION=203,
		HS_NO_CONTENT=204,
		HS_RESET_CONTENT=205,
		HS_PARTIAL_CONTENT=206,

		HS_MULTIPLE_CHOICES=300,
		HS_MOVED_PERMANENTLY=301,
		HS_FOUND=302,
		HS_SEE_OTHER=303,
		HS_NOT_MODIFIED=304,
		HS_USE_PROXY=305,
		HS_TEMPORARY_REDIRECT=307,

		HS_BAD_REQUEST=400,
		HS_UNAUTHORIZED=401,
		HS_PAYMENT_REQUIRED=402,
		HS_FORBIDDEN=403,
		HS_NOT_FOUND=404,
		HS_METHOD_NOT_ALLOWED=405,
		HS_NOT_ACCEPTABLE=406,
		HS_PROXY_AUTHENTICATION_REQUIRED=407,
		HS_REQUEST_TIME_OUT=408,
		HS_CONFLICT=409,
		HS_GONE=410,
		HS_LENGTH_REQUIRED=411,
		HS_PRECONDITION_FAILED=412,
		HS_REQUEST_ENTITY_TOO_LARGE=413,
		HS_REQUEST_URI_TOO_LARGE=414,
		HS_UNSUPPORTED_MEDIA_TYPE=415,
		HS_REQUESTED_RANGE_NOT_SATISFIABLE=416,
		HS_EXPECTATION_FAILED=417,

		HS_INTERNAL_SERVER_ERROR=500,
		HS_NOT_IMPLEMENTED=501,
		HS_BAD_GATEWAY=502,
		HS_SERVICE_UNAVAILABLE=503,
		HS_GATEWAY_TIME_OUT=504,
		HS_HTTP_VERSION_NOT_SUPPORTED=505
	};

	Status  getStatus()const;
	void    setStatus(Status iStatus);

	const String&  getServer()const;
	void    setServer(const String& strServer);

	const String&  getDate()const;
	void    setDate(const String& strDate);

	virtual void parse(std::istream& is);
	virtual void serialize(std::ostream& os);

	typedef String CookieSpecifiction;
	typedef std::list<CookieSpecifiction, AllocatorFactory<CookieSpecifiction, &MemoryManager::GetAllocator > > CookiesList;

	void addCookieSpecification(const String& strValue);
	const CookiesList& getCookies()const;

protected:

	Status        iStatus;

	String        strServer;
	String        strDate; //TODO real Date

	CookiesList   lstCookies;

	class Parser{
	public:

		Parser(Response& response, std::istream& in);

		void parse();

	protected:

		void processNameValuePair();
		void parseNameValue(char* sBuffer);

		String strName;
		String strValue;
		Response& response;
		std::istream& is;
	};


	static const String& StatusToString(Status iStatus);
	static Status StringToStatus(const String& strStatus);

	Response();
	friend class Factory<Response>;
};

//TODO (L) consider region memory manager for values storage.
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_HTTP_Response_H_ */
