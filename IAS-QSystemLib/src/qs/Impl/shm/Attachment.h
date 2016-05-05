/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Attachment.h
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
#ifndef _IAS_QS_System_Attachment_H_
#define _IAS_QS_System_Attachment_H_

#include <qs/api.h>

#include <commonlib/commonlib.h>
#include <commonlib/memory/mm/SimpleListMemoryManager.h>
#include <commonlib/memory/mm/PowerOfTwoMemoryManager.h>

#include <qs/Impl/System.h>

#include "org/invenireaude/qsystem/System.h"
#include <org/invenireaude/qsystem/stats/SystemStats.h>

using namespace ::org::invenireaude::qsystem;


namespace IAS {
namespace QS {
namespace SHM {

class ContentManager;

namespace Admin {
class ActionDispatcher;
}

namespace Shared {

class System;
class SharedMemorySegment;
class Queue;
class QueueTable;
class SessionTable;
class Connection;
class ContentStorage;

}
/*************************************************************************/
/** The Attachment class.
 *
 */
class Attachment {
public:

	virtual ~Attachment() throw();

	class Locker : public Mutex::Locker{
		public:
		Locker(Attachment* pAttachment);
		~Locker();
	};

	static ::IAS::Allocator* GetAllocatorForSystem();
	static ::IAS::Allocator* GetAllocatorForQueueData();
	static ::IAS::Allocator* GetAllocatorForApplicationData();

	API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	Shared::QueueTable*   getQueueTable();
	Shared::SessionTable* getSessionTable();
	ContentManager*  	  getContentManager();


	Admin::ActionDispatcher* getActionDispatcher();

	void dumpInfo(std::ostream& os);


	stats::Ext::SystemStatsPtr getStats(bool bReset);

	const String& getName()const { return strName; }

protected:

	Attachment(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);
	Attachment(::org::invenireaude::qsystem::Ext::SystemPtr dmAttachment);

	IAS_DFT_FACTORY< SharedContent<Shared::System> >::PtrHolder   ptrShared;
	Shared::System* getShared();

	SharedMemoryFile* createSHM(const String& strName, size_t iSize);
	SharedMemoryFile* attachSHM(const String& strName, void *pAddress);

	IAS_DFT_FACTORY< SharedMemoryFile >::PtrHolder            ptrSHMSystemHeap;
	IAS_DFT_FACTORY< SharedMemoryFile >::PtrHolder            ptrSHMQueueData;
	IAS_DFT_FACTORY< SharedMemoryFile >::PtrHolder            ptrSHMApplicationData;

	static IAS_DFT_FACTORY< SimpleListMemoryManager >::PtrHolder     TheMMSystemHeap;
	static IAS_DFT_FACTORY< SimpleListMemoryManager >::PtrHolder     TheMMQueueData;
	static IAS_DFT_FACTORY< PowerOfTwoMemoryManager >::PtrHolder     TheMMApplicationData;


	IAS_DFT_FACTORY<Admin::ActionDispatcher>::PtrHolder ptrActionDispatcher;

	String buildSHMName(const String& strName);

	Shared::ContentStorage* getContentStorage();

	IAS_DFT_FACTORY< ContentManager >::PtrHolder               ptrContentManager;

	String strName;
	friend class Factory<Attachment>;
};

template<class T>
class SystemAllocator :
		public ::IAS::AllocatorFactory<T,Attachment::GetAllocatorForSystem, StaticCastOperator<T> >{};

template<class T>
class QueueAllocator :
		public ::IAS::AllocatorFactory<T,Attachment::GetAllocatorForQueueData, StaticCastOperator<T> >{};

template<class T>
class ApplicationAllocator :
		public ::IAS::AllocatorFactory<T,Attachment::GetAllocatorForApplicationData, StaticCastOperator<T> >{};

/*************************************************************************/

}
}
}

#endif /* _IAS_QS_System_Attachment_H_ */
