/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/MemoryManagerStatistics.cpp
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
#include <commonlib/commonlib.h>
#include "MemoryManagerStatistics.h"
#include "commonlib/exception/InternalException.h"

namespace IAS {

/*************************************************************************/
MemoryManagerStatistics::MemoryManagerStatistics():
	iAllocated(0),
	iHWMark(0),
	iSize(0){}
/*************************************************************************/
MemoryManagerStatistics::~MemoryManagerStatistics()throw(){}
/*************************************************************************/
void MemoryManagerStatistics::clear(){
	IAS_TRACER;
	iAllocated=iHWMark=iSize=0;
}
/*************************************************************************/
void MemoryManagerStatistics::setSize(size_t iSize){
	IAS_TRACER;
	this->iSize=iSize;
}
/*************************************************************************/
void MemoryManagerStatistics::setAllocated(size_t iAllocated){
	IAS_TRACER;
	this->iAllocated=iAllocated;
}
/*************************************************************************/
void MemoryManagerStatistics::setHighWater(size_t iHWMark){
	IAS_TRACER;
	this->iHWMark=iHWMark;
}
/*************************************************************************/
void MemoryManagerStatistics::setSearches(const TimeSamplesResults& tsr){
	IAS_TRACER;
	this->tsrAllocations=tsr;
}
/*************************************************************************/

}

