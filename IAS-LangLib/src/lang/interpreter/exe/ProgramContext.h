/*
 * File: IAS-LangLib/src/lang/interpreter/exe/ProgramContext.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_ProgramContext_H_
#define _IAS_AS_Lang_Interpreter_Exe_ProgramContext_H_

#include <commonlib/commonlib.h>

#include "Context.h"
#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {

class Program;

/*************************************************************************/
/** The runtime context for a program.
 *  The class extends the regular context providing call parameters.
 */
 class ProgramContext : protected Context {
public:

	virtual ~ProgramContext() throw();

	void execute(Exe::Context *pCtx = NULL);

	DM::DataObject* getResult() const;
	DM::DataObjectList& getResultAsList() const;

	DM::DataObject* getParameters();

	bool hasResult()const;

protected:
	ProgramContext(const DM::DataFactory *pDataFactory, const Program* pProgram);

	void init(const Program *pProgram);

	const Program *pProgram;

	friend class ::IAS::Factory<ProgramContext>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_CONTEXT_H_ */
