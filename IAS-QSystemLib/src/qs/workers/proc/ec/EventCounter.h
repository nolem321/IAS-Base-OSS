/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ec/EventCounter.h
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
#ifndef _IAS_QS_Workers_Proc_EC_EventCounter_H_
#define _IAS_QS_Workers_Proc_EC_EventCounter_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/ec/Record.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace EC {

/*************************************************************************/
class EventCounter{
	public:

	virtual ~EventCounter() throw(){};

	virtual void update(const String& strKey,
						unsigned int iValue,
						long ts,
						org::invenireaude::qsystem::workers::ec::Ext::RecordPtr& dmOutput)=0;

	virtual bool read(const String& strKey,
					  org::invenireaude::qsystem::workers::ec::Ext::RecordPtr& dmRecord)=0;

	virtual void readAll(DM::DataObjectList& dmRecordsList,
						 bool bReset = true)=0;


};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_EC_EventCounter_H_ */
