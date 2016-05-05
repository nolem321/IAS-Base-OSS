/*
 * File: IAS-CommonLib/src/commonlib/net/http/Request.h
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
#ifndef _IAS_Net_HTTP_Request_H_
#define _IAS_Net_HTTP_Request_H_

#include <commonlib/memory/memory.h>
#include "Header.h"

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
/** The Request class.
 *
 */
class Request : public Header {
public:

	virtual ~Request() throw();

	enum Method{
		HM_NONE,
		HM_GET,
		HM_POST,
		HM_HEADER,
		HM_DELETE
	};

	Method  getMethod()const;
	void    setMethod(Method iMethod);

	const String&  getResource()const;
	void           setResource(const String& strResource);

	const String&  getFrom()const;
	void    setFrom(const String& strFrom);

	const String&  getUserAgent()const;
	void    setUserAgent(const String& strUserAgent);

	const String&  getHost()const;
	void    setHost(const String& strHost);

	const String&  getAccept()const;
	void    setAccept(const String& strAccept);

	const String&  getAcceptLanguage()const;
	void    setAcceptLanguage(const String& strAcceptLanguage);

	bool    isSetAuthorization()const;

	void getAuthoriation(String& strMethod, String& strParameter)const;
	void setAuthorization(const String& strMethod, const String& strParameter);

	virtual void parse(std::istream& is);
	virtual void serialize(std::ostream& os);

	typedef std::pair<String,String> Cookie;
	typedef std::list<Cookie, AllocatorFactory<Cookie, &MemoryManager::GetAllocator > > CookiesList;

	void addCookie(const String& strName, const String& strValue);
	const CookiesList& getCookies()const;

protected:

	Method        iMethod;
	String        strResource;
	String        strFrom;
	String        strUserAgent;
	String        strHost;
	String        strAccept;
	String        strAcceptLanguage;

	String        strAuthorizationMethod;
	String        strAuthorizationParameter;

	CookiesList   lstCookies;

	class Parser{
	public:

		Parser(Request& request, std::istream& in);

		void parse();

	protected:

		void processNameValuePair();
		void parseNameValue(char* sBuffer);

		String strName;
		String strValue;
		Request& request;
		std::istream& is;
	};


	static const String& MethodToString(Method iMethod);
	static Method StringToMethod(const String& strMethod);

	Request();
	friend class Factory<Request>;
};

//TODO (L) consider region memory manager for values storage.
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_HTTP_Request_H_ */
