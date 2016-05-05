/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ec/simple/Data.h
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
#ifndef _IAS_QS_Workers_Proc_EC_Simple_Data_H_
#define _IAS_QS_Workers_Proc_EC_Simple_Data_H_

#include <commonlib/commonlib.h>

#include "../EventCounter.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace EC {
namespace Simple {

/*************************************************************************/
/** The Data class.
 *
 */
struct Data {
public:

	struct Settings {

		size_t iMaxNumSamples;
		size_t iResetInterval;
		size_t iKeyStorageSize;

	};



	struct Record{

		unsigned int  iCount;

		unsigned int  iMin;
		unsigned int  iMax;
		unsigned long iTotal;
	};

	struct Sample{
		unsigned int tsUpdate;
		size_t       iKeyOffset;
		Record       record;
	};

	Mutex theMutex;

	long tsVersion;
	long iNumSamples;

	Settings settings;

	size_t iKeyStorageUsed;

	Data(const Settings& settings);

	bool isEmpty()const{ return tsVersion == 0;} ;

};
/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_EC_Simple_Data_H_ */
