/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/DSManager.h
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
#ifndef _IAS_QS_Workers_Proc_DS_DSManager_H_
#define _IAS_QS_Workers_Proc_DS_DSManager_H_

#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS{

class DSDriver;

/*************************************************************************/
class DSManager {
public:
	virtual ~DSManager() throw(){};

	virtual DS::DSDriver *getDSDriver(const String& strName)const=0;
	virtual void addDSDriver(const String& strName, DS::DSDriver *pDSDriver)=0;

};
/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_IO_DSManager_H_ */
