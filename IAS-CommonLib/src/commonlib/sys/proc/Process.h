/*
 * File: IAS-CommonLib/src/commonlib/sys/proc/Process.h
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
#ifndef _IAS_SYS_Proc_Process_H_
#define _IAS_SYS_Proc_Process_H_

#include "commonlib/types.h"

namespace IAS {
namespace SYS {
namespace Proc {
class Runnable;
/*************************************************************************/
/** The Process class.
 *
 */
class Process {
public:

	Process(Runnable* pRunnable);
	virtual ~Process() throw();

	void setOutputStream(const String& strPath);
	void setErrorStream(const String& strPath);
	void setInputStream(const String& strPath);

	void updateEnvironment(const StringPairList& lstEnvironment);

	void disableOutputStream();
	void disableErrorStream();
	void disableInputStream();
	void disableAllStreams();

	void start();
	void stop();
	void kill(int iSignal);
	void wait();

	bool isRunning();
	int getPid()const;

protected:


	Runnable* pRunnable;
	bool bIsStarted;

	int iPid;

	virtual void startRunnable();

	int    iFDInput;
	int    iFDOutput;
	int    iFDError;

	StringPairList lstEnvironment;

	void setupStream(int iFDStream, int& iFDNEw);

};

/*************************************************************************/
}
}
}

#endif /* _IAS_SYS_Proc_Process_H_ */
