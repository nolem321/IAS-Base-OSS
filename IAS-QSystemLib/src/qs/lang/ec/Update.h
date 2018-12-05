/*
 * File: IAS-QSystemLib/src/qs/lang/ec/Update.h
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
#ifndef _IAS_QS_Lang_EC_Update_H_
#define _IAS_QS_Lang_EC_Update_H_

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/ec/EventCounter.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace EC {

/*************************************************************************/
/** The Update class.
 *
 */
class Update : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~Update() throw();

	/** Creates an instance. */
	static Statement* Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);



protected:
	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	Update(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

	Workers::Proc::EC::EventCounter* pEventCounter;
	String strEventCounterName;

	ThreadSpecific<Workers::Proc::WCM::WorkContextManager>::Pointer  pWorkContext;

	friend class ::IAS::Factory<Update>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Std_Update_H_ */
