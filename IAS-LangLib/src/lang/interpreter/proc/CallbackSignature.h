/*
 * File: IAS-LangLib/src/lang/interpreter/proc/CallbackSignature.h
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
#ifndef _IAS_AS_Lang_Interpreter_Proc_CALLBACKSIGNATURE_H_
#define _IAS_AS_Lang_Interpreter_Proc_CALLBACKSIGNATURE_H_

#include <commonlib/commonlib.h>
#include "lang/model/Node.h"

#include <dm/datamodel.h>

#include "BlockChain.h"

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Exe{
namespace Dec  { class VariableDeclaration; };
namespace Dec  { class Parameters; };
namespace Stmt { class Statement; };
namespace Stmt { class LeftSide; };
namespace Stmt { class CatchList; };
namespace Stmt { class Catch; };

namespace Expr { class Expr; };
namespace Expr { namespace XPath { class XPathExprFamily; } };
namespace Expr { class ExprList; };
namespace Expr { class BooleanExpr; };
namespace Expr { namespace XPath { class XPathAccessor; } };
class Program;
}
namespace Proc {
class ExecStore;
/*************************************************************************/

/** The class. */
 class CallbackSignature {
public:

	virtual ~CallbackSignature(){};

	struct CallbackCtx{
		CallbackCtx(DM::DataFactory *pDataFactory,
					ExecStore* pExecStore);
		int iIndent;

		DM::DataFactory *getDataFactory() const;
		ExecStore        *getExecStore() const;
		BlockChain       *getBlockChain();

	protected:
		DM::DataFactory *pDataFactory;
		IAS_DFT_FACTORY<BlockChain>::PtrHolder ptrBlockChain;
		ExecStore*       pExecStore;
	};

	union Result{
		Exe::Dec::VariableDeclaration *pVariableDeclaration;
		Exe::Dec::Parameters          *pParameters;

		Exe::Stmt::Statement          *pStatement;
		Exe::Stmt::LeftSide           *pLeftSide;
		Exe::Stmt::Catch              *pCatch;
		Exe::Stmt::CatchList          *pCatchList;

		Exe::Expr::Expr               *pExpr;
		Exe::Expr::XPath::XPathExprFamily *pXPathExprFamily;
		Exe::Expr::ExprList           *pExprList;
		Exe::Expr::BooleanExpr        *pBooleanExpr;
		Exe::Expr::XPath::XPathAccessor  *pXPathAccessor;

		Exe::Program                  *pProgram;

	};

	virtual void call(const Model::Node* pNode,
						CallbackCtx *pCtx,
						Result& aResult)=0;

protected:

	void printIndent(CallbackCtx *pCtx,
				       CallbackSignature::Result& aResult);

	friend class ::IAS::Factory<CallbackSignature>;
};

/*************************************************************************/
}
}
}
}


#endif /* _IAS_AS_Lang_Interpreter_Proc_CALLBACKREGISTER_H_ */
