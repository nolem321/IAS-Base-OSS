/*
 * File: Messages.cpp
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

#include "Messages.h"


namespace IAS {
namespace SM {
namespace UI {

Messages Messages::TheInstance;

/*************************************************************************/

Messages::Messages(){
	IAS_TRACER;

	UpdateCatalog(MSGI_ServiceStarted,        "IASI-4001 Service started: &1 [&2]");
	UpdateCatalog(MSGI_ServiceStopped,        "IASI-4002 Service stopped: &1 [&2]");
	UpdateCatalog(MSGI_ServiceNotRunning,     "IASI-4003 Service was not running: &1 [&2]");
	UpdateCatalog(MSGI_ServiceRestarted,      "IASI-4004 Service restarted: &1 [&2]");
	UpdateCatalog(MSGE_ServiceFailed,         "IASE-4001 Service failed: &1 [&2]");
	UpdateCatalog(MSGE_ConfigError,           "IASE-4010 SM Configuration Error: &1 &2");
}
/*************************************************************************/
Messages::~Messages(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
