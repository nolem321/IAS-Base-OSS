/*
 * File: IAS-LangLib/src/lang/interpreter/exe/Program.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Program_H_
#define _IAS_AS_Lang_Interpreter_Exe_Program_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Exe {
namespace Stmt{
class Statement;
}
namespace Dec{
class Parameters;
}

class Context;
/*************************************************************************/
/** The class. */
 class Program {
public:

	virtual ~Program() throw();

	void execute(Context* pCtx);

	DM::DataObject* createParameters();

	const Dec::Parameters* getParameters()const { return ptrParameters; };

	void setStatement(Stmt::Statement* pMainStmtBlock);

	bool isReturningResult()const {return bIsReturningResult; } ;

	const String& getName()const { return strName; };
	const String& getSourceName()const { return strSourceName; };

	void setSourceAndName(const String& strName, const String& strSourceName);

protected:
	Program(Dec::Parameters *pParameters, bool bIsReturningResult);

	IAS_DFT_FACTORY< Dec::Parameters >::PtrHolder ptrParameters;
	IAS_DFT_FACTORY< Stmt::Statement >::PtrHolder ptrMainStmtBlock;

	bool bIsReturningResult;

	String strName;
	String strSourceName;

	friend class ::IAS::Factory<Program>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Program_H_ */
