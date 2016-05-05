/*
 * File: IAS-LangLib/src/lang/interpreter/text/expr/xpath/XPathExprAccessNodeHandler.h
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
#ifndef _IAS_AS_Lang_Export_Text_Expr_XPathExprAccessNodeHandler_H_
#define _IAS_AS_Lang_Export_Text_Expr_XPathExprAccessNodeHandler_H_

#include <lang/export/text/CallbackSignature.h>

namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
namespace Expr {
namespace XPath {

/*************************************************************************/
/** The class. */
 class XPathExprAccessNodeHandler :
 public ::IAS::Lang::Export::Text::CallbackSignature {
public:

	virtual ~XPathExprAccessNodeHandler() throw();

	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult);
protected:
	XPathExprAccessNodeHandler();

	friend class ::IAS::Factory<XPathExprAccessNodeHandler>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_AS_Lang_Export_Text_Expr_VARIABLENODEHANDLER_H_ */
