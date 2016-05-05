/*
 * File: IAS-QSystemLib/src/qs/net/StateMachineWorker.cpp
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
#include "StateMachineWorker.h"
#include "StateMachine.h"

namespace IAS {
namespace QS {
namespace Net {

/*************************************************************************/
StateMachineWorker::StateMachineWorker(StateMachine *pStateMachine):
		pStateMachine(pStateMachine),
		Thread(this){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pStateMachine);
}
/*************************************************************************/
StateMachineWorker::~StateMachineWorker() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StateMachineWorker::run(){
	IAS_TRACER;

	SYS::Signal::ThreadRegistration tr;

	Thread::Cancellation tc(true);

	while(true){

		Thread::Cancellation::Test();
		StateMachine::ContextWork cw(pStateMachine);

		Thread::Cancellation tc(false);

		cw.work();

	}

}
/*************************************************************************/
}
}
}
