/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/CopyOf.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_CopyOf_H_
#define _IAS_Lang_Interpreter_Exe_Expr_CopyOf_H_


#include "DataObjectExpr.h"
#include "ExprResultSetter.h"
#include "xpath/XPathExprFamily.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr{
namespace XPath{
class XPathExprFamily;
}

/*************************************************************************/
/** The CopyOf class.
 *
 */
class CopyOf : public DataObjectExpr {
public:

	virtual ~CopyOf() throw();

	class ExprResultSetter : public IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter{
	public:

		ExprResultSetter(const IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter& other);

		virtual void assign(DM::DataObject* dmValue);
		virtual void assignList(DM::DataObjectList& refList);
	};

	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const;
	virtual void evaluate(Context *pCtx, IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter& refResult) const;

protected:

	CopyOf(XPath::XPathExprFamily   *pXPathExprFamily);
	IAS_DFT_FACTORY<XPath::XPathExprFamily>::PtrHolder   ptrXPathExprFamily;

	friend class ::IAS::Factory<CopyOf>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Stmt_CopyOf_H_ */
