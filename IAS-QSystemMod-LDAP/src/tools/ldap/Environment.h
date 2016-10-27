/*
 * File: Environment.h
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


#ifndef _IAS_Tools_LDAP_Environment_H_
#define _IAS_Tools_LDAP_Environment_H_

#include <commonlib/commonlib.h>

#include "Connector.h"

namespace IAS {
namespace Tools {
namespace LDAP {


/*************************************************************************/
/** The Environment class.
 *
 */
class Environment : public InstanceFeature<Environment>{
public:

	virtual ~Environment() throw();

	Connector* lookup(const String& strName);

protected:
	Environment();

	typedef HashMapStringToPointer<Connector> ConnectorsMap;
	ConnectorsMap hmConnectors;

	Mutex mutex;

	friend class Factory<Environment>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Tools_LDAP_Environment_H_ */
