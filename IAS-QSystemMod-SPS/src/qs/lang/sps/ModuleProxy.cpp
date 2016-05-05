/*
 * File: IAS-QSystemMod-SPS/src/qs/lang/sps/ModuleProxy.cpp
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
#include "ModuleProxy.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "GetDocument.h"
#include "SetDocument.h"
#include "SendAsyncRequest.h"
#include "SetNextActivity.h"
#include "SetVersion.h"
#include "Terminate.h"

namespace IAS {
namespace QS {
namespace Lang {
namespace SPS {

/*************************************************************************/
ModuleProxy::ModuleProxy(){
	IAS_TRACER;
}
/*************************************************************************/
ModuleProxy::~ModuleProxy() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ModuleProxy::setupImpl(){
	IAS_TRACER;
	registerSymbol("GetDocument",        &(GetDocument::Create));
	registerSymbol("SetDocument",        &(SetDocument::Create));
	registerSymbol("SendAsyncRequest",   &(SendAsyncRequest::Create));
	registerSymbol("SetNextActivity",    &(SetNextActivity::Create));
	registerSymbol("SetVersion",         &(SetVersion::Create));
	registerSymbol("Terminate",          &(Terminate::Create));
}
/*************************************************************************/
void ModuleProxy::cleanUpImpl(){
	IAS_TRACER;
}
/*************************************************************************/
ModuleProxy* ModuleProxy::Create(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ModuleProxy>::Create();
}
/*************************************************************************/
}
}
}
}
/*************************************************************************/
void* ias_qs_lang_sps_proxy(){
	IAS_TRACER;
	return ::IAS::QS::Lang::SPS::ModuleProxy::Create();
}
/*************************************************************************/
