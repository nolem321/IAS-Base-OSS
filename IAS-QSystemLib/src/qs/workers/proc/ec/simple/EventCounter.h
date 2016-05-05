/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ec/simple/EventCounter.h
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
#ifndef _IAS_QS_Workers_Proc_EC_Simple_EventCounter_H_
#define _IAS_QS_Workers_Proc_EC_Simple_EventCounter_H_

#include <commonlib/commonlib.h>
#include "Data.h"

#include <org/invenireaude/qsystem/workers/ec/SimpleEventCounter.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace EC {
namespace Simple {

/*************************************************************************/
/** The EventCounter class.
 *
 */
class EventCounter : public EC::EventCounter {
public:

	virtual ~EventCounter() throw();

	virtual void update(const String& strKey,
						unsigned int iValue,
						long ts,
						org::invenireaude::qsystem::workers::ec::Ext::RecordPtr& dmOutput);

	virtual bool read(const String& strKey,
					  org::invenireaude::qsystem::workers::ec::Ext::RecordPtr& dmRecord);

	virtual void readAll(DM::DataObjectList& dmRecordsList,
						 bool bReset = true);

protected:
	EventCounter(const ::org::invenireaude::qsystem::workers::ec::SimpleEventCounter* dmParameters);

	String strName;

	IAS_DFT_FACTORY< SharedContent<Data> >::PtrHolder ptrShared;

	IAS_DFT_FACTORY< SharedMemoryFile >::PtrHolder ptrSamples;
	IAS_DFT_FACTORY< SharedMemoryFile >::PtrHolder ptrKeys;

	Data*  pData;
	Data::Sample*  pSamples;
	char*          pKeys;


	bool lookup(const String& strKey, Data::Sample* &pSample);

	size_t        appendKey(const String& strKey);

	friend class Factory<EventCounter>;

private:
	void resetIfNeeded(long ts);
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_EC_Simple_EventCounter_H_ */
