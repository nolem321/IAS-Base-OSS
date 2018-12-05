/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/Load.h
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
#ifndef _IAS_Lang_Interpreter_Extern_Std_Load_H_
#define _IAS_Lang_Interpreter_Extern_Std_Load_H_

#include <lang/interpreter/extern/Statement.h>


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe{
class Context;
}
namespace Extern {
namespace Std {

/*************************************************************************/
/** The Load class.
 *
 */
class Load : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~Load() throw();

	/** Creates an instance. */
	static Statement* Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy);

protected:

	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	Load(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy);

	friend class ::IAS::Factory<Load>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Std_Load_H_ */
