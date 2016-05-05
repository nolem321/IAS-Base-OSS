/*
 * File: IAS-LangLib-TestCases/src/testcases/TCTypePrinting.h
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
#ifndef _IAS_TCT_TCTypePrinting_H
#define _IAS_TCT_TCTypePrinting_H


#include "commonlib/testcase/TestUnit.h"

#include <lang/model/Model.h>
#include <lang/script/parser/Lexer.h>
#include <lang/script/parser/Parser.h>

namespace IAS{
namespace TCT{

class TCTypePrinting: public TestUnit{

public:

	virtual ~TCTypePrinting()  throw ();

protected:
	TCTypePrinting(TestSuite* pTestSuite,
				   const String& strObjectName,
				   const String& strTypeName,
				   const String& strTypeURIName);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<TCTypePrinting> theTestRunner;

	void caseOne();

	String strProgramName;
	String strTypeName;
	String strTypeURIName;

	friend class ::IAS::Factory<TCTypePrinting>;

	IAS_DFT_FACTORY< ::IAS::Lang::Script::Parser::Lexer>::PtrHolder ptrLexer;
	IAS_DFT_FACTORY< ::IAS::Lang::Model::Model>::PtrHolder ptrModel;

	String getOutputFileName()const;

private:
	String getOutputFileName();

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
