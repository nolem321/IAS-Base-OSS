/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Catch.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Stmt_Catch_H_
#define _IAS_Lang_Interpreter_Exe_Stmt_Catch_H_

#include "../dec/DeclarationBlockFeature.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {
class Statement;

/*************************************************************************/
/** The Catch class.
 *
 */
class Catch:
	public ::IAS::Lang::Interpreter::Exe::Dec::DeclarationBlockFeature {
public:

	virtual ~Catch() throw();

	void setCatchVariable(Exe::Dec::VariableDeclaration* pVariableDeclaration);
	void setCatchStatement(Statement *pStatement);

	virtual void execute(Context *pCtx, const DM::DataObjectPtr& ptrException) const;

	const DM::Type* getCatchType()const;

	virtual void declareBlockVariables(DM::DataFactory *pDataFactory);

protected:
	Catch()throw();

	IAS_DFT_FACTORY<Statement>::PtrHolder ptrStatement;
	const DM::Type*     pCatchType;
	const DM::Property *pCatchVariableProperty;
	friend class ::IAS::Factory<Catch>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Stmt_Catch_H_ */
