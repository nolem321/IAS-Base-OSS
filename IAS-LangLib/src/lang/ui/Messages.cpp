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
namespace Lang {
namespace UI {

Messages Messages::TheInstance;

/*************************************************************************/

Messages::Messages(){
	IAS_TRACER;

	UpdateCatalog(MSGI_LangEnvInfo,             "IASI-1001 Script Environment: &1");
	UpdateCatalog(MSGE_LangEnvError,            "IASE-1001 Script Engine Error: &1");
	UpdateCatalog(MSGE_LangScriptParseError,    "IASE-1002 Script Parse Error: &1 ");
	UpdateCatalog(MSGE_LangScriptNotFoundError, "IASE-1003 Source cannot be found: &1 ");
	UpdateCatalog(MSGE_LangScriptUsageError,    "IASE-1004 Bad script usage: &1 ");
	UpdateCatalog(MSGE_LangScriptRuntimeError,  "IASE-1010 Script Runtime Error: &1");
	UpdateCatalog(MSGE_LangInternalError,       "IASE-1999 Script Engine Internal Error: &1");

}
/*************************************************************************/
Messages::~Messages(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
