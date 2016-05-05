/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Content.cpp
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
#include "Content.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/Attachment.h>

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Content::Content(const Shared::ContentStorage::Descriptor& descriptor):
		descriptor(descriptor),
		pEntry(0){
	IAS_TRACER;

	pEntry=this->descriptor.getEntry();

	Mutex::Locker locker(pEntry->mutex);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Before: "<<((void*)this)<<", pMemorySlot="<<pEntry->pMemorySlot);

	if(!pEntry->pMemorySlot){
		pEntry->pMemorySlot=StreamMemoryBuffer::Create(Attachment::GetAllocatorForApplicationData());
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Setting: "<<((void*)this)<<", pMemorySlot="<<pEntry->pMemorySlot<<", "<<(void*)(pEntry));

	ptrSMB=IAS_DFT_FACTORY<StreamMemoryBuffer>::Create(pEntry->pMemorySlot,Attachment::GetAllocatorForApplicationData());

	this->init(ptrSMB);
}
/*************************************************************************/
void Content::Destroy(Shared::ContentStorage::Entry* pEntry){
	IAS_TRACER;

	if(!pEntry->pMemorySlot)
		return;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Recycle memory slot.");

	StreamMemoryBuffer::Destroy(pEntry->pMemorySlot,Attachment::GetAllocatorForApplicationData());
	pEntry->pMemorySlot=0;
}
/*************************************************************************/
Content::~Content() throw(){
	IAS_TRACER;
    flush();
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Leaving: "<<((void*)this)<<", pMemorySlot="<<pEntry->pMemorySlot);
}
/*************************************************************************/
const Shared::ContentStorage::Descriptor& Content::getDescriptor() const{
	return descriptor;
}
/*************************************************************************/

}
}
}
