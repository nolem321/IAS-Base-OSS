/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/io/Context.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_IO_Context_H_
#define _IAS_QS_Workers_Proc_WCM_IO_Context_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>
#include <org/invenireaude/qsystem/workers/io/Parameters.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace IO {
/*************************************************************************/

/** The Context class.
 *

 */
class Context {
public:

	QS::API::Session*           lookupSession(URI& uri, const ::org::invenireaude::qsystem::workers::io::Parameters* dmParameters);
	QS::API::Connection*        lookupConnection(URI& uri, const ::org::invenireaude::qsystem::workers::Connection* dmConnection);
	QS::API::Administrator*     lookupAdministrator(URI& uri, const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	void commit();
	void rollback();

protected:


	struct Entry{

		Entry(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);
		virtual ~Entry(){};

		API::Connection::PtrHolder        ptrConnection;
		API::Session::PtrHolder           ptrTransactedSession;
		API::Session::PtrHolder           ptrAutoCommitSession;
		API::Session::PtrHolder           ptrXAManagedSession;
		API::Administrator::PtrHolder     ptrAdministrator;
	};


	void createEntryIfNeeded(URI& uri, const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	typedef HashMapStringToPointer<Entry> SessionsMap;
	SessionsMap                        	  hmSession;

};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_WCM_IO_Context_H_ */
