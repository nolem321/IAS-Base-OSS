/*
 * File: IAS-LangLib/src/lang/export/text/expr/RelationalBinaryOperNodeHandler.h
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
#ifndef _IAS_AS_Lang_Export_Text_Expr_RelationalBinaryOPERNODEHANDLER_H_
#define _IAS_AS_Lang_Export_Text_Expr_RelationalBinaryOPERNODEHANDLER_H_

#include "LogicalExprNodeHandler.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
class RelationalBinaryOperNode;
}
}
namespace Export{
namespace Text {
namespace Expr {

/*************************************************************************/
/** The class. */
 class RelationalBinaryOperNodeHandler : public LogicalExprNodeHandler{
public:

	virtual ~RelationalBinaryOperNodeHandler() throw();

	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult);

protected:
	RelationalBinaryOperNodeHandler();

	friend class ::IAS::Factory<RelationalBinaryOperNodeHandler>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_AS_Lang_Export_Text_Expr_RelationalBinaryOPERNODEHANDLER_H_ */
