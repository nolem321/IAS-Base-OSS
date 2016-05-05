/*
 * File: IAS-LangLib/src/lang/interpreter/exe/Context.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_CONTEXT_H_
#define _IAS_AS_Lang_Interpreter_Exe_CONTEXT_H_

#include <dm/datamodel.h>
#include "expr/ExprResultSetter.h"
#include<vector>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {

/*************************************************************************/
/** The runtime context (mostly stack).
 *  The class encapsulates are runtime data need during the program
 *  execution. Thread context in the other words.
 */
 class Context {
public:

	virtual ~Context() throw();

	const DM::DataFactory* getDataFactory() const;

	void pushBlock(DM::DataObject *pVariables);
	void popBlock();

	DM::DataObject* getBlockVariables(int iOffset);

	void setInterrupted(bool bIsInterrupted) { this->bIsInterrupted=bIsInterrupted; }
	bool isInterrupted() const { return bIsInterrupted; };

	Expr::ExprResultSetter getResultSetter();

protected:

	Context();

	void setDataFactory(const DM::DataFactory *pDataFactory);

	const DM::DataFactory* pDataFactory;

	typedef std::vector<DM::DataObjectPtr> VariablesChain;
	VariablesChain                     	    lstVariablesChain;

	DM::DataObjectPtr ptrParameterValues;

	const DM::Property *pResultProperty;

	bool bIsInterrupted;

	DM::DataObjectPtr ptrException;

	friend class ::IAS::Factory<Context>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_CONTEXT_H_ */
