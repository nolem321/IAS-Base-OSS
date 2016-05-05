/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/Registry.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_Registry_H_
#define _IAS_QS_Workers_Proc_WCM_Registry_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {

/*************************************************************************/
/** The Registry class.
 *
 */
class Registry : public InstanceFeature<Registry>{
public:

	virtual ~Registry() throw();

	class RegistryMapping{

	public:

		const org::invenireaude::qsystem::workers::Connection* lookup(const String& strAlias)const;

	protected:

		typedef  HashMapWithStringKey<org::invenireaude::qsystem::workers::Ext::ConnectionPtr> ConnectionMap;
		ConnectionMap hmConnections;

		void addConnection(const org::invenireaude::qsystem::workers::Connection* pConnection);
		friend class Registry;

		Mutex mutex;
	};


	RegistryMapping io;
	RegistryMapping ds;
	RegistryMapping ecs;

protected:
	Registry();

	void loadRegistry();
	void loadRegistry(const String& strFileName);
	void insertRegistry(const org::invenireaude::qsystem::workers::Registry* pRegistry,
			            RegistryMapping& mapping);

	static const String& CStrEnvName;

	DM::DataFactory *pDataFactory;

	friend class Factory<Registry>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_WCM_Registry_H_ */
