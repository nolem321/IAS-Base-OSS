/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/Base64ToBinary.h
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
#ifndef _IAS_Lang_Interpreter_Extern_Std_Base64ToBinary_H_
#define _IAS_Lang_Interpreter_Extern_Std_Base64ToBinary_H_

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
/** The Base64ToBinary class.
 *
 */
class Base64ToBinary : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~Base64ToBinary() throw();

	/** Creates an instance. */
	static Statement* Create(const StringList& lstParamaters, const ModuleProxy* pModuleProxy);


protected:
	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	Base64ToBinary(const StringList& lstParamaters, const ModuleProxy* pModuleProxy);

	friend class ::IAS::Factory<Base64ToBinary>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Std_StrToUpper_H_ */
