/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/ds/Context.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_DS_Context_H_
#define _IAS_QS_Workers_Proc_WCM_DS_Context_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>
#include <map>
#include <set>
#include <unordered_map>

#include <ds/api.h>

#include <org/invenireaude/qsystem/workers/ds/Parameter.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace DS {
/*************************************************************************/
class Context {
public:


	//TODO (MH) remove this const and compute URI here.
	::IAS::DS::API::Session*    lookupSession(URI& uri, const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);
	::IAS::DS::API::Connection* lookupConnection(URI& uri, const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);

	void commit();
	void rollback();

protected:

	struct Entry{

		virtual ~Entry(){};

		::IAS::DS::API::Connection::PtrHolder ptrConnection;
		::IAS::DS::API::Session::PtrHolder    ptrSession;
	};

	typedef HashMapStringToPointer<Entry> SessionsMap;
	SessionsMap                           hmSession;

	void createEntryIfNeeded(URI& uri,const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);
};

/*************************************************************************/

}
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_WCM_DS_Context_H_ */
