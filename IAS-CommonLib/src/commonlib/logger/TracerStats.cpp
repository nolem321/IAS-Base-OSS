/*
 * File: IAS-CommonLib/src/commonlib/logger/TracerStats.cpp
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
#include "TracerStats.h"

namespace IAS {

TracerStats* TracerStats::pInstance = NULL;

TracerStats::TracerStats() throw(){

	iTotalEntries = 0;
	iCurEntries   = 0;
}

TracerStats::~TracerStats() throw(){}

/*************************************************************************/
void TracerStats::addEntry(const char* sFile, const char* sFun,  const TimeSample& ts){

	Mutex::Locker locker(theLock);

	KeyPair key(sFile, sFun);

	hmEntries[key].addSample(ts);

}
/*************************************************************************/

void TracerStats::printToStream(std::ostream& os){

	Mutex::Locker locker(theLock);

	os << " >>>  EXECUTION TIMEs " << std::endl;
	os << " >>>  Total:    " << iTotalEntries << std::endl;
	os << " >>>  Current:  " << iCurEntries << std::endl;

	EntryMap::iterator iter;

	for (iter = hmEntries.begin(); iter != hmEntries.end(); iter++) {



		os.width(70);
		os << iter->first.strFile << ": ";
		os.width(30);
		os << iter->first.strFun << ": ";
		os << (iter->second)<<std::endl;
	}/* for */

	os << std::endl;
}

}
