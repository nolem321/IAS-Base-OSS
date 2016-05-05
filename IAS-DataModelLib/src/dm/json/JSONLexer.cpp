/*
 * File: IAS-DataModelLib/src/dm/json/JSONLexer.cpp
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
#include "../../dm/json/JSONLexer.h"
#include <commonlib/commonlib.h>

#include "../../dm/json/exception/JSONHelperException.h"
#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace JSON {

/*************************************************************************/
JSONLexer::JSONLexer(std::istream& is):
		is(is),
		iLineNo(1),
		iState(S_Start),
		iToken(T_None),
		cCurrent(0){
	IAS_TRACER;

	strValue.reserve(128);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"JSONLexer is ready.");
}
/*************************************************************************/
JSONLexer::~JSONLexer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
JSONLexer::Token JSONLexer::next(){
	IAS_TRACER;

	iToken=T_None;
	iState=S_Start;

	strValue.clear();

	skipWhiteChars();

	while(iToken == T_None){

		switch(iState){
			case S_Start:  handleStart();  break;
			case S_String: handleString(); break;
			case S_Symbol:  handleSymbol(); break;
			case S_Number: handleNumber(); break;
			default:
				//TODO more JSON Handlers
				IAS_THROW(InternalException("Not implemented case in JSON Lexer."));
		}
	}

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Token:"<<iToken);

	return iToken;
}
/*************************************************************************/
void JSONLexer::nextChar(){
	IAS_TRACER;

	cCurrent=is.get();

	if(is.eof())
		IAS_THROW(JSONHelperException("Unexpected end of stream in JSON lexer.",iLineNo));

}
/*************************************************************************/
void JSONLexer::skipWhiteChars(){
	IAS_TRACER;

	do{
		nextChar();
		if(cCurrent=='\n')
			iLineNo++;
	}while(cCurrent == ' ' || cCurrent == '\n' || cCurrent == '\t');

}
/*************************************************************************/
void JSONLexer::handleStart(){
	IAS_TRACER;

	switch(cCurrent){

		case '{' :
			iToken = T_LeftBrace;
		return;

		case '}' :
			iToken = T_RightBrace;
		return;

		case '[' :
			iToken = T_LeftBracket;
		return;

		case ']' :
			iToken = T_RightBracket;
		return;

		case ':' :
			iToken = T_Colon;
		return;

		case ',' :
			iToken = T_Comma;
		return;

		case '"' :
			iState = S_String;
		return;

		default:

			if((cCurrent>='0' && cCurrent<='9') || cCurrent == '-' || cCurrent=='+'){
				strValue+=cCurrent;
				iState= S_Number;
				return;
			}

			if((cCurrent>='a' && cCurrent<='z') || (cCurrent>='A' && cCurrent<='Z')){
				strValue+=cCurrent;
				iState= S_Symbol;
				return;
			}
	}

	IAS_THROW(JSONHelperException("Unexptected character: [")<<cCurrent<<":"<<(int)cCurrent<<"]"<<iLineNo);
}
/*************************************************************************/
void JSONLexer::handleSymbol(){
	IAS_TRACER;

	nextChar();

	if((cCurrent>='a' && cCurrent<='z') || (cCurrent>='A' && cCurrent<='Z')){
		strValue+=cCurrent;
	}else{

		if(strValue.compare("true")){
			iToken=T_BooleanValue;

		}else if(strValue.compare("false")){
			iToken=T_BooleanValue;

		}else if(strValue.compare("null")){
			iToken=T_Null;
		}

		is.unget();
	}

}
/*************************************************************************/
void JSONLexer::handleString(){
	IAS_TRACER;
	nextChar();

	//TODO escapes

	if(cCurrent != '"'){
		strValue+=cCurrent;
	}else{
		iToken=T_StringValue;
	}

}
/*************************************************************************/
void JSONLexer::handleNumber(){
	IAS_TRACER;

	nextChar();

	if((cCurrent>='0' && cCurrent<='9') || cCurrent=='.'){
		strValue+=cCurrent;
	}else{
		iToken=T_NumericValue;
		is.unget();
	}

}
/*************************************************************************/
void JSONLexer::asset(Token iToken){
	IAS_TRACER;
	next();
	if(iToken != this->iToken)
		IAS_THROW(JSONHelperException(String("Unexpected token! Expected=")+
				TypeTools::IntToString(iToken)+", got="+
				TypeTools::IntToString(this->iToken),iLineNo));
}
/*************************************************************************/
}
}
}
