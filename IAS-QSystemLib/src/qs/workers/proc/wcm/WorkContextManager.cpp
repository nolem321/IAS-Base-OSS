/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/WorkContextManager.cpp
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
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "WorkContextManager.h"

#include "../GlobalContext.h"

#include "io/Manager.h"
#include "ds/Manager.h"
#include "txm/Manager.h"

#include "../io/IOFactory.h"
#include "../ds/DSFactory.h"
#include "../txm/TXMFactory.h"
#include "../txm/TXMDriver.h"

#include <org/invenireaude/qsystem/workers/Context.h>

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {

/*************************************************************************/
WorkContextManager::WorkContextManager(GlobalContext *pGlobalContext):
		pGlobalContext(pGlobalContext),
		caches(pGlobalContext){
	IAS_TRACER;

	ptrIOManager=IAS_DFT_FACTORY<IO::Manager>::Create(this);
	ptrDSManager=IAS_DFT_FACTORY<DS::Manager>::Create(this);
	ptrTXMManager=IAS_DFT_FACTORY<TXM::Manager>::Create(this);

}
/*************************************************************************/
WorkContextManager::~WorkContextManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
GlobalContext *WorkContextManager::getGlobalContext(){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pGlobalContext);
	return pGlobalContext;
}
/*************************************************************************/
Proc::IO::IOManager*  WorkContextManager::getIOManager()const{
	IAS_TRACER;
	return ptrIOManager;
}
/*************************************************************************/
Proc::DS::DSManager*  WorkContextManager::getDSManager()const{
	IAS_TRACER;
	return ptrDSManager;
}
/*************************************************************************/
void WorkContextManager::begin(){
	IAS_TRACER;
	txm.begin();
	//TODO robust commit/rollback
	//caches.rollback();
}
/*************************************************************************/
void WorkContextManager::commit(){
	IAS_TRACER;

	caches.commit();
	txm.commit();
	ds.commit();
	qs.commit();

}
/*************************************************************************/
void WorkContextManager::rollback(){
	IAS_TRACER;

	caches.rollback();
	txm.rollback();
	ds.rollback();
	qs.rollback();

}
/*************************************************************************/

}
}
}
}
}
