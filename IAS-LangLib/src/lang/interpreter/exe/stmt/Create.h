/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Create.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Stmt_Create_H_
#define _IAS_Lang_Interpreter_Exe_Stmt_Create_H_

#include "Statement.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr{
namespace XPath{
class XPathExprFamily;
}
}
class Context;
namespace Stmt {

/*************************************************************************/
/** The Create class.
 *
 */
class Create : public Statement{
public:

	virtual ~Create() throw();

	virtual void execute(Exe::Context *pCtx)const;

protected:
	Create(Expr::XPath::XPathExprFamily   *pXPathExprFamily);

	IAS_DFT_FACTORY<Expr::XPath::XPathExprFamily>::PtrHolder   ptrXPathExprFamily;

	friend class ::IAS::Factory<Create>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Stmt_Create_H_ */
