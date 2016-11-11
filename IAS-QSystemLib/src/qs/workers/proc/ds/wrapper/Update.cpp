/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Update.cpp
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
#include "Update.h"
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
Update::Update(::IAS::DS::API::Session* pSession,
			   Lexer *pLexer,
			   const ::IAS::DM::DataFactory* pDataFactory,
			   ::IAS::DM::DataObject* dm):
				tabInputSetters(dm->getType()){

	IAS_TRACER;

	ptrUpdate=pSession->createUpdate();

	strSQLText="UPDATE ";

	pLexer->assetNext(Lexer::T_SYMBOL);
	bool bQuote=pLexer->isQuoted();

	if(bQuote)
		strSQLText+='"';

	strSQLText+=pLexer->getValue();

	if(bQuote)
		strSQLText+='"';

	pLexer->assetNext(Lexer::T_SET);
	strSQLText+=" SET ";

	Lexer::Token iToken;

	int iCountSpec=0;

	iCountSql=0;

	while((iToken=pLexer->nextToken()) != Lexer::T_END){

		if(iToken == Lexer::T_WHERE)
			break;

		if(iCountSpec++) {
			pLexer->assetToken(Lexer::T_COMMA);
			iToken=pLexer->nextToken();
		}

		if(iToken == Lexer::T_QUESTION_MARK) {

			bReusable=false;
			pLexer->assetNext(Lexer::T_SYMBOL);

			if(!dm->isSet(pLexer->getXPathValue())) {
				pLexer->assetNext(Lexer::T_ARROW);
				pLexer->assetNext(Lexer::T_SYMBOL);
				iCountSpec++;
				continue;
			}
		}

		const String& strTag(tabInputSetters.addXPath(pLexer->getXPathValue()));

		pLexer->assetNext(Lexer::T_ARROW);
		pLexer->assetNext(Lexer::T_SYMBOL);

		bool bQuote=pLexer->isQuoted();

		if(iCountSql++)
			strSQLText+=",";

		if(bQuote)
			strSQLText+='"';

		strSQLText+=pLexer->getValue();

		if(bQuote)
			strSQLText+='"';

		strSQLText+=" = ";
		strSQLText+=strTag;

	}


	if(iToken == Lexer::T_WHERE)
		handleWhere(pLexer,tabInputSetters,dm);

	pLexer->assetNext(Lexer::T_END);

	if(iCountSql == 0)
		return;

	ptrUpdate->setSQLText(strSQLText);
	ptrUpdate->prepare();

	tabInputSetters.bind(ptrUpdate);

}
/*************************************************************************/
Update::~Update() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Update::execute(::IAS::DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(iCountSql == 0)
		return;

	ptrUpdate->feedInputs(dm);

	TimeSample ts(true);
	ptrUpdate->execute();
	tsrExe.addSample(ts);
}
/*************************************************************************/
}
}
}
}
}
}
