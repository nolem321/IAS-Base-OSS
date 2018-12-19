/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/StandardModuleProxy.h
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
#ifndef _IAS_Lang_Interpreter_Extern_Std_System_StandardModuleProxy_H_
#define _IAS_Lang_Interpreter_Extern_Std_System_StandardModuleProxy_H_

#include <lang/interpreter/extern/ModuleProxy.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace System {

/*************************************************************************/
/** The StandardModuleProxy class.
 *
 */
class StandardModuleProxy : public ::IAS::Lang::Interpreter::Extern::ModuleProxy {
public:

	virtual ~StandardModuleProxy() throw();

	static StandardModuleProxy* Create();

protected:
	StandardModuleProxy();

	virtual void setupImpl();
	virtual void cleanUpImpl();
	friend class ::IAS::Factory<StandardModuleProxy>;
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
void* ias_lang_std_system_proxy();
}
/*************************************************************************/

#endif /* _IAS_Lang_Interpreter_Extern_Std_System_StandardModuleProxy_H_ */
