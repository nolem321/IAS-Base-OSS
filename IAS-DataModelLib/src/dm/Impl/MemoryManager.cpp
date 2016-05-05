/*
 * File: IAS-DataModelLib/src/dm/Impl/MemoryManager.cpp
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
#include "../../dm/Impl/MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
MemoryManager* MemoryManager::TheInstance(NULL);
ThreadSpecific<Allocator> PtrDataAllocator;
/*************************************************************************/
MemoryManager::MemoryManager(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Default settings.");

	pAllocatorForData=IAS_DFT_FACTORY< ::IAS::MemoryManager >::Create();
	PtrDataAllocator.SetPointer(pAllocatorForData);

	pAllocatorForTypes=IAS_DFT_FACTORY< ::IAS::MemoryManager >::Create();
}
/*************************************************************************/
MemoryManager::~MemoryManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void MemoryManager::setAllocatorForData(IAS::Allocator* pAllocator){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pAllocator);
	this->pAllocatorForData=pAllocator;
	PtrDataAllocator.SetPointer(pAllocatorForData);
}
/*************************************************************************/
IAS::Allocator* MemoryManager::GetAllocatorForData(){
	IAS_TRACER;
	if(!TheInstance)
		Create();
	IAS_CHECK_IF_NULL(TheInstance);
	return TheInstance->getAllocatorForData();;
}
/*************************************************************************/
IAS::Allocator* MemoryManager::GetAllocatorForTypes(){
	IAS_TRACER;
	if(!TheInstance)
		Create();
	IAS_CHECK_IF_NULL(TheInstance);
	return TheInstance->getAllocatorForTypes();
}
/*************************************************************************/
MemoryManager* MemoryManager::GetInstance(){
	IAS_TRACER;
	if(!TheInstance)
		Create();
	IAS_CHECK_IF_NULL(TheInstance);
	return TheInstance;
}
/*************************************************************************/
IAS::Allocator* MemoryManager::getAllocatorForData() {
	IAS_TRACER;

	//TODO (M) revise this thread specific implementation - it looks like prototyping.

	if(! PtrDataAllocator.GetPointer())
		PtrDataAllocator.SetPointer(IAS_DFT_FACTORY< ::IAS::MemoryManager >::Create());

	return PtrDataAllocator.GetPointer();
}
/*************************************************************************/
IAS::Allocator* MemoryManager::getAllocatorForTypes() {
	IAS_TRACER;
	if(!TheInstance)
		Create();
	return pAllocatorForTypes;
}
/*************************************************************************/
void MemoryManager::PrintToStream(std::ostream& os, bool bNewOnly) {
	//TheInstance->pAllocatorForTypes->printToStream(os,bNewOnly);
	//TheInstance->pAllocatorForData->printToStream(os,bNewOnly);
}
/*************************************************************************/
void MemoryManager::Create(){
	IAS_TRACER;
	TheInstance=IAS_DFT_FACTORY<MemoryManager>::Create();
}
/*************************************************************************/
}
}
}
