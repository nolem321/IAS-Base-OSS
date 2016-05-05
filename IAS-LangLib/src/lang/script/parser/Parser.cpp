/*
 * File: IAS-LangLib/src/lang/script/parser/Parser.cpp
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
#include "../../script/parser/Parser.h"

#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "AutoGenParser.hpp"
#include "../../script/parser/AutoGenParser.hpp"
#include "../../script/parser/location.hh"
#include "../../script/parser/Lexer.h"

#include <lang/exception/ParseErrorException.h>
#include <lang/exception/SourceNotFoundException.h>


namespace IAS {
namespace Lang {
namespace Script {
namespace Parser {

/*************************************************************************/
Parser::Parser(Model::Model *pModel):
	pLexer(NULL){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pModel);
	this->pModel=pModel;
}

/*************************************************************************/
Parser::~Parser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Model::Model *Parser::getModel() const
{
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pModel);
	return pModel;
}
/*************************************************************************/
void Parser::parse(Lexer *pLexer){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pLexer);
	this->pLexer=pLexer;
	yy::AutoGenParser autoGenParser(*this);
	autoGenParser.parse();
	this->pLexer=NULL;
}
/*************************************************************************/
Lang::Model::ProgramNode* Parser::getLastProgram()const{
	IAS_TRACER;
	if(lstPrograms.size()==0)
		IAS_THROW(ItemNotFoundException("The last program not found."));

	return *(lstPrograms.begin());
}
/*************************************************************************/
const Parser::ProgramList& Parser::getRecentlyParsed()const{
	IAS_TRACER;
	return lstPrograms;
}
/*************************************************************************/
void Parser::addProgram(Lang::Model::ProgramNode* pProgram){
	IAS_TRACER;
	getModel()->addProgram(pProgram);
	lstPrograms.push_front(pProgram);
}
/*************************************************************************/
void Parser::addTypeDefinition(Lang::Model::Dec::TypeDefinitionNode* pTypeDefinition){
	IAS_TRACER;
	getModel()->addTypeDefinition(pTypeDefinition);
}
/*************************************************************************
Model::SourceLocation Parser::getLocation()const{
	IAS_TRACER;

	const String& str
	Model::SourceLocation::SourceID iSourceId=
			pModel->getSourceID(pLexer->getLocation()->getName());
}
/*************************************************************************/
void Parser::open(const String& strObjectName){
	IAS_TRACER;
	try{
		pLexer->openObject(strObjectName);
	}catch(ItemNotFoundException& e){
		IAS_THROW(SourceNotFoundException(strObjectName,
				pLexer->getLocation()->getName(),
				pLexer->getLocation()->getLineNo()));
	}
}
/*************************************************************************/
Lexer* Parser::getLexer(){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pLexer);
	return pLexer;
}
/*************************************************************************/
void Parser::onAutoGenParserError(const yy::location& l, const std::string& strInfo){
	IAS_TRACER;

	String strTmp(strInfo.c_str());

	IAS_THROW(ParseErrorException(strTmp,
			pLexer->getLocation()->getName(),
			pLexer->getLocation()->getLineNo()));

}
/*************************************************************************/
}
}
}
}
