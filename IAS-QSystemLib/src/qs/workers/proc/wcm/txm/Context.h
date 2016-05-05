/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/txm/Context.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_TXM_Context_H_
#define _IAS_QS_Workers_Proc_WCM_TXM_Context_H_

#include <commonlib/commonlib.h>

#include <txm/api.h>

#include <org/invenireaude/qsystem/workers/txm/Parameter.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace TXM {

/*************************************************************************/
class Context {
public:

	IAS::TXM::API::Session*           lookupSession(const URI& uri);

	void begin();
	void commit();
	void rollback();

protected:


	struct Entry{

		virtual ~Entry(){};

		IAS::TXM::API::Connection::PtrHolder        ptrConnection;
		IAS::TXM::API::Session::PtrHolder           ptrSession;
	};


	typedef HashMapStringToPointer<Entry> SessionsMap;
	SessionsMap                        	  hmSession;
	void createEntry(const URI& uri);
};

/*************************************************************************/

}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_WCM_TXM_Context_H_ */
