/*
 * File: IAS-LangLib/src/lang/printer/expr/ExprListNodeHandler.h
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
#ifndef _IAS_AS_Lang_Printer_Expr_ExprListNodeHandler_H_
#define _IAS_AS_Lang_Printer_Expr_ExprListNodeHandler_H_

#include <lang/printer/CallbackSignature.h>

namespace IAS {
namespace Lang {

namespace Model {
namespace Expr {
class ExprNode;
}
}

namespace Printer {
namespace Expr {



/*************************************************************************/
/** The class. */
 class ExprListNodeHandler :
 public ::IAS::Lang::Printer::CallbackSignature {
public:

	virtual ~ExprListNodeHandler() throw();


	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os);
protected:
	ExprListNodeHandler();
	

	friend class ::IAS::Factory<ExprListNodeHandler>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Printer_Expr_EXPRNODEHANDLER_H_ */
