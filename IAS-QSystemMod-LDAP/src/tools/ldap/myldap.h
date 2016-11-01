/*
 * File: MyLDAP.h
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

#ifndef _IAS_Tools_LDAP_Handle_MyLDAP_H_
#define _IAS_Tools_LDAP_Handle_MyLDAP_H_


#define LDAP_DEPRECATED true
#include <ldap.h>

#define USED_LDAP_VERSION LDAP_VERSION3

namespace IAS {
namespace Tools {
namespace LDAP {

typedef std::pair<String, StringList> Attribute;
typedef std::list<Attribute, IAS_DFT_FACTORY<Attribute> > Entry;
typedef std::list<Entry, IAS_DFT_FACTORY<Entry> > EntryList;

}
}
}

#endif /* TOOLS_LDAP_HANDLE_MYLDAP_H_ */
