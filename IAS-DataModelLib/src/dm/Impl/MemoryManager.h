/*
 * File: IAS-DataModelLib/src/dm/Impl/MemoryManager.h
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
#ifndef _IAS_DM_Impl_MemoryManager_H_
#define _IAS_DM_Impl_MemoryManager_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
/** The MemoryManager class.
 *
 */
class MemoryManager {
public:

	virtual ~MemoryManager() throw();

	/** Creates an instance. */
	static void Create();

	static IAS::Allocator* GetAllocatorForData();
	static IAS::Allocator* GetAllocatorForTypes();

	virtual IAS::Allocator* getAllocatorForData();
	virtual IAS::Allocator* getAllocatorForTypes();

	virtual void setAllocatorForData(IAS::Allocator* pAllocator);

	static void PrintToStream(std::ostream& os);

	static MemoryManager* GetInstance();


protected:
	MemoryManager();

	static MemoryManager* TheInstance;

	//TODO realy auto delete ?
	//IAS_DFT_FACTORY<Allocator>::PtrHolder  ptrAllocatorForData;
	//IAS_DFT_FACTORY<Allocator>::PtrHolder  ptrAllocatorForTypes;
	IAS::Allocator  *pAllocatorForData;
	IAS::Allocator  *pAllocatorForTypes;

	friend class ::IAS::Factory<MemoryManager>;
};

template<class T>
class ModelAllocator : public ::IAS::AllocatorFactory<T, Impl::MemoryManager::GetAllocatorForTypes >{};

template<class T>
class DataAllocator : public ::IAS::AllocatorFactory<T, Impl::MemoryManager::GetAllocatorForData >{};
/*
template<class T>
class ModelAllocator : public ::IAS2::MemoryManagerFactory<T>{};

template<class T>
class DataAllocator : public ::IAS2::MemoryManagerFactory<T>{};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_MemoryManager_H_ */
