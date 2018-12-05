/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ti/ServiceManagerAction.h
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/SMCENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _IAS_QS_Lang_SM_ServiceManagerAction_H_
#define _IAS_QS_Lang_SM_ServiceManagerAction_H_

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>

namespace IAS {

namespace SM {
  namespace API{
    class ServiceManager;
    class ActionDispatcher;
  }
}


namespace QS {
namespace Lang {
namespace SM {
/*************************************************************************/
/** The ServiceManagerAction class.
 *
 */
class ServiceManagerAction : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~ServiceManagerAction() throw();

	/** Creates an instance. */
	static Statement* Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

protected:

	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	ServiceManagerAction(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);


	IAS_DFT_FACTORY< ::IAS::SM::API::ServiceManager>::PtrHolder   ptrServiceManager;
	IAS_DFT_FACTORY< ::IAS::SM::API::ActionDispatcher>::PtrHolder ptrActionDispatcher;


	friend class ::IAS::Factory<ServiceManagerAction>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Std_ServiceManagerAction_H_ */
