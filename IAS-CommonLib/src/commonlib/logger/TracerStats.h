/*
 * File: IAS-CommonLib/src/commonlib/logger/TracerStats.h
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
#ifndef _IAS_TracerStats_H_
#define _IAS_TracerStats_H_

#include "../types.h"
#include <iostream>
#include <map>
#include<string.h>

#include "../threads/Mutex.h"

#include <commonlib/time/TimeSamplesRegister.h>

namespace IAS {

/*************************************************************************/
/** The TracerStats class.
 */

class TracerStats  {
public:
	TracerStats()throw();
	virtual ~TracerStats() throw();

	void printToStream(std::ostream& os);

	inline static TracerStats *GetInstance(){
		if(pInstance == NULL)
			pInstance = new TracerStats;
		return pInstance;
	}

	void addEntry(const char* sFile, const char*sFun, const TimeSample& ts);

 private:

	 struct KeyPair{
		 KeyPair(const char* sFile, const char*sFun):strFile(sFile),strFun(sFun){};

		 KeyPair(const KeyPair& other){
			 strFile=other.strFile;
			 strFun=other.strFun;
		 }

		 /* TODO (L) - do something about symbol lookups */
		 /* we need to store a copy - as the dynamic loader may unload symobols :( */
		 /* but maybe we do need to create a strings pair for each lookup */

		 String strFile;
		 String strFun;


		 bool operator==(const KeyPair& other) const{
			 return strFile.compare(other.strFile) == 0 && strFun.compare(other.strFun) ==0;
		 }

		 bool operator<(const KeyPair& other) const {
			 return strFile.compare(other.strFile) < 0 ||
					 (strFile.compare(other.strFile) == 0 &&
					  strFun.compare(other.strFun) < 0);
		 }

		 KeyPair& operator=(const KeyPair& other){
			 strFile=other.strFile;
			 strFun=other.strFun;
			 return *this;
		 }
	 };



	typedef std::map<KeyPair, TimeSamplesResults> EntryMap;

	static TracerStats *pInstance;
	EntryMap hmEntries;

	long iTotalEntries;
	long iCurEntries;

	Mutex theLock;
};

}

#endif /* TRACERSTATS_H_ */
