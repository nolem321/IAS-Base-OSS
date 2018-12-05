/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/PowerOfTwoMemoryManager.h
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

#ifndef _IAS_QS_System_MM_PowerOfTwoMemoryManager_H_
#define _IAS_QS_System_MM_PowerOfTwoMemoryManager_H_

#include <commonlib/commonlib.h>
#include <commonlib/memory/mm/PowerOfTwoMemoryManager.h>

#include <org/invenireaude/qsystem/stats/MemoryManager.h>

namespace IAS {
namespace QS {
namespace SHM {
namespace MM {

/*************************************************************************/
/** The PowerOfTwoMemoryManager class.
 *
 */
class PowerOfTwoMemoryManager : public ::IAS::PowerOfTwoMemoryManager {
public:

	virtual ~PowerOfTwoMemoryManager()throw();

		virtual org::invenireaude::qsystem::stats::Ext::MemoryManagerPtr getStatistics()const;

protected:

	PowerOfTwoMemoryManager(void *pStart, size_t iSize);
	PowerOfTwoMemoryManager(void *pStart);

	friend class Factory<PowerOfTwoMemoryManager>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_QS_System_MM_PowerOfTwoMemoryManager_H_ */
