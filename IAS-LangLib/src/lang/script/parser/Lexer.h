/*
 * File: IAS-LangLib/src/lang/script/parser/Lexer.h
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
#ifndef _IAS_AS_Lang_Script_Parser_LEXER_H_
#define _IAS_AS_Lang_Script_Parser_LEXER_H_

#include <commonlib/commonlib.h>
#include "../../script/parser/AutoGenParser.hpp"
#include "lang/tools/parser/LexerBase.h"
#include "lang/exception/ParseErrorException.h"


namespace IAS {
namespace Lang {

namespace Script {
namespace Parser {

/*************************************************************************/
/** The class. */
 class Lexer : public ::IAS::Lang::Tools::Parser::LexerBase{
public:

	virtual ~Lexer() throw();

	typedef ::yy::AutoGenParser::token_type TokenType;
	typedef ::yy::AutoGenParser::token Token;

	typedef LexerBase::TokenInfo<TokenType> TokenInfo;

	const TokenInfo& nextToken() throw(ParseErrorException);

	const ::IAS::Lang::Tools::Parser::LexerLocation* getLocation();

protected:
	Lexer(::IAS::Lang::Tools::Parser::LexerIStreamFactory* pLexerIStreamFactory,
	      ::IAS::Lang::Tools::Parser::ISourceLocationStore *pSourceLocationStore);

	enum States{

		S_Start,
		S_End,

		S_String,
		S_StringEsc,
		S_Integer,
		S_Float,
		S_Symbol,
		S_Greater,
		S_Less,
		S_Eq,
		S_Colon,
		S_SpecSymbol,
		S_QuestionMark,

		S_Slash,
		S_BlockComment,
		S_LineComment
	};

	void handleStep();

	void handleState_Start(unsigned char c);
	void handleState_String(unsigned char c);
	void handleState_StringEsc(unsigned char c);
	void handleState_Symbol(unsigned char c);
	void handleState_SpecSymbol(unsigned char c);
	void handleState_Integer(unsigned char c);
	void handleState_Float(unsigned char c);
	void handleState_Greater(unsigned char c);
	void handleState_Less(unsigned char c);
	void handleState_Eq(unsigned char c);
	void handleState_Colon(unsigned char c);
	void handleState_QuestionMark(unsigned char c);
	void handleState_Slash(unsigned char c);
	void handleState_BlockComment(unsigned char c);
	void handleState_LineComment(unsigned char c);

private:

	void init();

	TokenInfo aTokenInfo;
	States    iCurrentState;

	typedef  std::map<String, TokenType> KeywordsMap;

	KeywordsMap hmKeywords;
	KeywordsMap hmConstants;

	int     iEscCharValue;
	int     iEscCharLen;

	friend class ::IAS::Factory<Lexer>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Script_Parser_LEXER_H_ */
