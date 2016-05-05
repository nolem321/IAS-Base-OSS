/*
 * File: IAS-LangLib/src/lang/interpreter/proc/CallbackRegister.h
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
#ifndef _IAS_AS_Lang_Interpreter_Proc_CALLBACKREGISTER_H_
#define _IAS_AS_Lang_Interpreter_Proc_CALLBACKREGISTER_H_

#include <commonlib/commonlib.h>
#include "lang/model/Node.h"
#include "CallbackSignature.h"

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
class ExecStore;
/*************************************************************************/
/** The class. */
 class CallbackRegister :
	public ::IAS::CallbackRegister< const Model::Node, CallbackSignature >,
	public ::IAS::InstanceFeature< Interpreter::Proc::CallbackRegister >{

public:

	virtual ~CallbackRegister() throw();

	static void Call(const Model::Node* pNode,
			           ExecStore*       pExecStore,
					   DM::DataFactory *pDataFactory,
					   CallbackSignature::Result&      aResult);

	static void SubCall(const Model::Node* pNode,
						  CallbackSignature::CallbackCtx* pCtx,
						  CallbackSignature::Result&      aResult);
protected:

	CallbackRegister();
	void init();

	friend class ::IAS::Factory<CallbackRegister>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Proc_CALLBACKREGISTER_H_ */
