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
#include <lang/model/dec/ResultDeclarationNode.h>

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

	bool bIsFunction = false;

	ptrCall=pSession->createCall();

	Lexer::Token iToken = pLexer->nextToken();

	if(iToken == Lexer::T_INTO){

		bIsFunction = true;

		pLexer->assetNext(Lexer::T_SYMBOL);

		String strXPath(pLexer->getXPathValue());
		String strTag(tabInputSetters.addXPath(strXPath, SettersTable::M_OUTPUT));

		strSQLText = "BEGIN " + strTag + " := ";

		pLexer->nextToken();

	}else{
		strSQLText = "CALL ";
	};

	pLexer->assetToken(Lexer::T_SYMBOL);

	bool bQuote=pLexer->isQuoted();

	//if(bQuote)
	//	strSQLText+='"';

	strSQLText+=pLexer->getValue();

	//if(bQuote)
	//	strSQLText+='"';

	int iCount=0;

	pLexer->assetNext(Lexer::T_OPENPAR);

	while((iToken=pLexer->nextToken()) != Lexer::T_END){

		if(iToken == Lexer::T_CLOSEPAR)
			break;

		if(iCount){
			pLexer->assetToken(Lexer::T_COMMA);
			pLexer->nextToken();
		}else{
			strSQLText+="(";
		}

		pLexer->assetToken(Lexer::T_SYMBOL);

		String strXPath(pLexer->getXPathValue());
		bool bQuote=pLexer->isQuoted();

		iToken=pLexer->nextToken();
		SettersTable::Mode iMode;

		switch(iToken){strSQLText+='"';

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

		if(bQuote)
			strSQLText+='"';

		strSQLText+=strTag;

		if(bQuote)
			strSQLText+='"';

	}

	if(iCount)
		strSQLText += ")";

	iToken=pLexer->nextToken();

	if(bIsFunction)
		strSQLText += "; END;";

	if(iToken != Lexer::T_END)
		IAS_THROW(ParseException(String("Expected end of input, got:")+TypeTools::IntToString(iToken),pLexer->getLine()));

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
	TimeSample ts(true);
	ptrCall->execute();
	tsrExe.addSample(ts);
	ptrCall->fetch(dm);
}
/*************************************************************************/
}
}
}
}
}
}
