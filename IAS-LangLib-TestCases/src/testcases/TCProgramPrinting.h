/*
 * File: IAS-LangLib-TestCases/src/testcases/TCProgramPrinting.h
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
#ifndef _IAS_TCT_TCProgramPrinting_H
#define _IAS_TCT_TCProgramPrinting_H


#include "commonlib/testcase/TestUnit.h"

#include <lang/model/Model.h>

#include "../../../IAS-LangLib/src/lang/script/parser/Lexer.h"

namespace IAS{
namespace TCT{

class TCProgramPrinting: public TestUnit{

public:

	virtual ~TCProgramPrinting()  throw ();

protected:
	TCProgramPrinting(TestSuite* pTestSuite,
					   const String& strProgramName);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<TCProgramPrinting> theTestRunner;

	void caseOne();

	String strProgramName;

	friend class ::IAS::Factory<TCProgramPrinting>;

	IAS_DFT_FACTORY< ::IAS::Lang::Script::Parser::Lexer>::PtrHolder ptrLexer;
	IAS_DFT_FACTORY< ::IAS::Lang::Model::Model>::PtrHolder ptrModel;

	String getOutputFileName()const;

private:
	String getOutputFileName();

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
