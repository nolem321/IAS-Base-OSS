/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/cache/Context.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_Storage_Context_H_
#define _IAS_QS_Workers_Proc_WCM_Storage_Context_H_

#include <commonlib/commonlib.h>

#include <qs/workers/proc/dict/Dictionary.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace WCM {
namespace Storage {

/*************************************************************************/
/** The Context class.
 *
 */
class Context {
public:


	Context(GlobalContext *pGlobalContext) throw();
	~Context() throw();

	void setLocalValue(const String& strKey, DM::DataObject* dm);
	DM::DataObject* getLocalValue(const String& strKey);

	void setGlobalValue(const String& strKey, DM::DataObject* dm);
	DM::DataObject* getGlobalValue(const String& strKey);

	void clear();

	protected:

	typedef HashMapWithStringKey<DM::DataObjectPtr> ValuesMap;

	ValuesMap hmLocalValues;
	ValuesMap hmGlobalValues;

};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_WCM_Cache_Context_H_ */
