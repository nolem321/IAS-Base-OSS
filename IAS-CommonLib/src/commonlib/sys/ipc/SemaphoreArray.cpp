/*
 * File: IAS-CommonLib/src/commonlib/sys/ipc/SemaphoreArray.cpp
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
#include "SemaphoreArray.h"

#include <commonlib/commonlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

namespace IAS {
namespace IPC {

/*************************************************************************/
SemaphoreArray::Descriptor::Descriptor(ResourceDescriptor::Mode iMode) throw() :
	ResourceDescriptor(iMode),iNumSem(1) {
	IAS_TRACER;
}
/*************************************************************************/
void SemaphoreArray::Descriptor::setNumSem(int iNumSem) {
	IAS_TRACER;
	this->iNumSem = iNumSem;
}
/*************************************************************************/
int SemaphoreArray::Descriptor::getNumSem() const {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "NumSem: "<<iNumSem);
	return iNumSem;
}
/*************************************************************************/

/*************************************************************************/
void SemaphoreArray::Semaphore::lock(){
	IAS_TRACER;
	dec();
}
/*************************************************************************/
void SemaphoreArray::Semaphore::unlock(){
	inc();
}
/*************************************************************************/
SemaphoreArray::Semaphore::Semaphore(const Semaphore& other){
	IAS_TRACER;
	iSemId=other.iSemId;
	iIdx=other.iIdx;
}
/*************************************************************************/
SemaphoreArray::Semaphore::Semaphore(int iSemId, int iIdx):
	iSemId(iSemId),
	iIdx(iIdx){
	IAS_TRACER;
}
/*************************************************************************/

/*************************************************************************/
SemaphoreArray::SemaphoreArray(const SemaphoreArray::Descriptor& aDescriptor) :
	aDescriptor(aDescriptor),
	iSemId(-1){
	IAS_TRACER;
	init();
}
/*************************************************************************/
SemaphoreArray::~SemaphoreArray() throw () {
	IAS_TRACER;

	if(aDescriptor.getDeleteOnCleanUp()){
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "SemaphoreArray will be deleted: "<<iSemId);
		semctl(iSemId, 0, IPC_RMID);
	}
}
/*************************************************************************/
void SemaphoreArray::init() {
	IAS_TRACER;

	key_t key = aDescriptor.getKey();

	iNumSem = aDescriptor.getNumSem();

	iSemId = semget(key, iNumSem, aDescriptor.getOpenFlags());

	if (iSemId == -1) {
		IAS_THROW(SystemException("SemaphoreArray::semget",errno));
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "SemaphoreArray of "<<iNumSem<<", iSemId="<<iSemId);
}
/*************************************************************************/
void SemaphoreArray::Semaphore::reset() {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "reset, iSemid="<<iSemId<<":"<<iIdx);

	int iRes = semctl(iSemId, iIdx, SETVAL, 0);

	if (iRes == -1) {
		IAS_THROW(SystemException("SemaphoreArray::reset",errno));
	}

}
/*************************************************************************/
void SemaphoreArray::resetAll() {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "resetAll, iSemid="<<iSemId);

	short *args = new short[iNumSem];

	for(int iIdx = 0; iIdx<iNumSem;iIdx++)
		args[iIdx]=0;

	int iRes = semctl(iSemId, 0, SETALL, args);

	delete[] args;

	if (iRes == -1) {
		IAS_THROW(SystemException("SemaphoreArray::resetAll",errno));
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "reset, iSemid="<<iSemId);
}
/*************************************************************************/
void SemaphoreArray::Semaphore::inc(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "inc, iSemid="<<iSemId<<":"<<iIdx);

	struct sembuf arg;

	arg.sem_flg = 0;
	arg.sem_num = iIdx;
	arg.sem_op = 1;

	int iRes = semop(iSemId, &arg, 1);

	if (iRes == -1) {
		IAS_THROW(SystemException("SemaphoreArray::inc",errno));
	}
}
/*************************************************************************/
void SemaphoreArray::Semaphore::dec() {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "dec, iSemid="<<iSemId<<":"<<iIdx);

	struct sembuf arg;

	arg.sem_flg = 0 | SEM_UNDO;
	arg.sem_num = iIdx;
	arg.sem_op = -1;

	int iRes = semop(iSemId, &arg, 1);

	if (iRes == -1) {
		IAS_THROW(SystemException("SemaphoreArray::dec",errno));
	}
}
/*************************************************************************/
bool SemaphoreArray::Semaphore::decNoWait() {

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "decNoWait, iSemid="<<iSemId<<":"<<iIdx);

	struct sembuf arg;

	arg.sem_flg = IPC_NOWAIT;
	arg.sem_num = iIdx;
	arg.sem_op = -1;

	int iRes = semop(iSemId, &arg, 1);

	if(iRes == 0)
		return true;

	if(iRes == -1 && errno == EAGAIN)
		return false;

	IAS_THROW(SystemException("SemaphoreArray::decNoWait",errno));

}
/*************************************************************************/
int SemaphoreArray::Semaphore::get() const {
	IAS_TRACER;

	int iRes = semctl(iSemId, iIdx, GETVAL, 0);

	if (iRes == -1) {
		IAS_THROW(SystemException("SemaphoreArray::reset",errno));
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "get, iSemid="<<iSemId<<":"<<iIdx<<"="<<iRes);

	return iRes;
}
/*************************************************************************/
SemaphoreArray::Semaphore SemaphoreArray::operator[](int iIdx){

	IAS_TRACER;

	if (iIdx < 0 || iIdx >= iNumSem)
	IAS_THROW(BadUsageException("SemaphoreArray::dec: bad iIdx."));

	return Semaphore(iSemId,iIdx);
}
/*************************************************************************/
}
}
