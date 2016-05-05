/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Call.cpp
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
#include "Call.h"
#include<qs/log/LogLevel.h>

#include <dm/datamodel.h>
#include "Lexer.h"

#include "exception/ParseException.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
Call::Call(::IAS::DS::API::Session* pSession,
			   Lexer *pLexer,
			   const ::IAS::DM::DataFactory* pDataFactory,
			   ::IAS::DM::DataObject* dm):
			   tabInputSetters(dm->getType()){

	IAS_TRACER;

	ptrCall=pSession->createCall();

	pLexer->assetNext(Lexer::T_SYMBOL);

	bool bQuote=pLexer->isQuoted();

	strSQLText+="CALL ";

	if(bQuote)
		strSQLText+='"';

	strSQLText+=pLexer->getValue();

	if(bQuote)
		strSQLText+='"';

	pLexer->assetNext(Lexer::T_OPENPAR);
	strSQLText+=" (";

	Lexer::Token iToken;
	int iCount=0;

	while((iToken=pLexer->nextToken()) != Lexer::T_END){

		if(iToken == Lexer::T_CLOSEPAR)
			break;

		if(iCount){
			pLexer->assetToken(Lexer::T_COMMA);
			pLexer->nextToken();
		}

		pLexer->assetToken(Lexer::T_SYMBOL);

		String strXPath(pLexer->getXPathValue());

		iToken=pLexer->nextToken();
		SettersTable::Mode iMode;

		switch(iToken){
			case Lexer::T_ARROW:
				iMode=SettersTable::M_INPUT;
			break;
			case Lexer::T_LE_EQ:
				iMode=SettersTable::M_OUTPUT;
			break;
			case Lexer::T_DIFF:
				iMode=SettersTable::M_INPUT_OUTPUT;
			break;
			default:
				IAS_THROW(ParseException(String("Expected => / <= / <> , got:")+TypeTools::IntToString(iToken),pLexer->getLine()));
		}

		String strTag(tabInputSetters.addXPath(strXPath,iMode));

		if(iCount++)
			strSQLText+=", ";

		strSQLText+=strTag;
	}


	iToken=pLexer->nextToken();

	if(iToken != Lexer::T_END)
		IAS_THROW(ParseException(String("Expected end of input, got:")+TypeTools::IntToString(iToken),pLexer->getLine()));


	strSQLText+=")";

	ptrCall->setSQLText(strSQLText);
	ptrCall->prepare();

	tabInputSetters.bindIO(ptrCall);
}
/*************************************************************************/
Call::~Call() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Call::parseInput(Lexer* pLexer){
	IAS_TRACER;
}
/*************************************************************************/
void Call::execute(::IAS::DM::DataObjectPtr& dm){
	IAS_TRACER;

	ptrCall->feedInputs(dm);
	ptrCall->execute();
	ptrCall->fetch(dm);
}
/*************************************************************************/
}
}
}
}
}
}
