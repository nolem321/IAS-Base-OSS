/*
 * File: IAS-CommonLib/src/commonlib/net/URI.h
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
#ifndef _IAS_URI_H_
#define _IAS_URI_H_

#include <commonlib/types.h>
#include "commonlib/containers/HashMapStringToPointer.h"

namespace IAS {

/*************************************************************************/
/** The URI class.
 *
 * //TODO (M) change name to URI and make internal parser class with a stringstream.
 *
 */
class URI {
public:

	URI(const String& strValue="");
	URI(const URI& other){ copy(other); };

	inline const String& getProtocol()const{return strProtocol;}
	inline const String& getHost()const{return strHost;}
	inline unsigned int  getPort()const{return iPort;}
	inline const String& getPath()const{return strPath;}
	inline const String& getUser()const{return strUser;}
	inline const String& getPassword()const{return strPassword;}

	void setProtocol(const String& strProtocol);
	void setHost(const String& strHost);
	void setPath(const String& strPath);
	void setPort(unsigned int iPort);
	void setUser(const String& strUser);
	void setPassword(const String& strPassword);

	typedef HashMapWithStringKey<String> ValuesMap;

	typedef ValuesMap::const_iterator const_iterator;

	inline const_iterator begin()const { return hmValues.begin(); };
	inline const_iterator end()const { return hmValues.end(); };

	const String& getURIString()const;

	inline operator const String&()const{ return getURIString(); }
	inline operator String()const{ return getURIString(); }

	inline URI& operator=(const URI& other){ copy(other); return *this; };

	bool hasValue(const String& strName)const;
	const String& getValue(const String& strName)const;

	void addValue(const String& strName, const String& strValue);

protected:

	void copy(const URI& other);

	void parse();

	void asset(const String& strAllowed);

	void parseProtocol();
	void parseDomain();
	void parsePort();
	void parsePath();
	void parseQuery();

	String strProtocol;
	String strHost;
	String strPath;
	String strUser;
	String strPassword;

	unsigned int iPort;

	String       strValue;
	StringStream ssValue;

	void setDefaultPort();
	ValuesMap							  hmValues;
};

/*************************************************************************/
}

#endif /* _IAS_URI_H_ */
