/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/RelationalEqNodeHandler.h
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
#ifndef _IAS_AS_Lang_Interpreter_Proc_Expr_RelationalEqNodeHandler_H_
#define _IAS_AS_Lang_Interpreter_Proc_Expr_RelationalEqNodeHandler_H_

#include "RelationalBinaryOperNodeHandler.h"

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
/** The class. */
 class RelationalEqNodeHandler : public RelationalBinaryOperNodeHandler {
public:

	virtual ~RelationalEqNodeHandler() throw();

	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult);

protected:
	RelationalEqNodeHandler();

	friend class ::IAS::Factory<RelationalEqNodeHandler>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Proc_Expr_RelationalEqNODEHANDLER_H_ */
