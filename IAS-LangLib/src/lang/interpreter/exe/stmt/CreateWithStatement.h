/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/CreateWithStatement.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Stmt_CreateWithStatement_H_
#define _IAS_Lang_Interpreter_Exe_Stmt_CreateWithStatement_H_

#include "Create.h"
#include <lang/interpreter/exe/dec/DeclarationBlockFeature.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {
/*************************************************************************/
/** The CreateWithStatement class.
 *
 */
class CreateWithStatement : public Create ,
							public Exe::Dec::DeclarationBlockFeature {
public:

	virtual ~CreateWithStatement() throw();

	virtual void execute(Exe::Context *pCtx)const;

	void setStatement(Statement* pStatement);

protected:
	CreateWithStatement(Expr::XPath::XPathExprFamily   *pXPathExprFamily);

	IAS_DFT_FACTORY<Statement>::PtrHolder  ptrStatement;

	friend class ::IAS::Factory<CreateWithStatement>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Stmt_CreateWithStatement_H_ */
