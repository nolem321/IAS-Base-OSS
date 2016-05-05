/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/ProcessDataStore.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPS_ProcessDataStore_H_
#define _IAS_QS_Workers_Proc_Logic_SPS_ProcessDataStore_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/sps/ProcessInstance.h>
#include <org/invenireaude/qsystem/workers/sps/ProcessArray.h>
#include <org/invenireaude/qsystem/workers/sps/DocumentsArray.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/prog/ProgramSet.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

/*************************************************************************/
/** The ProcessDataStore class.
 *
 */

class WrappedStatement;

class ProcessDataStore {
public:

	virtual ~ProcessDataStore() throw();

	void createProcessInstance(org::invenireaude::qsystem::workers::sps::Ext::ProcessInstancePtr dmProcessInstance)const;
	void saveProcessInstance(org::invenireaude::qsystem::workers::sps::Ext::ProcessInstancePtr dmProcessInstance)const;

	org::invenireaude::qsystem::workers::sps::Ext::ProcessInstancePtr loadAndLockProcessInstance(const String& strPID)const;

	void createDocument(const String& strPID,const String& strName, DM::DataObject* dm)const;
	void saveDocument(const String& strPID,const String& strName, DM::DataObject* dm)const;

	org::invenireaude::qsystem::workers::sps::Ext::DocumentsArrayPtr loadDocuments(const String& strPID)const;

	void getProcessesToSchedule(org::invenireaude::qsystem::workers::sps::Ext::ProcessArrayPtr dmArray, int iMaxEntries );
	void getProcessesToClean(org::invenireaude::qsystem::workers::sps::Ext::ProcessArrayPtr dmArray, int iMaxEntries );

protected:
	ProcessDataStore(const String& strDataSource);

	String strDataSource;

	ThreadSpecific<Workers::Proc::WCM::WorkContextManager>::Pointer  pWorkContext;
	IAS_DFT_FACTORY<Workers::Proc::Prog::ProgramSet>::PtrHolder ptrProgramSet;

	friend class Factory<ProcessDataStore>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPS_ProcessDataStore_H_ */
