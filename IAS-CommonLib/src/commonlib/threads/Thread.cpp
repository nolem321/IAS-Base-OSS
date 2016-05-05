/*
 * File: IAS-CommonLib/src/commonlib/threads/Thread.cpp
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
#include "Thread.h"
#include "Runnable.h"

#include "../memory/memory.h"
#include "../logger/logger.h"
#include "../ui/Messages.h"
#include "../ui/UserMessage.h"

#include <pthread.h>
#include <signal.h>

namespace IAS {
/*************************************************************************/
Thread::Thread(Runnable *pRunnable):
		pRunnable(pRunnable),
		bIsStarted(false),
		bCanceled(false),
		theThread(0){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pRunnable);
}
/*************************************************************************/
Thread::~Thread() {
	IAS_TRACER;
	if(bIsStarted)
		stop();
}
/*************************************************************************/
void *Thread::Starter(void *pArgs){

	IAS_TRACER;

	Thread *pThread=(Thread*)pArgs;

	IAS_CHECK_IF_NULL(pThread);

	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTERM);
	pthread_sigmask(SIG_SETMASK, &set, NULL);

	try{
		Thread::Specific::SetPointer(pThread);
		pThread->pRunnable->run();
	}catch(Exception& e){
		UserMessage(Messages::MSGE_ThreadException)<<e.getName()<<e.getInfo();
#ifdef __GNUC__
	}catch(__cxxabiv1::__forced_unwind&){
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "CANCELLED !");
		throw;
#endif
	}catch(std::exception& e){
		IAS_LOG(LogLevel::INSTANCE.isError(), "std::exception:"<<e.what());
		UserMessage(Messages::MSGE_ThreadException)<<e.what();
	}catch(...){
		IAS_LOG(LogLevel::INSTANCE.isError(), "Unknown exception !");
		UserMessage(Messages::MSGE_ThreadException)<<"unknown";
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "GOOD BYE !");

	return 0;
}
/*************************************************************************/
void Thread::start() {
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pRunnable);

	int iResult = -1;

	if((iResult = pthread_create(&theThread,NULL,Starter,this)) != 0){
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "Error on thread creation, res="<<iResult<<".");
		IAS_THROW(SystemException("pthread_create", iResult));
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "Thread is stared.");

	bIsStarted=true;
	bCanceled=false;
}
/*************************************************************************/
void Thread::stop() {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isSystem(), "Canceling a thread: "<<theThread);

	if(bCanceled || !bIsStarted)
		return;

	int iRes=pthread_cancel(theThread);

	if(iRes != 0 && iRes != ESRCH ){
		IAS_LOG(LogLevel::INSTANCE.isError(), "Error: "<<iRes);
		IAS_THROW(SystemException("pthread_cancel",iRes))
	}

	bCanceled=true;
}
/*************************************************************************/
void Thread::join() {
	IAS_TRACER;

	if(!bIsStarted)
		return;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "Waiting for a thread to complete: "<<theThread);

	void *pResult;
	int iRes=pthread_join(theThread, &pResult);

	if(iRes != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(), "Error: "<<iRes);
		IAS_THROW(SystemException("pthread_join",iRes))
	}

	bIsStarted=false;
}
/*************************************************************************/
Thread::Cancellation::Cancellation(bool bEnabled):state(0){
	pthread_setcancelstate(bEnabled ? PTHREAD_CANCEL_ENABLE : PTHREAD_CANCEL_DISABLE,&state);
}
/*************************************************************************/
void Thread::Cancellation::Test(){
	Cancellation ca(true);
	pthread_testcancel();
}
/*************************************************************************/
Thread::Cancellation::~Cancellation(){

	pthread_setcancelstate(state,0);

	//if(state == PTHREAD_CANCEL_ENABLE)
	//	pthread_testcancel();

}
/*************************************************************************/
}


