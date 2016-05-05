/*
 * File: IAS-ServiceManagerLib/src/sm/mon/ProcessLockFile.h
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
#ifndef _IAS_SM_Mon_ProcessLockFile_H_
#define _IAS_SM_Mon_ProcessLockFile_H_

#include <commonlib/commonlib.h>
#include <commonlib/sys/fs/FileLock.h>
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Mon {

/*************************************************************************/
/** The ProcessLockFile class.
 *
 */
class ProcessLockFile : public ::IAS::SYS::FS::FileLock {
public:

	enum State{
		PS_ENDED,
		PS_STARTED
	};

	virtual ~ProcessLockFile() throw();


	void setProcessPidAndState(unsigned int iPid,State iState);
	void getProcessPidAndState(unsigned int& iPid,State& iState);

protected:
	ProcessLockFile(const String& strLockDir,
					const ::org::invenireaude::sm::cfg::Service* pService,
			   	    int iInstanceIdx);

	String getFileName(const ::org::invenireaude::sm::cfg::Service* pService,
			   	      int iInstanceIdx);

	friend class ::IAS::Factory<ProcessLockFile>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Mon_ProcessLockFile_H_ */
