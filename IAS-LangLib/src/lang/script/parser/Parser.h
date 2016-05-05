/*
 * File: IAS-LangLib/src/lang/script/parser/Parser.h
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
#ifndef _IAS_AS_Lang_Script_Parser_PARSER_H_
#define _IAS_AS_Lang_Script_Parser_PARSER_H_

#include <commonlib/commonlib.h>

#include "lang/model/Model.h"

namespace yy{
 class location;
}
namespace IAS {
namespace Lang {
namespace Script {
namespace Parser {

class Lexer;

/*************************************************************************/
/** The class. */
 class Parser {
public:

	virtual ~Parser() throw();

	void onAutoGenParserError(const yy::location& l, const std::string& strInfo);

	void open(const String& strObjectName);

	//Model::SourceLocation getLocation()const;

	void addProgram(Lang::Model::ProgramNode* pProgram);
	void addTypeDefinition(Lang::Model::Dec::TypeDefinitionNode* pTypeDefinition);

	void parse(Lexer *pLexer);
	Lexer* getLexer();

	typedef std::list<Lang::Model::ProgramNode*> ProgramList;

	const ProgramList& getRecentlyParsed()const;

	Lang::Model::ProgramNode* getLastProgram()const;

protected:
	Parser(Model::Model *pModel);
	Model::Model *getModel() const;

private:
	Model::Model *pModel;
	Lexer *pLexer;

	ProgramList lstPrograms;
	friend class ::IAS::Factory<Parser>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Script_Parser_PARSER_H_ */
