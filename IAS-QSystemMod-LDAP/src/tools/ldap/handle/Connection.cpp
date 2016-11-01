/*
 * File: Connection.cpp
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

#include "Connection.h"

#include <commonlib/net/URI.h>

#include "QueryResult.h"

namespace IAS {
namespace Tools {
namespace LDAP {
namespace Handle {
/*************************************************************************/
Connection::Connection(const String& strHost, const int iPort):
		strHost(strHost),
		iPort(iPort),
		ldConn(NULL){
	IAS_TRACER;

	int rc;
	int protocol = USED_LDAP_VERSION;

	URI uri;

	uri.setProtocol("ldap");
	uri.setHost(strHost);
	uri.setPort(iPort);

	String strURI((String)uri);

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Connecting to: " << strURI);

	rc = ldap_initialize(&ldConn, strURI.c_str());

	if (rc != LDAP_SUCCESS) {
		IAS_THROW(BadUsageException("Could not create LDAP session handle: " + (String) ldap_err2string(rc)));
	}

}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;

  if (ldConn != NULL) {
    ldap_unbind_ext_s(ldConn, NULL, NULL);
  }
}
/*************************************************************************/
void Connection::setProtocol(int iProtocol){

	IAS_TRACER;
	int rc;

	rc = ldap_set_option(ldConn, LDAP_OPT_PROTOCOL_VERSION, &iProtocol);

	if (rc != LDAP_SUCCESS) {
		IAS_THROW(BadUsageException("Could not set LDAP_OPT_PROTOCOL_VERSION to: " + iProtocol));
	}

}
/*************************************************************************/
void Connection::authorize(const String& strUser, const String& strPassword){
  int rc;

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Authorizing with credentials: "<<strUser<<" / "<<strPassword);

	{
		Thread::Cancellation ca(true);

		rc = ldap_simple_bind_s(ldConn, strUser.c_str(), strPassword.c_str());
	}

  if (rc != LDAP_SUCCESS) {
	IAS_THROW(BadUsageException("Error on authorization (bind): " + String(ldap_err2string(rc))));
  }

}
/*************************************************************************/
QueryResult* Connection::query(const String& strSearchBase, const String& strQuery){
	IAS_TRACER;
  
  int rc;

  char **attrs = NULL;
  LDAPMessage *msg;

  {
  		Thread::Cancellation ca(true);

  		rc = ldap_search_ext_s(ldConn, strSearchBase.c_str(), LDAP_SCOPE_SUBTREE,
                         strQuery.c_str(),
                         attrs, 0,
                         NULL, NULL, NULL, LDAP_NO_LIMIT, &msg);

  }

   if (rc != LDAP_SUCCESS) {
	   ldap_msgfree(msg); //Man pages say to do so.
	   IAS_THROW(BadUsageException("Error on search: " + (String) ldap_err2string(rc)));
    }

   return IAS_DFT_FACTORY<QueryResult>::Create(msg, ldConn);
}
/*************************************************************************/
}
}
}
}
