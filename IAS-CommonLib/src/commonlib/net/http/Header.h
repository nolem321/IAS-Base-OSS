/*
 * File: IAS-CommonLib/src/commonlib/net/http/Header.h
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
#ifndef _IAS_Net_HTTP_Header_H_
#define _IAS_Net_HTTP_Header_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
/** The Header class.
 *
 */
class Header {
public:

	virtual ~Header() throw();

	typedef std::pair<String,String> NameValuePair;
	typedef std::list<NameValuePair, AllocatorFactory<NameValuePair, &MemoryManager::GetAllocator > > NameValuePairList;

	typedef NameValuePairList::const_iterator const_iterator;

	enum Version{
		HV_1_0 = 0,
		HV_1_1 = 1,
	};

	Version getVersion()const;
	void    setVersion(Version iVersion);

	const String&  getTransferEncoding()const;
	void  setTransferEncoding(const String& strTransferEncoding);

	const String&  getContentType()const;
	void    setContentType(const String& strContentType);

	size_t  getContentLength()const;
	void    setContentLength(size_t iContentLength);
	void    setContentLength(const String& strContentLength);
	bool    isSetContentLength()const;

	void    addCustomHeader(const NameValuePair& nameValue);

	virtual void parse(std::istream& is)=0;
	virtual void serialize(std::ostream& os)=0;

	class Parser{
	public:
		static Header::NameValuePair ParseNameValue(const char* sBuffer);
	};

protected:
	Header();

	Version		  iVersion;
	String        strContentType;
	size_t        iConentLength;

	String        strTransferEncoding;

	NameValuePairList lstCustomHeaders;

	friend class Factory<Header>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_HTTP_Header_H_ */
