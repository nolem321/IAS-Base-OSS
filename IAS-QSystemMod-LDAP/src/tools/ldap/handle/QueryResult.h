/*
 * File: QueryResult.h
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


#ifndef _IAS_Tools_LDAP_Handle_QueryResult_H_
#define _IAS_Tools_LDAP_Handle_QueryResult_H_

#include <commonlib/commonlib.h>

#include "../myldap.h"

namespace IAS {
namespace Tools {
namespace LDAP {
namespace Handle {

class Connection;

/*************************************************************************/
/** The QueryResult class.
 *
 */
class QueryResult {
public:

	virtual ~QueryResult() throw();

	void getEntries(EntryList& lstResult);

protected:

  QueryResult(LDAPMessage *msg, ::LDAP* ldConn);

  ::LDAP*     ldConn;
  LDAPMessage *msg;

  struct MemHolder {
	  MemHolder(char *p);
	  MemHolder& operator=(char *p);
	 ~MemHolder();
	 char *p;
  };

  struct BerHolder {
	 ~BerHolder();
	 BerElement *p;
  };

  struct BerValHolder {
	  BerValHolder(berval **p);
	 ~BerValHolder();
	 berval **p;
  };

  void readEntry(LDAPMessage *entry, EntryList& resultEntryList);
  void readAttribute(LDAPMessage *entry, const char* sAttrName, Entry& resultEntry);

  friend class Factory<QueryResult>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Tools_LDAP_Handle_QueryResult_H_ */
