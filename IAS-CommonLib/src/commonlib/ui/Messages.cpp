/*
 * File: IAS-CommonLib/src/commonlib/ui/Messages.cpp
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#include "Messages.h"

namespace IAS{

Messages Messages::TheInstance;

/*************************************************************************/
Messages::Messages(){
	IAS_TRACER;

	UpdateCatalog(MSGI_Start,               "IASI-0001 &1 has started.");
	UpdateCatalog(MSGI_Stop,                "IASI-0002 &1 has stopped.");
	UpdateCatalog(MSGI_ConfigInfo,          "IASI-1001 Setting &1=&2.");
	UpdateCatalog(MSGE_ConfigError,         "IASE-0001 Config error: &1");
	UpdateCatalog(MSGE_ThreadException,     "IASE-0001 Thread ended with this exception: [&1] &2");
	UpdateCatalog(MSGE_InternalError,       "IASE-9999 Internal error: &1");

}
/*************************************************************************/
Messages::~Messages(){
	IAS_TRACER;
}
/*************************************************************************/
}/* namespace IAS */

