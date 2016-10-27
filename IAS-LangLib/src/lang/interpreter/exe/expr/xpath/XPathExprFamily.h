/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathExprFamily.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathExprFamily_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathExprFamily_H_

#include "../Expr.h"

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
class Expr;
class DataObjectExpr;
namespace XPath {
class XPathAccessor;

/*************************************************************************/
/** The class. */
 class XPathExprFamily : public virtual Expr {
public:

	 virtual ~XPathExprFamily() throw();

	 //TODO (M) ??? const DataObjectExpr XPathAccessor ?
	static XPathExprFamily* Create(Expr* pExpr, XPathAccessor  *pXPathAccessor);

	virtual bool isArray()const;

	ExprResultSetter getTargetObjectSetter(Context *pCtx) const;
	DM::DataObjectList& getTargetObjectList(Context *pCtx) const;


	bool isSet(Context* pCtx)const;
	bool isNull(Context* pCtx)const;
	void deleteDataObject(Context* pCtx)const;
	DM::DataObject* createDataObject(Context* pCtx)const;

protected:
	XPathExprFamily(Expr* pExpr, XPathAccessor  *pXPathAccessor);

	IAS_DFT_FACTORY<Expr>::PtrHolder           ptrExpr;
	IAS_DFT_FACTORY<XPathAccessor>::PtrHolder  ptrXPathAccessor;

	DM::DataObject* getTargetObject(Context *pCtx) const;

	friend class ::IAS::Factory<XPathExprFamily>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathExprFamily_H_ */
