/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/MemoryManagerStatistics.h
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
#ifndef _IAS_MemoryManagerStatistics_H_
#define _IAS_MemoryManagerStatistics_H_

#include <commonlib/time/TimeSamplesRegister.h>

namespace IAS {

/*************************************************************************/
/** The MemoryManagerStatistics class.
 *
 */
class MemoryManagerStatistics : public Allocator {
public:

	~MemoryManagerStatistics()throw();

	void clear();

	void setSize(size_t iSize);
	void setAllocated(size_t iAllocated);
	void setHighWater(size_t iHWMark);

	size_t getSize()const { return iSize; };
	size_t getAllocated()const { return iAllocated; };
	size_t getHighWater()const { return iHWMark; };

	int getAllocationPct()const {
		if(!iSize)
			return 0;
		return 100.0*iAllocated/iSize;
	}

	MemoryManagerStatistics();

	void setSearches(const TimeSamplesResults& tsr);

	const TimeSamplesResults getSearches()const{
		return tsrAllocations;
	}


protected:

	size_t iSize;
	size_t iAllocated;
	size_t iHWMark;

	TimeSamplesResults tsrAllocations;
};

/*************************************************************************/
}

#endif /* _IAS_MemoryManagerStatistics_H_ */

