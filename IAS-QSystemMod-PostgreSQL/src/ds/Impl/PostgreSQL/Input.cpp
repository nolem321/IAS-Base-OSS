/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Input.cpp
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
#include "Input.h"
#include "exception/PostgreSQLException.h"

#include <sqlite3.h>
#include "log/LogLevel.h"
#include "Session.h"

#include <qs/fmt/FmtFactory.h>


namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
Input::Input(Statement& statement):
		statement(statement),
		iNumValues(0){
	IAS_TRACER;
}
/*************************************************************************/
Input::~Input() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Input::reset(){
	IAS_TRACER;

	for(int iIdx = 0; iIdx < iNumValues; iIdx++)
		if(tabValues[iIdx])
			delete[] tabValues[iIdx] ;
}
/*************************************************************************/
void Input::addInput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;
	lstElements.push_back(Element(strTag,pSetter));
}
/*************************************************************************/
void Input::feedInputs(DM::DataObjectPtr& dm){
	IAS_TRACER;

	String strValue;
	strValue.reserve(128);

	iNumValues = 0;
	for(ElementList::const_iterator it=lstElements.begin();
		it != lstElements.end(); it++){

		if(!(*it).pSetter->isSet(dm)){

			tabValues[iNumValues++] = 0;

		}else{

			DM::DataObjectPtr dmValue((*it).pSetter->getValue(dm));

			if((*it).pSetter->getTargetTypeEnum() == DM::Type::DataObjectType ||
			   (*it).pSetter->getTargetTypeEnum() == DM::Type::AnyType){
				QS::Fmt::Formatter *pFormatter=statement.getSession()->getFormatter();
				StringStream ssValue;
				pFormatter->write(dmValue,ssValue);
				strValue=ssValue.str();
			}else{
				strValue=dmValue->toString();
			}

			tabValues[iNumValues] = new char [strValue.length() + 1];
			strncpy(tabValues[iNumValues], strValue.c_str(), strValue.length() + 1);
			iNumValues++;
		}
	}
}
/*************************************************************************/
}
}
}
}
