/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/StandardModuleProxy.cpp
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
#include "StandardModuleProxy.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "ExecuteAdHoc.h"
#include "Load.h"
#include "Save.h"
#include "SysLog.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace System {

/*************************************************************************/
StandardModuleProxy::StandardModuleProxy(){
	IAS_TRACER;
}
/*************************************************************************/
StandardModuleProxy::~StandardModuleProxy() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StandardModuleProxy::setupImpl(){

	IAS_TRACER;

	registerSymbol("ExecuteAdHoc",&(ExecuteAdHoc::Create));
	registerSymbol("Load",&(Load::Create));
	registerSymbol("Save",&(Save::Create));
  registerSymbol("SysLog",&(SysLog::Create));
}
/*************************************************************************/
void StandardModuleProxy::cleanUpImpl(){
	IAS_TRACER;
}
/*************************************************************************/
StandardModuleProxy* StandardModuleProxy::Create(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<StandardModuleProxy>::Create();
}
/*************************************************************************/
}
}
}
}
}
}
/*************************************************************************/
void* ias_lang_std_system_proxy(){
	IAS_TRACER;
	return ::IAS::Lang::Interpreter::Extern::Std::System::StandardModuleProxy::Create();
}
/*************************************************************************/

