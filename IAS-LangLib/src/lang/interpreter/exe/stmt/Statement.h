/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Statement.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENT_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENT_H_

#include <commonlib/commonlib.h>
#include "../Context.h"


namespace IAS {
namespace Lang {

namespace Model{
namespace Stmt{
class StatementNode;
}
}

namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
/** The base runtime statement interface.
 */
 class Statement {
public:

	virtual ~Statement() throw();

	virtual void execute(Context *pCtx) const = 0;

	void setSourceLine(unsigned short iLine);
	unsigned short getSourceLine()const;

	void setSource(const String& strSourceText){ this->strSourceText=strSourceText;};
	const String& getSource()const{ return strSourceText;};

protected:

	Statement()throw();
	unsigned short iLine;

	String strSourceText;

	friend class ::IAS::Factory<Statement>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENT_H_ */
