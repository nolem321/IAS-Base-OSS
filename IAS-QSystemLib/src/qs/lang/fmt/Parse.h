/*
 * File: IAS-QSystemLib/src/qs/lang/fmt/Parse.h
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
#ifndef _IAS_QS_Lang_Fmt_Parse_H_
#define _IAS_QS_Lang_Fmt_Parse_H_

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/fmt/FmtFactory.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace Fmt {

/*************************************************************************/
/** The Parse class.
 *
 */
class Parse : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~Parse() throw();

	/** Creates an instance. */
	static Statement* Create(const StringList& lstParamaters, const IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

protected:
	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	Parse(const StringList& lstParamaters, const IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

	ThreadSpecific<Workers::Proc::WCM::WorkContextManager>::Pointer  pWorkContext;

	IAS_DFT_FACTORY<QS::Fmt::FmtFactory>::PtrHolder ptrFmtFactory;

	friend class ::IAS::Factory<Parse>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Std_Parse_H_ */
