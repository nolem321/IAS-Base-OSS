/*
 * File: IAS-LangLib/src/lang/script/parser/Lexer.cpp
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
#include "../../script/parser/Lexer.h"

#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "lang/tools/parser/LexerIStreamWrapper.h"

using namespace yy;

namespace IAS {
namespace Lang {
namespace Script {
namespace Parser {

/*************************************************************************/
Lexer::Lexer(Tools::Parser::LexerIStreamFactory* pLexerIStreamFactory,
		     Tools::Parser::ISourceLocationStore *pSourceLocationStore):
		LexerBase(pLexerIStreamFactory, pSourceLocationStore){
	IAS_TRACER;

	init();
}
/*************************************************************************/
Lexer::~Lexer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const ::IAS::Lang::Tools::Parser::LexerLocation* Lexer::getLocation(){
	IAS_TRACER;
	return getActiveWrapper();
}
/*************************************************************************/
void Lexer::init(){

	IAS_TRACER;
	hmKeywords["PROGRAM"]=Token::T_PROGRAM;
	hmKeywords["IMPORT"]=Token::T_IMPORT;
	hmKeywords["BEGIN"]=Token::T_BEGIN;
	hmKeywords["END"]=Token::T_END;

	hmKeywords["CALL"]=Token::T_CALL;

	hmKeywords["FOR"]=Token::T_FOR;
	hmKeywords["TO"]=Token::T_TO;
	hmKeywords["STEP"]=Token::T_STEP;

	hmKeywords["WHILE"]=Token::T_WHILE;
	hmKeywords["DO"]=Token::T_DO;

	hmKeywords["WITH"]=Token::T_WITH;

	hmKeywords["AS"]=Token::T_AS;
	hmKeywords["OF"]=Token::T_OF;
	hmKeywords["ARRAY"]=Token::T_ARRAY;
	hmKeywords["RETURNS"]=Token::T_RETURNS;
	hmKeywords["VAR"]=Token::T_VAR;

	hmKeywords["IF"]=Token::T_IF;
	hmKeywords["THEN"]=Token::T_THEN;
	hmKeywords["ELSE"]=Token::T_ELSE;

	hmKeywords["AND"]=Token::T_AND;
	hmKeywords["OR"]=Token::T_OR;
	hmKeywords["NOT"]=Token::T_NOT;

	hmKeywords["NEW"]=Token::T_NEW;
	hmKeywords["COPYOF"]=Token::T_COPYOF;
	hmKeywords["DETACH"]=Token::T_DETACH;
	hmKeywords["SIZEOF"]=Token::T_SIZEOF;
	hmKeywords["DELETE"]=Token::T_DELETE;
	hmKeywords["TYPE"]=Token::T_TYPE;
	hmKeywords["TYPENS"]=Token::T_TYPENS;

	hmKeywords["ISSET"]=Token::T_ISSET;
	hmKeywords["ISNULL"]=Token::T_ISNULL;
	hmKeywords["ISTYPE"]=Token::T_ISTYPE;
	hmKeywords["ISINSTANCE"]=Token::T_ISINSTANCE;

	hmKeywords["STRLEN"]=Token::T_STRLEN;

	hmKeywords["EXTERNAL"]=Token::T_EXTERNAL;

	hmKeywords["RETURN"]=Token::T_RETURN;

	hmKeywords["TRY"]=Token::T_TRY;
	hmKeywords["CATCH"]=Token::T_CATCH;
	hmKeywords["THROW"]=Token::T_THROW;

	hmKeywords["DEFINE"]=Token::T_DEFINE;
	hmKeywords["EXTENSION"]=Token::T_EXTENSION;

	hmKeywords["TRUE"]=Token::T_BOOLEAN;
	hmKeywords["FALSE"]=Token::T_BOOLEAN;

	hmKeywords["NULL"]=Token::T_NULL;

}

