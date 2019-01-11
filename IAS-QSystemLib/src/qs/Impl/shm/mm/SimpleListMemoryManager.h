/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/SimpleListMemoryManager.h
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
#ifndef _IAS_QS_System_MM_SimpleListMemoryManager_H_
#define _IAS_QS_System_MM_SimpleListMemoryManager_H_

#include <commonlib/commonlib.h>
#include <commonlib/memory/mm/SimpleListMemoryManager.h>

#include <org/invenireaude/qsystem/stats/MemoryManager.h>

namespace IAS {
namespace QS {
namespace SHM {
namespace MM {

/*************************************************************************/
/** The SimpleListMemoryManager class.
 *
 */
class SimpleListMemoryManager : public ::IAS::SimpleListMemoryManager {
public:

	virtual ~SimpleListMemoryManager()throw();

	virtual org::invenireaude::qsystem::stats::Ext::MemoryManagerPtr getStatistics()const;

protected:

	SimpleListMemoryManager(void *pStart, size_t iSize);
	SimpleListMemoryManager(void *pStart);

	friend class Factory<SimpleListMemoryManager>;


};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_System_MM_SimpleListMemoryManager_H_ */