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
namespace QS {
namespace UI {

Messages Messages::TheInstance;

/*************************************************************************/

Messages::Messages(){
	IAS_TRACER;

	UpdateCatalog(MSGI_LogicStarted,          "IASI-2001 Worker Started: &1");
	UpdateCatalog(MSGI_LogicStopped,          "IASI-2001 Worker Ended: &1");
	UpdateCatalog(MSGE_LogicFailed,           "IASE-2001 Worker has failed: &1 ");
	UpdateCatalog(MSGE_ScriptFailed,          "IASE-2002 Script has failed: &1 &2");
	UpdateCatalog(MSGE_ScriptException,       "IASE-2003 Script has thrown an exception: &1 &2");
	UpdateCatalog(MSGE_Rollback,              "IASE-2004 Rollback: &1 &2");
  UpdateCatalog(MSGE_Communication,         "IASE-2005 Communication: &1 &2");
	UpdateCatalog(MSGE_ConfigError,           "IASE-2010 QS Configuration Error: &1 &2");
}
/*************************************************************************/
Messages::~Messages(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
