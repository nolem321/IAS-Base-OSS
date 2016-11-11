/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/SelectOnce.cpp
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
#include "SelectOnce.h"
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
SelectOnce::SelectOnce(::IAS::DS::API::Session* pSession,
			   Lexer *pLexer,
			   const ::IAS::DM::DataFactory* pDataFactory,
			   ::IAS::DM::DataObject* dm):
			   Select(pSession,dm->getType()){

	IAS_TRACER;

	parseResultAndFromAndWhere(pLexer,dm,tabResultSetSetters,true);

	ptrSelect->setSQLText(strSQLText);
	ptrSelect->prepare();

	tabInputSetters.bind(ptrSelect);
	tabResultSetSetters.bind(ptrSelect);
}
/*************************************************************************/
SelectOnce::~SelectOnce() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SelectOnce::parseInput(Lexer* pLexer){
	IAS_TRACER;
}
/*************************************************************************/
void SelectOnce::execute(::IAS::DM::DataObjectPtr& dm){
	IAS_TRACER;

	ptrSelect->feedInputs(dm);

	TimeSample ts(true);

	ptrSelect->execute();

	tsrExe.addSample(ts);

	AutoClose ac(ptrSelect);

	if(ptrSelect->next()){

		for(int iIdx=0;iIdx<tabResultSetSetters.size();iIdx++){
			ptrSelect->fetch(iIdx,dm);
		}

	}
}
/*************************************************************************/
}
}
}
}
}
}
