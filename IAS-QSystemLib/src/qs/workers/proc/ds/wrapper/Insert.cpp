/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Insert.cpp
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
#include "Insert.h"
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
Insert::Insert(::IAS::DS::API::Session* pSession,
			   Lexer *pLexer,
			   const ::IAS::DM::DataFactory* pDataFactory,
			   ::IAS::DM::DataObject* dm):
			   tabInputSetters(dm->getType()){

	IAS_TRACER;

	ptrInsert=pSession->createInsert();


	pLexer->assetNext(Lexer::T_INTO);
	pLexer->assetNext(Lexer::T_SYMBOL);
	bool bQuote=pLexer->isQuoted();

	strSQLText+="INSERT INTO ";

	if(bQuote)
		strSQLText+='"';

	strSQLText+=pLexer->getValue();

	if(bQuote)
		strSQLText+='"';

	strSQLText+=" (";

	Lexer::Token iToken;
	int iCount=0;

	while((iToken=pLexer->nextToken()) != Lexer::T_END){

		if(iCount){
			pLexer->assetToken(Lexer::T_COMMA);
			iToken=pLexer->nextToken();
		}

		if(iToken == Lexer::T_QUESTION_MARK){

			bReusable=false;

			pLexer->assetNext(Lexer::T_SYMBOL);

			if(!dm->isSet(pLexer->getXPathValue())){
				pLexer->assetNext(Lexer::T_ARROW);
				pLexer->assetNext(Lexer::T_SYMBOL);
				continue;
			}
		}

		pLexer->assetToken(Lexer::T_SYMBOL);

		tabInputSetters.addXPath(pLexer->getXPathValue());

		pLexer->assetNext(Lexer::T_ARROW);
		pLexer->assetNext(Lexer::T_SYMBOL);
		bool bQuote=pLexer->isQuoted();

		if(iCount++)
			strSQLText+=", ";

		if(bQuote)
			strSQLText+='"';

		strSQLText+=pLexer->getValue();

		if(bQuote)
			strSQLText+='"';

	}

	pLexer->nextToken();

	if(iToken != Lexer::T_END)
		IAS_THROW(ParseException(String("Expected end of input, got:")+TypeTools::IntToString(iToken),pLexer->getLine()));

	const SettersTable::TagsTable& tabTags(tabInputSetters.getTags());

	strSQLText+=") VALUES (";

	for(SettersTable::TagsTable::const_iterator it=tabTags.begin();
		it != tabTags.end();
	    it++){

			if(it != tabTags.begin())
				strSQLText+=", ";

			strSQLText+=*it;
	    }

	strSQLText+=")";

	ptrInsert->setSQLText(strSQLText);
	ptrInsert->prepare();

	tabInputSetters.bind(ptrInsert);
}
/*************************************************************************/
Insert::~Insert() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Insert::parseInput(Lexer* pLexer){
	IAS_TRACER;
}
/*************************************************************************/
void Insert::execute(::IAS::DM::DataObjectPtr& dm){
	IAS_TRACER;

	ptrInsert->feedInputs(dm);
	TimeSample ts(true);
	ptrInsert->execute();
	tsrExe.addSample(ts);
}
/*************************************************************************/
}
}
}
}
}
}
