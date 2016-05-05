/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/SharedBrowserWorker.h
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
#ifndef _IAS_QS_Workers_Proc_IO_SharedBrowserWorker_H_
#define _IAS_QS_Workers_Proc_IO_SharedBrowserWorker_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>
#include <org/invenireaude/qsystem/workers/io/SharedBrowserInput.h>


#include <qs/workers/proc/wcm/io/Context.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
/** The SharedBrowserWorker class.
 *
 */
class SharedBrowserWorker :
		public Thread,
		public Runnable{
public:

	virtual ~SharedBrowserWorker() throw();

	virtual void run();

	API::Message * getNextMessage(int iTimeout);

	void addReader();
	bool removeReader();

protected:

	SharedBrowserWorker(const ::org::invenireaude::qsystem::workers::io::SharedBrowserInput* dmParameters);


	typedef IAS_DFT_FACTORY<API::Message>::PtrHoldersCollection MessageSet;

	MessageSet phcMessages;

	static const int iMaxMessagesInQueue=10;

	Mutex           mutex;
	Condition       cndReaders;
	Condition       cndWriters;

	void enqueueNextMessage(API::Browser* pBrowser);

	const ::org::invenireaude::qsystem::workers::io::SharedBrowserInput* dmParameters;

	int iTimeout;
	bool bAutoRecycle;

	bool bEndOfData;
	int iNumReaders;

	void broadcastEndOfWork();

	class EOWBroadcaster{
	public:
		 EOWBroadcaster(SharedBrowserWorker& worker):worker(worker){};
		~EOWBroadcaster(){ worker.broadcastEndOfWork(); }
	protected:
		SharedBrowserWorker& worker;
	};

	friend class Factory<SharedBrowserWorker>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_IO_SharedBrowserWorker_H_ */

