/*
 * File: IAS-LangLib/src/lang/export/text/expr/ExprNodeHandler.h
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
#ifndef _IAS_AS_Lang_Export_Text_Expr_EXPRNODEHANDLER_H_
#define _IAS_AS_Lang_Export_Text_Expr_EXPRNODEHANDLER_H_

#include <lang/export/text/CallbackSignature.h>

namespace IAS {
namespace Lang {

namespace Model {
namespace Expr {
class ExprNode;
}
}

namespace Export{
namespace Text {
namespace Expr {



/*************************************************************************/
/** The class. */
 class ExprNodeHandler :
 public ::IAS::Lang::Export::Text::CallbackSignature {
public:

	virtual ~ExprNodeHandler() throw();

	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult);
protected:
	ExprNodeHandler();

	virtual void handleUnary(const Model::Expr::ExprNode* pNode,
							   CallbackCtx *pCtx, CallbackSignature::Result& aResult,
							   const String& strText);


	virtual void handleBinary(const Model::Expr::ExprNode* pLeftNode,
							     const Model::Expr::ExprNode* pRightNode,
							     CallbackCtx *pCtx, CallbackSignature::Result& aResult,
								  const String& strText);


	friend class ::IAS::Factory<ExprNodeHandler>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_AS_Lang_Export_Text_Expr_EXPRNODEHANDLER_H_ */
