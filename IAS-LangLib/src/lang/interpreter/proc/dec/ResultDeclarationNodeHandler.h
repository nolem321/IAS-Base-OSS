/*
 * File: IAS-LangLib/src/lang/interpreter/proc/dec/ResultDeclarationNodeHandler.h
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
#ifndef _IAS_AS_Lang_Interpreter_Proc_Dec_ResultDeclarationNodeHandler_H_
#define _IAS_AS_Lang_Interpreter_Proc_Dec_ResultDeclarationNodeHandler_H_

#include "DeclarationNodeHandler.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {
namespace Dec {

/*************************************************************************/
/** The class. */
 class ResultDeclarationNodeHandler :  public DeclarationNodeHandler {
public:

	virtual ~ResultDeclarationNodeHandler() throw();

	virtual void call(const Model::Node* pNode,
						CallbackCtx *pCtx,
						CallbackSignature::Result& aResult);
protected:
	ResultDeclarationNodeHandler();

	friend class ::IAS::Factory<ResultDeclarationNodeHandler>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Proc_Stmt_FORLOOPNODEHANDLER_H_ */
