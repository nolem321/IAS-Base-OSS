/*
 * File: IAS-CommonLib/src/commonlib/sys/DynamicLibraryStore.h
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
#ifndef _IAS_SYS_DynamicLibraryStore_H_
#define _IAS_SYS_DynamicLibraryStore_H_

#include <commonlib/misc/InstanceFeature.h>
#include <commonlib/memory/memory.h>
#include <commonlib/containers/HashMapStringToPointer.h>
#include <commonlib/threads/Mutex.h>

namespace IAS {
namespace SYS {

class DynamicLibrary;

/*************************************************************************/
/** The DynamicLibraryStore class.
 *
 */
class DynamicLibraryStore {

public:

	virtual ~DynamicLibraryStore();

	::IAS::SYS::DynamicLibrary *getLibrary(const String& strName);

protected:

	Mutex mutex;

	DynamicLibraryStore();

	typedef HashMapStringToPointer<SYS::DynamicLibrary> LibrariesMap;
	LibrariesMap                                        hmLibraries;

	friend class Factory<DynamicLibraryStore>;
};

/*************************************************************************/
class GlobalDynamicLibraryStore:
		public DynamicLibraryStore,
		public InstanceFeature<GlobalDynamicLibraryStore>{
	protected:
		GlobalDynamicLibraryStore(){};

		friend class Factory<GlobalDynamicLibraryStore>;
};

/*************************************************************************/
}
}

#endif /* _IAS_SYS_DynamicLibraryStore_H_ */
