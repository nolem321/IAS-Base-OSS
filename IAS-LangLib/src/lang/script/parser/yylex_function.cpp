/*
 * File: IAS-LangLib/src/lang/script/parser/yylex_function.cpp
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
#include "../../script/parser/yylex_function.h"

#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../../script/parser/location.hh"
#include "../../script/parser/Lexer.h"
#include "../../script/parser/Parser.h"

#include "lang/tools/parser/LexerIStreamWrapper.h"

using namespace IAS;
using namespace Lang;
using namespace Script;
using namespace Parser;

 yy::AutoGenParser::token_type
  yylex (yy::AutoGenParser::semantic_type* yylval,
         yy::AutoGenParser::location_type* yylloc,
         IAS::Lang::Script::Parser::Parser& myParser){

	IAS_TRACER;

	const Lexer::TokenInfo& anInfo = myParser.getLexer()->nextToken();

	yy::AutoGenParser::token_type iToken=anInfo.getToken();
	if(anInfo.hasInfo()){

		//TODO (M) yylval->sval = IAS_DFT_FACTORY<String>::Create(anInfo.getInfo()); ?? static ??
		 yylval->sval = new String(anInfo.getInfo());
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),(void*)(yylval->sval)<<"="<<anInfo.getInfo());
	}else{
		yylval->sval=NULL;
	}

	return iToken;
}
