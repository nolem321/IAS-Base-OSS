/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/sys/mem/ModuleProxy.h
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
#ifndef _IAS_Lang_MOD_Monitor_SYS_MEM_ModuleProxy_H_
#define _IAS_Lang_MOD_Monitor_SYS_MEM_ModuleProxy_H_

#include <lang/interpreter/extern/ModuleProxy.h>

namespace IAS  {
namespace Lang {
namespace MOD  {
namespace Monitor{
namespace SYS  {
namespace MEM   {

/*************************************************************************/
/** The ModuleProxy class.
 *
 */
class ModuleProxy : public ::IAS::Lang::Interpreter::Extern::ModuleProxy {
public:

	virtual ~ModuleProxy() throw();

	static ModuleProxy* Create();

protected:
	ModuleProxy();

	virtual void setupImpl();
	virtual void cleanUpImpl();
	friend class ::IAS::Factory<ModuleProxy>;
};
/*************************************************************************/
}
}
}
}
}
}
/*************************************************************************/
extern "C"{
void* ias_lang_mod_monitor_sys_mem_proxy();
}
/*************************************************************************/
#endif /* _IAS_Lang_MOD_Monitor_SYS_MEM_ModuleProxy_H_ */
