/*
 * File: Connector.h
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


#ifndef _IAS_Tools_LDAP_Connector_H_
#define _IAS_Tools_LDAP_Connector_H_

#include <commonlib/commonlib.h>

#include "handle/Connection.h"
#include "handle/QueryResult.h"

#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace Tools {
namespace LDAP {

/*************************************************************************/
/** The Connector class.
 *
 */
class Connector {
public:

	virtual ~Connector() throw();

	void query(const String& strSearchBase, const String& strQuery, EntryList& lstResult);

	bool isValid();

protected:
	Connector(const String& strName);

	String strName;

	IAS_DFT_FACTORY<Handle::Connection>::PtrHolder ptrConnection;

    Mutex mutex;

    bool bValid;

    org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection;

    void connect();
    void queryImpl(const String& strSearchBase, const String& strQuery, EntryList& lstResult);

	friend class Factory<Connector>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Tools_LDAP_Connector_H_ */
