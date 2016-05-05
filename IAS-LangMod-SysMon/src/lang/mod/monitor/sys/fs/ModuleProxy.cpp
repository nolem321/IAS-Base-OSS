/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/sys/fs/ModuleProxy.cpp
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
#include "../../../monitor/sys/fs/ModuleProxy.h"

#include <lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "GetUsage.h"

namespace IAS  {
namespace Lang {
namespace MOD  {
namespace Monitor{
namespace SYS  {
namespace FS   {

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
	registerSymbol("GetUsage",  &(GetUsage::Create));
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
}
}
/*************************************************************************/
void* ias_lang_mod_monitor_sys_fs_proxy(){
	IAS_TRACER;
	return ::IAS::Lang::MOD::Monitor::SYS::FS::ModuleProxy::Create();
}
/*************************************************************************/
