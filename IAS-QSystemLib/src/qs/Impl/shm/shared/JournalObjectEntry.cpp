/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/JournalObjectEntry.cpp
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
#include "JournalObjectEntry.h"


namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

/*************************************************************************/
JournalObjectEntry::JournalObjectEntry(){
	IAS_TRACER;
	reset();
}
/*************************************************************************/
JournalObjectEntry::~JournalObjectEntry() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void JournalObjectEntry::set(Queue* pQueue, bool bRemoveOnClose){
	IAS_TRACER;

	if(iType != JOE_AllocatedUnused)
		IAS_THROW(InternalException("An attempt to overwrite a JOE."))

	this->pQueue=pQueue;
	this->bRemoveOnClose=bRemoveOnClose;
	this->iType=JOE_OpenedQueue;
}
/*************************************************************************/
void JournalObjectEntry::allocate(){
	IAS_TRACER;
	if(iType != JOE_Free)
		IAS_THROW(InternalException("JOE was not free when allocating."))
	iType=JOE_AllocatedUnused;
}
/*************************************************************************/
void JournalObjectEntry::reset(){
	IAS_TRACER;
	iType=JOE_Free;
}
/*************************************************************************/
void JournalObjectEntry::rollback(){
	IAS_TRACER;

	switch(iType){

		case JOE_OpenedQueue:
			if(bRemoveOnClose)
				pQueue->remove();

			pQueue->close();
		break;

	}

	reset();
}
/*************************************************************************/
}
}
}
}
