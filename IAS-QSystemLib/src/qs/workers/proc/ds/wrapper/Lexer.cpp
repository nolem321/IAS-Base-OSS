/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Lexer.cpp
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
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
Lexer::SymbolMap::SymbolMap(){

	(*this)["SELECT"] = T_SELECT;
	(*this)["INSERT"] = T_INSERT;
	(*this)["UPDATE"] = T_UPDATE;
	(*this)["DELETE"] = T_DELETE;
	(*this)["CALL"]   = T_CALL;

	(*this)["ONCE"]  = T_ONCE;
	(*this)["ARRAY"] = T_ARRAY;
	(*this)["MAP"]   = T_MAP;
	(*this)["INTO"]  = T_INTO;
	(*this)["FROM"]  = T_FROM;
	(*this)["SET"]   = T_SET;
	(*this)["WHERE"] = T_WHERE;
	(*this)["AND"]   = T_AND;
	(*this)["OR"]    = T_OR;
	(*this)["LIKE"]  = T_LIKE;
	(*this)["IN"]    = T_IN;
	(*this)["FOR"]   = T_FOR;

	(*this)["PAGE"]       = T_PAGE;
	(*this)["DISTINCT"]   = T_DISTINCT;

}
/*************************************************************************/
Lexer::Token Lexer::SymbolMap::convert(const String& strValue){

	if(count(strValue))
		return at(strValue);

	return Lexer::T_SYMBOL;
}
/*************************************************************************/
Lexer::PrintableSymbolMap::PrintableSymbolMap(){

	(*this)[T_NONE]    = "<none>";
	(*this)[T_SYMBOL]  = "<symbol>";

	(*this)[T_ARROW]         = "=>";
	(*this)[T_COMMA]         = ",";
	(*this)[T_OPENPAR]       = "(";
	(*this)[T_CLOSEPAR]      = ")";
	(*this)[T_QUESTION_MARK] = "?";
	(*this)[T_COLON]         = ":";


	(*this)[T_SELECT]  = "SELECT";
	(*this)[T_INSERT]  = "INSERT";
	(*this)[T_UPDATE]  = "UPDATE";
	(*this)[T_DELETE]  = "DELETE";
	(*this)[T_CALL]    = "CALL";
	(*this)[T_ONCE]    = "ONCE";
	(*this)[T_ARRAY]   = "ARRAY";
	(*this)[T_MAP]     = "MAP";
	(*this)[T_INTO]    = "INTO";
	(*this)[T_FROM]    = "FROM";
	(*this)[T_WHERE]   = "WHERE";
	(*this)[T_SET]     = "SET";

	(*this)[T_AND]    = "AND";
	(*this)[T_OR]     = "OR";
	(*this)[T_EQ]     = " = ";
	(*this)[T_DIFF]   = " <> ";
	(*this)[T_GT]     = " > ";
	(*this)[T_LE]     = " < ";
	(*this)[T_GT_EQ]  = " >= ";
	(*this)[T_LE_EQ]  = " <= ";

	(*this)[T_LIKE]   = "LIKE";
	(*this)[T_IN]     = "IN";
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

		SymbolMap::GetInstance();
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
	strXPathValue.clear();

	iToken=T_NONE;
	bQuoted=false;
	skipBlanks();

	if(!*sCur)
		return iToken=T_END;

	switch(*sCur){

	   case '\'': sCur++; handleQSymbol(); break;
	   case '=': sCur++; handleEQ();      break;
	   case '<': sCur++; handleLt();      break;
	   case '>': sCur++; handleGt();      break;

	   case '(':  sCur++; iToken = T_OPENPAR; break;
	   case ')':  sCur++; iToken = T_CLOSEPAR; break;
	   case ':':  sCur++; iToken = T_COLON; break;
	   case '?':  sCur++; iToken = T_QUESTION_MARK; break;
	   case ',':  sCur++; iToken = T_COMMA;         break;

	   default :
		   if( ('a' <= *sCur && *sCur <= 'z') ||
			   ('A' <= *sCur && *sCur <= 'Z') ||
			   ('_' == *sCur)){

			   strXPathValue+=*sCur;
			   strValue+=*sCur++;

			   handleSymbol();
		   }else{
			   IAS_THROW(ParseException("Parse error / unknown character",iLine));
		   }
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Token: "<<iToken);
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
			 || ('*' == *sCur )
			  )) {
		strXPathValue+=*sCur != '.' ? *sCur : '/';
		strValue+=*sCur++;
	}

	iToken=SymbolMap::GetInstance()->convert(strValue);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Value: "<<strValue);
}
/*************************************************************************/
void Lexer::handleQSymbol(){
	IAS_TRACER;

	bQuoted=true;

	while( *sCur && *sCur != '\n' && *sCur != '\''){
		strXPathValue+=*sCur != '.' ? *sCur : '/';
		strValue+=*sCur++;
	}

	if(*sCur++ != '\'')
		IAS_THROW(ParseException("Parse error at: ",iLine));

	iToken=T_SYMBOL;
}
/*************************************************************************/
void Lexer::handleEQ(){
	IAS_TRACER;

	if(*sCur=='>'){
		iToken=T_ARROW;
		sCur++;
	}else{
		if(*sCur)
			sCur++;
		iToken=T_EQ;
	}

}
/*************************************************************************/
void Lexer::handleLt() {
	IAS_TRACER;

	if(*sCur=='=') {
		iToken=T_LE_EQ;
		sCur++;
	}else if(*sCur=='>') {
		iToken=T_DIFF;
		sCur++;
	} else {
		if(*sCur)
			sCur++;
		iToken=T_LE;
	}

}
/*************************************************************************/
void Lexer::handleGt() {
	IAS_TRACER;

	if(*sCur=='=') {
		iToken=T_GT_EQ;
		sCur++;
	} else {
		if(*sCur)
		sCur++;
		iToken=T_GT;
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
}
