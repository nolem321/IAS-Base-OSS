/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/With.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_With_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_With_H_

#include "Statement.h"

#include "../dec/DeclarationBlockFeature.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;


namespace Expr{
namespace XPath{
class XPathExprFamily;
}
}
namespace Stmt {
class Statement;
class LeftSide;

/*************************************************************************/
/** The class. */
 class With : public Statement ,
 	 	 	 public  Exe::Dec::DeclarationBlockFeature {
public:

	virtual ~With() throw();

	void setStatement(Statement* pStatement);
	virtual void declareBlockVariables(DM::DataFactory *pDataFactory);

protected:
	With(Expr::XPath::XPathExprFamily      *pExpr);
	With(const String& strVarName,Expr::XPath::XPathExprFamily *pExpr);

	IAS_DFT_FACTORY<Expr::XPath::XPathExprFamily>::PtrHolder ptrExpr;
	IAS_DFT_FACTORY<Statement>::PtrHolder  ptrStatement;

	bool bDeclareBlockVariables;

	const DM::Property *pVariableProperty;

	void execute(Context *pCtx, DM::DataObjectPtr dmValue) const;

};

 /*************************************************************************/
 class WithNonArray : public With {
   public:
 	 virtual void execute(Context *pCtx) const;
 	virtual ~WithNonArray() throw();
   protected:
 	WithNonArray(Expr::XPath::XPathExprFamily      *pExpr);
 	WithNonArray(const String& strVarName, Expr::XPath::XPathExprFamily *pExpr);

	friend class ::IAS::Factory<WithNonArray>;
 };
/*************************************************************************/
class WithArray : public With {
  public:
	 virtual void execute(Context *pCtx) const;
	 virtual ~WithArray() throw();
  protected:
	 WithArray(Expr::XPath::XPathExprFamily      *pExpr);
	 WithArray(const String& strVarName, Expr::XPath::XPathExprFamily *pExpr);
	friend class ::IAS::Factory<WithArray>;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_ASSIGNMENT_H_ */
