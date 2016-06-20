/*
 * File: IAS-LangLib/src/lang/interpreter/ProgramLoader.h
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
#ifndef _IAS_Lang_Interpreter_ProgramLoader_H_
#define _IAS_Lang_Interpreter_ProgramLoader_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "TypeList.h"

#include <lang/export/text/SourceStore.h>


namespace IAS {
namespace Lang {

namespace Tools {
namespace Parser{
class LexerIStreamFactory;
class LexerIStreamWrapper;
}
}

namespace Script {
namespace Parser {
class Lexer;
class Parser;
}
}

namespace Model {
class Model;
}

namespace Interpreter {
namespace Exe{
class Program;
}
namespace Proc{
class ExecStore;
}
/*************************************************************************/
/** The ProgramLoader class.
 *
 */
class ProgramLoader {
public:

	virtual ~ProgramLoader() throw();

	void loadModel(const String& strObject, Tools::Parser::LexerIStreamWrapper* pWrapper = NULL);

	const ::IAS::Lang::Interpreter::Exe::Program* getExecutable(const String& strProgramName);

	void findAllMatches(const TypeList& lstTypes, ProgramList& lstOutput);

	::IAS::Lang::Export::Text::SourceStore* getSourceStore();

	const ::IAS::Lang::Model::Model* getModel()const;

protected:
	ProgramLoader(::IAS::DM::DataFactory  *pDataFactory,
			      Tools::Parser::LexerIStreamFactory* pLexerIStreamFactory = NULL);

	::IAS::DM::DataFactory  *pDataFactory;

	String createProgramFileName(const String& strName) const;

	IAS_DFT_FACTORY<Script::Parser::Lexer>::PtrHolder ptrLexer;

	IAS_DFT_FACTORY< ::IAS::Lang::Model::Model>::PtrHolder ptrModel;
	IAS_DFT_FACTORY< ::IAS::Lang::Interpreter::Proc::ExecStore>::PtrHolder ptrExecStore;

	IAS_DFT_FACTORY< ::IAS::Lang::Export::Text::SourceStore>::PtrHolder ptrSourceStore;

	static const char    CFilePathDelimiter;
	static const String& CStrFileSufix;
	static const char    CProgramNameDelimiter;

	StringList lstSourceDirs;

	friend class ::IAS::Factory<ProgramLoader>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Lang_Interpreter_ProgramLoader_H_ */