/*************************************************************************/
const Lexer::TokenInfo& Lexer::nextToken() throw(ParseErrorException){
	IAS_TRACER;

	iCurrentState=S_Start;
	aTokenInfo.setToken(Token::T_NONE);
	aTokenInfo.clearInfo();

	while(iCurrentState != S_End)
		handleStep();

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"Token:"<<aTokenInfo.getToken());
	return aTokenInfo;

}
/*************************************************************************/
void Lexer::handleStep(){
	IAS_TRACER;

	unsigned char c = getActiveWrapper()->getChar();

	if(getActiveWrapper()->isEOF()){

		if(iCurrentState==S_BlockComment)
			IAS_THROW(ParseErrorException("Block comment was not closed",getActiveWrapper()));

		if(iCurrentState==S_LineComment)
			iCurrentState=S_Start;

		if(iCurrentState==S_Start){

			while(getActiveWrapper()->isEOF() && getStackSize() > 1)
				popIStreamWrapper();

			if(getActiveWrapper()->isEOF()){
				iCurrentState=S_End;
				aTokenInfo.setToken(Token::T_EOF);
				return;
			}else
				c = getActiveWrapper()->getChar();
		}else{
			c=0;
		}
	}

	//TODO (M) map char -> function
	switch(iCurrentState){

		case S_Start:      handleState_Start(c); break;
		case S_String:     handleState_String(c); break;
		case S_StringEsc:  handleState_StringEsc(c); break;

		case S_Symbol:     handleState_Symbol(c); break;
		case S_SpecSymbol: handleState_SpecSymbol(c); break;
		case S_Integer:    handleState_Integer(c); break;
		case S_Float:      handleState_Float(c); break;
		case S_Greater:    handleState_Greater(c); break;
		case S_Less:       handleState_Less(c); break;
		case S_Eq:         handleState_Eq(c); break;
		case S_Colon:      handleState_Colon(c); break;
		case S_Slash:      handleState_Slash(c); break;

		case S_LineComment:    handleState_LineComment(c); break;
		case S_BlockComment:   handleState_BlockComment(c); break;

		default:
			IAS_THROW(InternalException(String("CurrentState not handled: ")+TypeTools::IntToString(iCurrentState)));
	}
}
/*************************************************************************/
void Lexer::handleState_Start(unsigned char c){
	IAS_TRACER;

	if(isspace(c))
		return;

	//TODO (M) map char -> function - or struct ( token, state)
	switch(c){
		case '(': aTokenInfo.setToken(Token::T_OPEN_PAR); iCurrentState=S_End; return;
		case ')': aTokenInfo.setToken(Token::T_CLOSE_PAR); iCurrentState=S_End; return;

		case '[': aTokenInfo.setToken(Token::T_OPEN_SQUARE); iCurrentState=S_End; return;
		case ']': aTokenInfo.setToken(Token::T_CLOSE_SQUARE); iCurrentState=S_End; return;

		case '+': aTokenInfo.setToken(Token::T_PLUS); iCurrentState=S_End; return;
		case '-': aTokenInfo.setToken(Token::T_MINUS); iCurrentState=S_End; return;

		case '*': aTokenInfo.setToken(Token::T_ASTERISK); iCurrentState=S_End; return;
		case '%': aTokenInfo.setToken(Token::T_PERCENT); iCurrentState=S_End; return;

		case ',': aTokenInfo.setToken(Token::T_COMMA); iCurrentState=S_End; return;
		case '.': aTokenInfo.setToken(Token::T_DOT); iCurrentState=S_End; return;
		case ';': aTokenInfo.setToken(Token::T_SEMICOLON); iCurrentState=S_End; return;

		case '/': iCurrentState=S_Slash; return;
		case ':': iCurrentState=S_Colon; return;
		case '=': iCurrentState=S_Eq; return;
		case '<': iCurrentState=S_Less; return;
		case '>': iCurrentState=S_Greater; return;
		case '"': iCurrentState=S_String; return;
		case '{': iCurrentState=S_SpecSymbol; return;
	}

	if(isdigit(c)){
		aTokenInfo.addChar(c);
		iCurrentState=S_Integer;
		return;
	}

	if(isalnum(c) || c == '_'){
		aTokenInfo.addChar(c);
		iCurrentState=S_Symbol;
		return;
	}

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isError(),"Unknown char:"<<(c)<<":"<<(int)c<<"\n");
	IAS_THROW(ParseErrorException(String("Unknown character: ")
			+(char)(c>' '?c:'_')+" ("+TypeTools::IntToString(c)+") ",
			getActiveWrapper()));
}
/*************************************************************************/
void Lexer::handleState_String(unsigned char c){
	IAS_TRACER;

	if(c == '"'){

		iCurrentState=S_End;
		aTokenInfo.setToken(Token::T_STRING,true);

	}else if(c == '\\'){
		iCurrentState=S_StringEsc;

		iEscCharLen   = 0;
		iEscCharValue = 0;

	}else{
		aTokenInfo.addChar(c);
	}

}
/*************************************************************************/
void Lexer::handleState_SpecSymbol(unsigned char c){
	IAS_TRACER;

	if(c == '}'){

		iCurrentState=S_End;
		aTokenInfo.setToken(Token::T_SYMBOL,true);

	}else{
		aTokenInfo.addChar(c);
	}

}
/*************************************************************************/
void Lexer::handleState_StringEsc(unsigned char c){
	IAS_TRACER;

	if(iEscCharLen){

		if('0' <= c && c <= '7'){

			iEscCharValue =  (iEscCharValue << 3) + (c - '0');

			if(++iEscCharLen < 3)
				return;

			aTokenInfo.addChar(iEscCharValue);

		}else{
			IAS_THROW(ParseErrorException(String("Bad octed number after \\")));
		}

	}else {

		if('0' <= c && c <= '7'){

			iEscCharValue = (iEscCharValue << 3) + (c - '0');
			iEscCharLen++;

			return;

		}else
			switch(c){

			case '"' : aTokenInfo.addChar(c); break;

			case 'n' : aTokenInfo.addChar('\n'); break;
			case 't' : aTokenInfo.addChar('\t'); break;
			case '\\': aTokenInfo.addChar('\\'); break;

		default:
			aTokenInfo.addChar(c);
		}
	};

	iCurrentState=S_String;
}
/*************************************************************************/
void Lexer::handleState_Symbol(unsigned char c){
	IAS_TRACER;

	if(isalpha(c) || isdigit(c) || c=='_'){
		aTokenInfo.addChar(c);
	}else{

		getActiveWrapper()->ungetChar();
		iCurrentState=S_End;

		KeywordsMap::const_iterator it=hmKeywords.find(aTokenInfo.getInfo());

		if(it == hmKeywords.end()){
			aTokenInfo.setToken(Token::T_SYMBOL,true);
		}else{
			aTokenInfo.setToken(it->second,true);
		}
	}

}
/*************************************************************************/
void Lexer::handleState_Integer(unsigned char c){
	IAS_TRACER;
	if(isdigit(c)){
		aTokenInfo.addChar(c);
	}else if(c == '.'){
		iCurrentState=S_Float;
		aTokenInfo.addChar(c);
	}else{
		getActiveWrapper()->ungetChar();
		iCurrentState=S_End;
		aTokenInfo.setToken(Token::T_INTEGER,true);
	}

}
/*************************************************************************/
void Lexer::handleState_Float(unsigned char c){
	IAS_TRACER;
	if(isdigit(c)){
		aTokenInfo.addChar(c);
	}else{
		getActiveWrapper()->ungetChar();
		iCurrentState=S_End;
		aTokenInfo.setToken(Token::T_FLOAT,true);
	}

}
/*************************************************************************/
void Lexer::handleState_Greater(unsigned char c){
	IAS_TRACER;

	iCurrentState=S_End;

	if(c == '='){
		aTokenInfo.setToken(Token::T_GREATER_EQ);
	}else{
		getActiveWrapper()->ungetChar();
		aTokenInfo.setToken(Token::T_GREATER);
	}

}
/*************************************************************************/
void Lexer::handleState_Less(unsigned char c){
	IAS_TRACER;

	iCurrentState=S_End;

	if(c == '='){
		aTokenInfo.setToken(Token::T_LESS_EQ);
	}else if(c == '>'){
		aTokenInfo.setToken(Token::T_DIFF);
	}else{
		getActiveWrapper()->ungetChar();
		aTokenInfo.setToken(Token::T_LESS);
	}

}
/*************************************************************************/
void Lexer::handleState_Eq(unsigned char c){
	IAS_TRACER;

	iCurrentState=S_End;

	if(c == '='){
		aTokenInfo.setToken(Token::T_EQ);
	}else{
		getActiveWrapper()->ungetChar();
		aTokenInfo.setToken(Token::T_ASSIGN);
	}

}
/*************************************************************************/
void Lexer::handleState_Colon(unsigned char c){
	IAS_TRACER;

	iCurrentState=S_End;

	if(c == ':'){
		aTokenInfo.setToken(Token::T_DOUBLECOLON);
	}else{
		getActiveWrapper()->ungetChar();
		aTokenInfo.setToken(Token::T_COLON);
	}

}
/*************************************************************************/
void Lexer::handleState_Slash(unsigned char c){
	IAS_TRACER;

	if(c == '/'){
		iCurrentState=S_LineComment;
	}else if(c == '*'){
		iCurrentState=S_BlockComment;
	}else{
		aTokenInfo.setToken(Token::T_SLASH);
		iCurrentState=S_End;
		getActiveWrapper()->ungetChar();
	}
}
/*************************************************************************/
void Lexer::handleState_BlockComment(unsigned char c){
	IAS_TRACER;

	if(c == '*'){

		c = getActiveWrapper()->getChar();

		if(c == '/'){
			iCurrentState=S_Start;
		}else{
			getActiveWrapper()->ungetChar();
		}
	}
}
/*************************************************************************/
void Lexer::handleState_LineComment(unsigned char c){
	IAS_TRACER;

	if(c == '\n')
		iCurrentState=S_Start;
}
/*************************************************************************/
}
}
}
}
