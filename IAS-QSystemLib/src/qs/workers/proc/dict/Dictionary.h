/*
 * File: IAS-QSystemLib/src/qs/workers/proc/dict/Dictionary.h
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
#ifndef _IAS_QS_Workers_Proc_Dict_Dictionary_H_
#define _IAS_QS_Workers_Proc_Dict_Dictionary_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Dict {

/*************************************************************************/
/** The Dictionary class.
 *
 */
class Dictionary {
public:

	virtual ~Dictionary() throw();


	void setValue(const String& strKey, DM::DataObject* dm);
	DM::DataObject* getValue(const String& strKey);

protected:

	Dictionary();

	Mutex mutex;

	typedef HashMapWithStringKey<DM::DataObjectPtr> ValuesMap;
	ValuesMap hmValues;

	friend class Factory<Dictionary>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Dict_Dictionary_H_ */
