/*
 * File: IAS-QSystemLib/src/qs/net/StateMachineWorkManager.cpp
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
#include "StateMachineWorkManager.h"
#include "StateMachineWorker.h"

namespace IAS {
namespace QS {
namespace Net {

/*************************************************************************/
StateMachineWorkManager::StateMachineWorkManager(StateMachine *pStateMachine, int iNumWorkers){
	IAS_TRACER;

	while(iNumWorkers--){
		phcWorkers.addPointer(IAS_DFT_FACTORY<StateMachineWorker>::Create(pStateMachine));
	}

}
/*************************************************************************/
StateMachineWorkManager::~StateMachineWorkManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StateMachineWorkManager::start(){
	IAS_TRACER;

	for(WorkersSet::iterator it=phcWorkers.begin();
			it != phcWorkers.end();it++){
		(*it)->start();
	}

}
/*************************************************************************/
void StateMachineWorkManager::stop(){
	IAS_TRACER;

	for(WorkersSet::iterator it=phcWorkers.begin();
			it != phcWorkers.end();it++){
		(*it)->stop();
	}

}
/*************************************************************************/
void StateMachineWorkManager::join(){
	IAS_TRACER;

	for(WorkersSet::iterator it=phcWorkers.begin();
			it != phcWorkers.end();it++){
		(*it)->join();
	}
}
/*************************************************************************/
}
}
}
