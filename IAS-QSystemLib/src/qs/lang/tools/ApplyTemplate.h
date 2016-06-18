/*
 * File: IAS-QSystemLib/src/qs/lang/tools/ApplyTemplate.h
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
#ifndef _IAS_QS_Lang_Tools_ApplyTemplate_H_
#define _IAS_QS_Lang_Tools_ApplyTemplate_H_

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {

/*************************************************************************/
/** The ApplyTemplate class.
 *
 */
class ApplyTemplate : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~ApplyTemplate() throw();

	/** Creates an instance. */
	static Statement* Create(const StringList& lstParamaters);

protected:
	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	ApplyTemplate(const StringList& lstParamaters);

	ThreadSpecific<Workers::Proc::WCM::WorkContextManager>::Pointer  pWorkContext;

	String strSpecs;

	friend class ::IAS::Factory<ApplyTemplate>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Std_ApplyTemplate_H_ */
