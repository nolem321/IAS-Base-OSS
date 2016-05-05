/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/AutoCancel.cpp
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
#include "AutoCancel.h"

#include <commonlib/commonlib.h>

#include <qs/log/LogLevel.h>

#include "../GlobalContext.h"

#include "unistd.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Mode {


/*************************************************************************/
AutoCancel::AutoCancel(GlobalContext *pGlobalContext):
	pGlobalContext(pGlobalContext){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pGlobalContext);
}
/*************************************************************************/
AutoCancel::~AutoCancel() throw(){
	IAS_TRACER;

	if(!pGlobalContext)
		return;

	pGlobalContext->abort();

	//TODO (H) hangs websphere mq
	SYS::Signal::SignalHandler();
}
/*************************************************************************/
void AutoCancel::release(){
	IAS_TRACER;
	pGlobalContext=0;
}
/*************************************************************************/
}
}
}
}
}
