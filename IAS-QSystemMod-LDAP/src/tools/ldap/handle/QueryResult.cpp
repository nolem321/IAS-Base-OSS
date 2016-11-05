/*
 * File: QueryResult.cpp
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

#include "QueryResult.h"

#include <commonlib/net/URI.h>

#include "Connection.h"

namespace IAS {
namespace Tools {
namespace LDAP {
namespace Handle {
/*************************************************************************/
QueryResult::QueryResult(LDAPMessage *msg, ::LDAP*     ldConn):
		msg(msg),
		ldConn(ldConn){
	IAS_TRACER;
}
/*************************************************************************/
QueryResult::~QueryResult() throw(){
	IAS_TRACER;

	ldap_msgfree(msg);
}
/*************************************************************************/
void QueryResult::getEntries(EntryList& lstResult){
	IAS_TRACER;
  
    LDAPMessage *entry;

    for (entry = ldap_first_entry(ldConn, msg); entry != NULL;
         entry = ldap_next_entry(ldConn, entry)) {

      readEntry(entry, lstResult);
    }

}
/*************************************************************************/
QueryResult::MemHolder::MemHolder(char *p):p(p){
}

QueryResult::MemHolder& QueryResult::MemHolder::operator=(char *p){

	if(this->p)
		ldap_memfree(this->p);

	this->p = p;
	return *this;
}

QueryResult::MemHolder::~MemHolder(){
	if(p)
	  ldap_memfree(p);
};

/*************************************************************************/
QueryResult::BerHolder::~BerHolder(){
	if(p)
	 ber_free(p, 0);
};

/*************************************************************************/
QueryResult::BerValHolder::BerValHolder(berval **p):p(p){
}

QueryResult::BerValHolder::~BerValHolder(){
	if(p)
  	  ldap_value_free_len(p);
};
/*************************************************************************/
void QueryResult::readEntry(LDAPMessage *entry, EntryList& resultEntryList) {

  Entry result;
  

  MemHolder mhDn(ldap_get_dn(ldConn, entry));
  result.push_back(Attribute("dn", { mhDn.p }));

  BerHolder bh;

  for (MemHolder mhName = ldap_first_attribute(ldConn, entry, &bh.p);
	    mhName.p != NULL; mhName = ldap_next_attribute(ldConn, entry, bh.p)) {

    readAttribute(entry, mhName.p, result);
  }

  resultEntryList.push_back(result);
}
/*************************************************************************/
void QueryResult::readAttribute(LDAPMessage *entry, const char* sAttrName, Entry& resultEntry) {
  
  BerValHolder bhv(ldap_get_values_len(ldConn, entry, sAttrName));

  if(!bhv.p)
	  IAS_THROW(InternalException("Bad LDAP attribute name: " + String(sAttrName)));

  StringList valueList;

  for(berval **pCursor = bhv.p; *pCursor != NULL; pCursor++)
	valueList.push_back(String((*pCursor)->bv_val, (*pCursor)->bv_len));
  
  resultEntry.push_back(Attribute(sAttrName, valueList));
}
/*************************************************************************/
}
}
}
}
