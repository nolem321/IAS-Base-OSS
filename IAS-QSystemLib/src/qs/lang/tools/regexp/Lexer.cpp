/*
 * File: IAS-QSystemLib/src/qs/lang/tools/regexp/Lexer.cpp
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
#include "Lexer.h"
#include<qs/log/LogLevel.h>

#include <dm/datamodel.h>
#include "exception/ParseException.h"

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {
namespace RegExp {

/*************************************************************************/
Lexer::PrintableSymbolMap::PrintableSymbolMap(){

	(*this)[T_NONE]    = "<none>";
	(*this)[T_STRING]  = "<regex/string/uri>";
	(*this)[T_SYMBOL]  = "<symbol/xpath>";
	(*this)[T_NUMBER]  = "<unsigned integer>";

	(*this)[T_ARROW]         = "=>";
	(*this)[T_COMMA]         = ",";
	(*this)[T_OPENPAR]       = "(";
	(*this)[T_CLOSEPAR]      = ")";
	(*this)[T_COLON]         = ":";


	(*this)[T_END]    = "<end of text>";


}

/*************************************************************************/
Lexer::Lexer(const String& strText):
		iLine(1),
		iUnGet(0),
		iToken(T_NONE),
		bQuoted(false),
		sCur(strText.c_str()){

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Specification: \n"<<strText<<"\n");

	IAS_TRACER;

	{
		static Mutex mutex;
		Mutex::Locker locker(mutex);

		PrintableSymbolMap::GetInstance();
	}
}
/*************************************************************************/
Lexer::~Lexer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Lexer::skipBlanks(){
	IAS_TRACER;

	for(; *sCur && (*sCur==' ' || *sCur=='\n' || *sCur=='\t' || *sCur=='\r');sCur++)
		if(*sCur == '\n')
			iLine++;

}
/*************************************************************************/
Lexer::Token Lexer::nextToken(){
	IAS_TRACER;

	if(iUnGet){
		iUnGet=0;
		return iToken;
	}

	strValue.clear();

	iToken=T_NONE;
	bQuoted=false;
	skipBlanks();

	if(!*sCur)
		return iToken=T_END;

	switch(*sCur){

	   case '\'': sCur++; handleString(); break;
	   case '=' : sCur++; handleEQ(); break;
	   case '(' :  sCur++; iToken = T_OPENPAR; break;
	   case ')' :  sCur++; iToken = T_CLOSEPAR; break;
	   case ':' :  sCur++; iToken = T_COLON; break;
	   case ',' :  sCur++; iToken = T_COMMA;         break;

	   default :

		   if('0' <= *sCur && *sCur <= '9'){
			   handleNumber();
		   }else if( ('a' <= *sCur && *sCur <= 'z') ||
			   ('A' <= *sCur && *sCur <= 'Z') ||
			   ('_' == *sCur)){

			   strValue+=*sCur++;

			   handleSymbol();
		   }else{
			   IAS_THROW(ParseException("Parse error / unknown character",iLine));
		   }
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo()||true,"Token: "<<iToken);
	return iToken;
}
/*************************************************************************/
void Lexer::handleSymbol(){
	IAS_TRACER;

	while( *sCur &&
			(   ('a' <= *sCur && *sCur <= 'z')
			 || ('A' <= *sCur && *sCur <= 'Z')
			 || ('0' <= *sCur && *sCur <= '9')
			 || ('.' == *sCur )
			 || ('_' == *sCur )
			 || ('[' == *sCur )
			 || (']' == *sCur )
			 || ('/' == *sCur )
			 || ('#' == *sCur )
			  )) {
		strValue+=*sCur != '.' ? *sCur : '/';

		sCur++;
	}

	iToken=T_SYMBOL;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Value: "<<strValue);
}
/*************************************************************************/
void Lexer::handleString(){
	IAS_TRACER;

	bQuoted=true;

	while( *sCur && *sCur != '\n' && *sCur != '\''){
		strValue+=*sCur++;
	}

	if(*sCur++ != '\'')
		IAS_THROW(ParseException("Parse error at: ",iLine));

	iToken=T_STRING;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Value (string): ["<<strValue<<"]");
}
/*************************************************************************/
void Lexer::handleNumber(){
	IAS_TRACER;

	while( *sCur && '0' <= *sCur && *sCur <= '9'){
			strValue+=*sCur++;
	}

	iToken=T_NUMBER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Value (number): "<<strValue);
}
/*************************************************************************/
void Lexer::handleEQ(){
	IAS_TRACER;

	if(*sCur == '>'){
		iToken=T_ARROW;
		sCur++;
	}else{
		IAS_THROW(ParseException("Parse error ('=>' expected) at: ",iLine));
	}

}
/*************************************************************************/
void Lexer::assetToken(Token iToken){
	IAS_TRACER;
	if(iToken != this->iToken){
		StringStream ssMsg;
		ssMsg<<"Expected token: \""<<PrintableSymbolMap::GetInstance()->find(iToken)->second;
		ssMsg<<"\", got: \""<<PrintableSymbolMap::GetInstance()->find(this->iToken)->second<<"\"";
		IAS_THROW(ParseException(ssMsg.str(),iLine));
	}

}
/*************************************************************************/
void Lexer::assetNext(Token iToken){
	IAS_TRACER;
	nextToken();
	assetToken(iToken);
}
/*************************************************************************/
void Lexer::unGet(){
	IAS_TRACER;
	if(iToken==T_NONE)
		IAS_THROW(BadUsageException("Token is T_NONE in unget()"));

	if(iUnGet)
		IAS_THROW(BadUsageException("Only one unget() call in a sequence allowed."));

	iUnGet++;
}
/*************************************************************************/
}
}
}
}
}

