/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/ProcessCacheEntry.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPS_ProcessCacheEntry_H_
#define _IAS_QS_Workers_Proc_Logic_SPS_ProcessCacheEntry_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/sps/ProcessInstance.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

class ProcessDataStore;

/*************************************************************************/
/** The ProcessCacheEntry class.
 *
 */
class ProcessCacheEntry : public RefCountingPointee {
public:

	virtual ~ProcessCacheEntry() throw();

	void updateProcessInstance(org::invenireaude::qsystem::workers::sps::ProcessInstance*);

	org::invenireaude::qsystem::workers::sps::ProcessInstance* getProcessInstance()const;

	void decNumPending();
	int  getNumPending()const;

	void step();

	void registerRequest();
	int getNumRequests()const;

	DM::DataObjectPtr getDocument(const String& strName);
	void setDocument(const String& strName, DM::DataObject* dm);

	void setSetNextActivity(const String& strNextActivity);

	void schedule();
	void enqueueForSchedule();
	void enqueueForEvent();

	void save(ProcessDataStore* pDataStore);
	void loadDocuments(ProcessDataStore* pDataStore);

	void terminate(const String& strInfo);

	bool isTerminated()const;

	typedef HashMapWithStringKey< DM::DataObjectPtr > DocumentsMap;

protected:

	ProcessCacheEntry(org::invenireaude::qsystem::workers::sps::Ext::ProcessInstancePtr dmProcessInstance);
	ProcessCacheEntry(const String& strID,
			          const String& strProcessName,
			          ProcessDataStore* pDataStore);

	org::invenireaude::qsystem::workers::sps::Ext::ProcessInstancePtr dmProcessInstance;


	//TODO better structure for modified documents
	typedef HashMapWithStringKey<bool>                 DocumentNameSet;

	DocumentsMap 		hmDocuments;
	DocumentNameSet		setModifiedDocuments;
	DocumentNameSet		setNewDocuments;

	int iNumRequests;
	String strNextActivity;

	friend class Factory<ProcessCacheEntry>;
};

typedef IAS_DFT_FACTORY<ProcessCacheEntry>::RefCountingPtr ProcessCacheEntryPtr;
/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPS_ProcessCacheEntry_H_ */
