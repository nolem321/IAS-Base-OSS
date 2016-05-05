/*
 * File: IAS-LangLib/src/lang/interpreter/proc/dec/DeclarationNodeHandler.h
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
#ifndef _IAS_AS_Lang_Interpreter_Proc_Dec_DeclarationNodeHandler_H_
#define _IAS_AS_Lang_Interpreter_Proc_Dec_DeclarationNodeHandler_H_

#include <lang/interpreter/proc/CallbackSignature.h>

namespace IAS {
namespace Lang {

namespace Model {
namespace Dec{
class DeclarationNode;
}
}

namespace Interpreter {
namespace Proc {
namespace Dec {

/*************************************************************************/
/** The class. */
 class DeclarationNodeHandler :  public ::IAS::Lang::Interpreter::Proc::CallbackSignature {
public:

	virtual ~DeclarationNodeHandler() throw();

	virtual void call(const Model::Node* pNode,
						CallbackCtx *pCtx,
						CallbackSignature::Result& aResult);
protected:
	DeclarationNodeHandler();

	void handle(const Model::Dec::DeclarationNode* pDeclarationNode,
				 CallbackCtx *pCtx,
				 CallbackSignature::Result& aResult);

	friend class ::IAS::Factory<DeclarationNodeHandler>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Proc_Stmt_FORLOOPNODEHANDLER_H_ */
