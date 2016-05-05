/*
 * File: IAS-CommonLib/src/commonlib/threads/Condition.cpp
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
#include "Condition.h"
#include "Mutex.h"

#include "../logger/logger.h"
#include "../memory/memory.h"
#include "../tools/TypeTools.h"

#include "string.h"

namespace IAS {

/*************************************************************************/
Condition::Condition(bool bShared){

	IAS_TRACER;

	int iResult = -1;

	pthread_condattr_t cond_attr;

	if ((iResult = pthread_condattr_init(&cond_attr)) != 0)
		IAS_THROW(SystemException("pthread_condattr_init", iResult));

	if (bShared) {
		if ((iResult = pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED)) != 0)
			IAS_THROW(SystemException("PTHREAD_PROCESS_SHARED", iResult));
	}

	if ((iResult = pthread_condattr_setclock(&cond_attr, CLOCK_MONOTONIC)) != 0)
				IAS_THROW(SystemException("CLOCK_MONOTONIC", iResult));

	if((iResult = pthread_cond_init(&theCond, &cond_attr)) != 0){
		IAS_THROW(SystemException("Error memory condition creation",iResult));
	}

}
/*************************************************************************/
Condition::~Condition() throw(){
	IAS_TRACER;

	int iResult = -1;

#ifdef _linux
	if (theCond.__data.__nwaiters > 1){
		IAS_LOG(LogLevel::INSTANCE.isError(), "GLIBC skip pthread_cond_destroy after other waiting process killed !");
		return;
	}
#endif

	if((iResult = pthread_cond_destroy(&theCond)) != 0){
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "Error condition destruction, res="<<iResult<<".");
	}

}
/*************************************************************************/
void Condition::wait(Mutex& mutex) throw(ThreadLockException){
	IAS_TRACER;

	int iResult = -1;

	if( (iResult = pthread_cond_wait(&theCond, &mutex.theMutex) ) != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(), "Error on cond wait res="<<iResult<<".");
		IAS_THROW(IAS::ThreadLockException("pthread_cond_wait",iResult));
	}
}
/*************************************************************************/
bool Condition::wait(Mutex& mutex, unsigned int iTimeoutMS) throw(ThreadLockException){
	IAS_TRACER;

	int iResult = -1;

	struct timespec ts;
	::clock_gettime(CLOCK_MONOTONIC, &ts);

	//TODO (L) burak w liczeniu czasuale chyba juz ok
	ts.tv_sec += (iTimeoutMS + ts.tv_nsec/1000000) / 1000;
	//if( (ts.tv_nsec + (iTimeoutMS%1000) *1000000) > 1000000000)
	//		ts.tv_sec += 1;

	ts.tv_nsec = (ts.tv_nsec  + (iTimeoutMS%1000) *1000000) % 1000000000;

	if( (iResult = pthread_cond_timedwait(&theCond, &mutex.theMutex, &ts) ) != 0){

		if(iResult == ETIMEDOUT){
			IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Current: "<<TypeTools::GetTimeMS());
			return false;
		}

		IAS_LOG(LogLevel::INSTANCE.isError(), "Error on cond wait res="<<iResult<<":"<<strerror(iResult));
		IAS_THROW(IAS::ThreadLockException("pthread_cond_wait",iResult));
	}

	return true;
}
/*************************************************************************/

void Condition::signal() throw(ThreadLockException){
	IAS_TRACER;

#ifdef IAS_FEATURE_THREAD_SAFE
	int iResult = -1;

	if( (iResult = pthread_cond_signal(&theCond)) != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(), "Error on cond signal res="<<iResult<<".");
		IAS_THROW(IAS::ThreadLockException("pthread_cond_signal",iResult));
	}
#endif

}

/*************************************************************************/
void Condition::broadcast() throw(ThreadLockException){
	IAS_TRACER;

#ifdef IAS_FEATURE_THREAD_SAFE
	int iResult = -1;

	if((iResult = pthread_cond_broadcast(&theCond)) != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(), "Error on cond broadcast res="<<iResult<<".");
		IAS_THROW(IAS::ThreadLockException("pthread_cond_broadcast",iResult));
	}
#endif

}
/*************************************************************************/

}
