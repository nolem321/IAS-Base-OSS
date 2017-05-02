/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Sort.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_Sort_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_Sort_H_

#include "Statement.h"

#include "../dec/DeclarationBlockFeature.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
class Program;
class ProgramContext;

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
 class Sort : public Statement {
public:

	virtual ~Sort() throw();

	virtual void execute(Exe::Context *pCtx)const;

protected:
	Sort(Expr::XPath::XPathExprFamily  *pListExpr,
		 Program* pProgram);

	IAS_DFT_FACTORY<Expr::XPath::XPathExprFamily>::PtrHolder ptrListExpr;

	Program* pProgram;

	class CallHelper {
		public:
			CallHelper(DM::DataObjectList& lstArray, const Program* pProgram, Exe::Context *pCtx);


		void sort();

	protected:

		DM::DataObject* pParameters;

		const DM::Property* pPropertyLeft;
		const DM::Property* pPropertyRight;
		Exe::Context *pCtx;

		DM::DataObjectList& lstArray;

		void swap(int iLeftIdx, int iRightIdx);
		int  partition(int iLeftIdx, int iRightIdx);
		void sort(int iLeftIdx, int iRightIdx);
		bool cmp(DM::DataObject* pLeft, DM::DataObject* pRight);

		IAS_DFT_FACTORY<ProgramContext>::PtrHolder ptrContext;
	};

	friend class ::IAS::Factory<Sort>;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_ASSIGNMENT_H_ */
