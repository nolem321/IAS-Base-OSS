/*
 * File: Connection.h
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


#ifndef _IAS_Tools_LDAP_Handle_Connection_H_
#define _IAS_Tools_LDAP_Handle_Connection_H_

#include <commonlib/commonlib.h>

#include "../myldap.h"

namespace IAS {
namespace Tools {
namespace LDAP {
namespace Handle {

class QueryResult;

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection {
public:

	virtual ~Connection() throw();

	void setProtocol(int iProtocol = USED_LDAP_VERSION);

	void authorize(const String& strUser, const String& strPassword);
	QueryResult* query(const String& strSearchBase, const String& strQuery);

	::LDAP* getLDAPConn(){ return ldConn;};

protected:
	Connection(const String& strHost, const int iPort);

	String strHost;
	const  int iPort;

  ::LDAP* ldConn;

  friend class Factory<Connection>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Tools_LDAP_Handle_Connection_H_ */
