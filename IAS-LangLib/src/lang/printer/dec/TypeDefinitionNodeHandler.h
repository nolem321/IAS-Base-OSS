/*
 * File: IAS-LangLib/src/lang/printer/dec/TypeDefinitionNodeHandler.h
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
#ifndef _IAS_AS_Lang_Printer_Dec_TypeDefinitionNodeHandlerr_H_
#define _IAS_AS_Lang_Printer_Dec_TypeDefinitionNodeHandlerr_H_

#include <lang/printer/CallbackSignature.h>

namespace IAS {
namespace Lang {
namespace Printer {
namespace Dec {

/*************************************************************************/
/** The class. */
 class TypeDefinitionNodeHandler :  public ::IAS::Lang::Printer::CallbackSignature {
public:

	virtual ~TypeDefinitionNodeHandler() throw();

	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os);
protected:
	TypeDefinitionNodeHandler();

	friend class ::IAS::Factory<TypeDefinitionNodeHandler>;
};

/*************************************************************************/
}
}
}
}


#endif /* _IAS_AS_Lang_Interpreter_Proc_Stmt_FORLOOPNODEHANDLER_H_ */
