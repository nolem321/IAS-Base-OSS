/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Select.cpp
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
#include "Select.h"
#include<qs/log/LogLevel.h>
#include "Lexer.h"

#include <dm/datamodel.h>

#include "exception/ParseException.h"


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
Select::Select(::IAS::DS::API::Session* pSession,
			   const ::IAS::DM::Type* pType):
			   tabInputSetters(pType),
			   tabResultSetSetters(pType),
			   bForUpdate(false){

	IAS_TRACER;

	ptrSelect=pSession->createSelect();

	strSQLText = "SELECT ";
}
/*************************************************************************/
Select::~Select() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Select::parseResult(Lexer* pLexer,
						 ResultSetSettersTable& tabResultSetSetters,
						 Lexer::Token iStopToken,
						 bool bFirst){
	IAS_TRACER;

	Lexer::Token iToken;

	int iCount=0;

	while((iToken=pLexer->nextToken()) != Lexer::T_END){

		if(iToken == iStopToken)
			break;

		if(iCount) {
			pLexer->assetToken(Lexer::T_COMMA);
			iToken=pLexer->nextToken();
		}

		bool bOptional=false;

		if(iToken == Lexer::T_QUESTION_MARK){
			bOptional=true;
			iToken=pLexer->nextToken();
		}

		if(!bFirst || iCount)
			strSQLText+=", ";

		iCount++;

		pLexer->assetToken(Lexer::T_SYMBOL);

		bool bQuote=pLexer->isQuoted();

		if(bQuote)
			strSQLText+='"';

		strSQLText+=pLexer->getValue();

		if(bQuote)
			strSQLText+='"';

		pLexer->assetNext(Lexer::T_ARROW);
		pLexer->assetNext(Lexer::T_SYMBOL);

		tabResultSetSetters.addXPath(pLexer->getXPathValue(), bOptional);
	}

}
/*************************************************************************/
void Select::parseResultAndFromAndWhere(Lexer* pLexer,
					 	 	 	 	    DM::DataObject* dm,
										ResultSetSettersTable& tabResultSetSetters,
										bool bFirst){
	IAS_TRACER;

	Lexer::Token iToken;

	parseResult(pLexer, tabResultSetSetters, Lexer::T_FROM, bFirst);

	pLexer->assetToken(Lexer::T_FROM);

	pLexer->assetNext(Lexer::T_SYMBOL);

	strSQLText+=" FROM \"";
	strSQLText+=pLexer->getValue();
	strSQLText+="\"";

	//TODO add order by

	if(pLexer->nextToken() == Lexer::T_WHERE)
		handleWhere(pLexer,tabInputSetters,dm);

	if(pLexer->getToken() == Lexer::T_FOR){
		pLexer->assetNext(Lexer::T_UPDATE);
		bForUpdate=true;

		strSQLText+=" FOR UPDATE ";
	}

	pLexer->assetNext(Lexer::T_END);
}
/*************************************************************************/
}
}
}
}
}
}
