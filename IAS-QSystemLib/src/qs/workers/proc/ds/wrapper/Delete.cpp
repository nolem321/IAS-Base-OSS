/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Delete.cpp
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
#include "Delete.h"
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
Delete::Delete(::IAS::DS::API::Session* pSession,
			   Lexer *pLexer,
			   const ::IAS::DM::DataFactory* pDataFactory,
			   ::IAS::DM::DataObject* dm):
				tabInputSetters(dm->getType()){

	IAS_TRACER;

	ptrDelete=pSession->createDelete();

	strSQLText="DELETE ";

	pLexer->assetNext(Lexer::T_FROM);
	pLexer->assetNext(Lexer::T_SYMBOL);
	bool bQuote=pLexer->isQuoted();

	strSQLText+=" FROM ";

	if(bQuote)
		strSQLText+='"';

	strSQLText+=pLexer->getValue();

	if(bQuote)
		strSQLText+='"';


	if(pLexer->nextToken() == Lexer::T_WHERE)
		handleWhere(pLexer,tabInputSetters,dm);

	pLexer->assetNext(Lexer::T_END);

	ptrDelete->setSQLText(strSQLText);
	ptrDelete->prepare();

	tabInputSetters.bind(ptrDelete);

}
/*************************************************************************/
Delete::~Delete() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Delete::execute(::IAS::DM::DataObjectPtr& dm){
	IAS_TRACER;

	ptrDelete->feedInputs(dm);
	ptrDelete->execute();;
}
/*************************************************************************/
}
}
}
}
}
}
