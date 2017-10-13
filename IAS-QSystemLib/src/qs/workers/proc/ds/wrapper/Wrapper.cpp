/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Wrapper.cpp
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
#include "Wrapper.h"
#include<qs/log/LogLevel.h>

#include "Insert.h"
#include "Delete.h"
#include "Update.h"
#include "Call.h"

#include "SelectOnce.h"
#include "SelectArray.h"

#include "exception/ParseException.h"

#include "Lexer.h"

#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
Wrapper::Wrapper():
	bReusable(true){
	IAS_TRACER;
}
/*************************************************************************/
Wrapper::~Wrapper() throw(){
	IAS_TRACER;

	if(bReusable){
		IAS_LOG(LogLevel::INSTANCE.isProfile() , strSQLText<<"\n"<<tsrExe);
	}
}
/*************************************************************************/
Wrapper* Wrapper::Create(::IAS::DS::API::Session* pSession,
								  const String& strSpecification,
								  const ::IAS::DM::DataFactory* pDataFactory,
								  ::IAS::DM::DataObject* dm){
	IAS_TRACER;

	IAS_DFT_FACTORY<Wrapper>::PtrHolder ptrWrapper;

	IAS_DFT_FACTORY<Lexer>::PtrHolder ptrLexer(IAS_DFT_FACTORY<Lexer>::Create(strSpecification));
	Lexer::Token iToken=ptrLexer->nextToken();

	try{

	switch(iToken){

		case Lexer::T_SELECT:

			iToken = ptrLexer->nextToken();

			switch(iToken){
			  case Lexer::T_ONCE:
				ptrWrapper=IAS_DFT_FACTORY<SelectOnce>::Create(pSession, ptrLexer.getPointer(), pDataFactory,dm);
				break;
			  case Lexer::T_ARRAY:
				ptrWrapper=IAS_DFT_FACTORY<SelectArray>::Create(pSession, ptrLexer.getPointer(), pDataFactory,dm);
				break;
			  case Lexer::T_CALL:
				ptrWrapper=IAS_DFT_FACTORY<SelectArray>::Create(pSession, ptrLexer.getPointer(), pDataFactory,dm);
				break;
			  default:
				IAS_THROW(ParseException("Expected ARRAY or ONCE keyword after select.",ptrLexer->getLine()));
			}

			break;

		case Lexer::T_INSERT:
			ptrWrapper=IAS_DFT_FACTORY<Insert>::Create(pSession, ptrLexer.getPointer(), pDataFactory,dm);
			break;

		case Lexer::T_DELETE:
			ptrWrapper=IAS_DFT_FACTORY<Delete>::Create(pSession, ptrLexer.getPointer(), pDataFactory,dm);
			break;

		case Lexer::T_UPDATE:
			ptrWrapper=IAS_DFT_FACTORY<Update>::Create(pSession, ptrLexer.getPointer(), pDataFactory,dm);
			break;

		case Lexer::T_CALL:
			ptrWrapper=IAS_DFT_FACTORY<Call>::Create(pSession, ptrLexer.getPointer(), pDataFactory,dm);
			break;


		default:
			IAS_THROW(ParseException("Expected statement name.",ptrLexer->getLine()));
	}

	}catch(Exception& e){
		e<<", SQL: "<<strSpecification;
		throw;
	};

	return ptrWrapper.pass();
}
/*************************************************************************/
Wrapper::SettersTable::SettersTable(const ::IAS::DM::Type* pType):
		_inputCleaner(tabSetters),
		pType(pType){
	IAS_TRACER;
}
/*************************************************************************/
Wrapper::SettersTable::~SettersTable(){
	IAS_TRACER;
}
/*************************************************************************/
const String& Wrapper::SettersTable::addXPath(const String& strXPath, Mode iMode){
	IAS_TRACER;

	tabSetters.push_back(IAS_DFT_FACTORY<DM::Tools::Setter>::Create(strXPath,pType));

	int iIdx=tabSetters.size()-1;

	char sBuf[8];

	sBuf[0]=':';
	sBuf[1]=iMode == M_INPUT ? 'I' : (iMode == M_OUTPUT ? 'O' : 'X');
	sBuf[2]='0' + (iIdx / 100) % 10 ;
	sBuf[3]='0' + (iIdx / 10)  % 10 ;
	sBuf[4]='0' + (iIdx % 10) ;
	sBuf[5]=0;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"push: "<<strXPath<<" "<<sBuf<<", "<<tabSetters[iIdx]->getTargetTypeEnum());


	tabTags.push_back(sBuf);
	tabModes.push_back(iMode);

	return tabTags[iIdx];
}
/*************************************************************************/
void Wrapper::SettersTable::bind(::IAS::DS::API::IInput* pIInput){
	IAS_TRACER;

	for(int iIdx=0;iIdx<tabTags.size();iIdx++){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"tag: "<<tabTags[iIdx]<<" "<<iIdx<<" / "<<tabTags.size());

		if(tabModes[iIdx] == M_INPUT)
			pIInput->addInput(tabTags[iIdx],tabSetters[iIdx]);
		else
			IAS_THROW(InternalException("Non input variable for IInput interface."));

	}
}
/*************************************************************************/
void Wrapper::SettersTable::bindIO(::IAS::DS::API::IOutput* pIOutput){
	IAS_TRACER;

	for(int iIdx=0;iIdx<tabTags.size();iIdx++){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"tag: "<<tabTags[iIdx]<<" "<<tabSetters[iIdx]->getXPath()<<" "<<iIdx<<" / "<<tabTags.size());

		switch(tabModes[iIdx]){

		case M_INPUT:
			pIOutput->addInput(tabTags[iIdx],tabSetters[iIdx]);
			break;

		case M_OUTPUT:
			pIOutput->addOutput(tabTags[iIdx],tabSetters[iIdx]);
			break;

		case M_INPUT_OUTPUT:
			pIOutput->addInputOutput(tabTags[iIdx],tabSetters[iIdx]);
			break;

		default:
			IAS_THROW(InternalException("Unknown mode."));

		}
	}
}
/*************************************************************************/
Wrapper::ResultSetSettersTable::ResultSetSettersTable(const ::IAS::DM::Type* pType):
		_inputCleaner(tabSetters),
		pType(pType){
	IAS_TRACER;

}
/*************************************************************************/
Wrapper::ResultSetSettersTable::~ResultSetSettersTable(){
	IAS_TRACER;
}
/*************************************************************************/
void Wrapper::ResultSetSettersTable::setType(const ::IAS::DM::Type* pType){
	IAS_TRACER;
	if(tabSetters.size())
		IAS_THROW(InternalException("Type change not allowed when setters are already created."));

	this->pType=pType;
}
/*************************************************************************/
int Wrapper::ResultSetSettersTable::addXPath(const String& strXPath, bool bOptional){
	IAS_TRACER;

	tabSetters.push_back(IAS_DFT_FACTORY<DM::Tools::Setter>::Create(strXPath,pType));
	tabOptional.push_back(bOptional);
	return tabSetters.size() - 1;
}
/*************************************************************************/
void Wrapper::ResultSetSettersTable::bind(::IAS::DS::API::IResultSetOutput* pResultSetOutput){
	IAS_TRACER;

	for(int iIdx=0;iIdx<tabSetters.size();iIdx++){
		pResultSetOutput->addResultSetOutput(tabSetters[iIdx],tabOptional[iIdx]);
	}
}
/*************************************************************************/
void Wrapper::handleWhere(Lexer *pLexer,
							  SettersTable& tabInputSetters,
							  DM::DataObject* dm){
	IAS_TRACER;
	strSQLText+=" WHERE ";

	Lexer::Token iToken = pLexer->nextToken();
	int iNumPar=0;
	int iNumExpr=0;

	bool bOptional=false;

	do {

		switch(iToken) {

			case Lexer::T_AND: strSQLText+=" AND "; iNumExpr=1; break;
			case Lexer::T_OR: strSQLText+=" OR "; iNumExpr=1; break;

			case Lexer::T_OPENPAR: strSQLText+=" ( "; iNumPar++; break;

			case Lexer::T_CLOSEPAR:
			strSQLText+=" ) ";
			if(--iNumPar<0)
				IAS_THROW(ParseException(String("Mismatched parenthesis."),pLexer->getLine()));
			break;

			case Lexer::T_QUESTION_MARK:
				bReusable=false;
				pLexer->assetNext(Lexer::T_SYMBOL);
				handleWhereCondition(pLexer,tabInputSetters,dm,true);
				iNumExpr=0;
				break;
			case Lexer::T_SYMBOL:
				handleWhereCondition(pLexer,tabInputSetters,dm,false);
				iNumExpr=0;
			break;

			default:

				if(iNumPar)
					IAS_THROW(ParseException(String("Mismatched AND / OR arguments."),pLexer->getLine()));

				if(iNumPar)
					IAS_THROW(ParseException(String("Mismatched parenthesis at the end."),pLexer->getLine()));

				return;
		}

		iToken = pLexer->nextToken();

	}while(true);

}
/*************************************************************************/
static void _replace(const String& strPattern,int iIdx,String& strOutput){

	strOutput.clear();

	for(const char *s=strPattern.c_str();*s;s++){
		if(*s == '*'){
			strOutput+=TypeTools::IntToString(iIdx);
		}else
			strOutput+=*s;
	}

}
/*************************************************************************/
static String _array_xpath(const String& strPattern){

	IAS_TRACER;

	String strOutput;

	for(const char *s=strPattern.c_str();*s;s++){
		if(*s == '[' && *++s == '*')
			return strOutput;
		else
			strOutput+=*s;
	}

	IAS_THROW(ItemNotFoundException(strPattern+" - missing * in XPath pattern."));
}
/*************************************************************************/
void Wrapper::handleWhereCondition(Lexer *pLexer,
									   SettersTable& tabInputSetters,
									   DM::DataObject* dm,
									   bool bOptional){
	IAS_TRACER;

	String strColumn(pLexer->getValue());
	bool bQuote=pLexer->isQuoted();

	Lexer::Token iComparatorToken = pLexer->nextToken();
	pLexer->assetNext(Lexer::T_SYMBOL);

	if(iComparatorToken == Lexer::T_IN){

		if(dm->getList(_array_xpath(pLexer->getXPathValue())).size() == 0){
			strSQLText += bOptional ? "1=1" : "0=1";
			return;
		}

	}else{

		if(bOptional && !dm->isSet(pLexer->getXPathValue())){
			strSQLText += "1=1";
			return;
		}

	}

	if(bQuote)
		strSQLText+='"';

	strSQLText += strColumn;

	if(bQuote)
		strSQLText+='"';

	switch(iComparatorToken) {

		case Lexer::T_EQ    :

			if(bOptional && dm->isSet(pLexer->getXPathValue()) && dm->getDataObject(pLexer->getXPathValue()) == NULL){
				strSQLText += " IS NULL ";
				return;
			}

			strSQLText += "  =  ";

			break;

		case Lexer::T_GT    : strSQLText+=" >  "; break;
		case Lexer::T_LE    : strSQLText+=" <  "; break;
		case Lexer::T_GT_EQ : strSQLText+=" >=  "; break;
		case Lexer::T_LE_EQ : strSQLText+=" <=  "; break;
		case Lexer::T_DIFF  : strSQLText+=" <>  "; break;
		case Lexer::T_LIKE  : strSQLText+=" LIKE  "; break;
		case Lexer::T_IN    :{

					strSQLText+=" IN ( ";

			        const String& strXPath(pLexer->getXPathValue());

					DM::DataObjectList& list(dm->getList(_array_xpath(strXPath)));
					String strItemXPath;

					for(int iIdx=0;iIdx<list.size();iIdx++){
						_replace(strXPath,iIdx,strItemXPath);
						if(iIdx)
							strSQLText += ", ";
						strSQLText += tabInputSetters.addXPath(strItemXPath);
					}

					strSQLText+=" ) ";

					bReusable=false;
				}break;

		default:
		IAS_THROW(ParseException(String("Unknown comparator: ")+TypeTools::IntToString(iComparatorToken),pLexer->getLine()));
	}

	if(iComparatorToken != Lexer::T_IN)
		strSQLText += tabInputSetters.addXPath(pLexer->getXPathValue());

}
/*************************************************************************/
}
}
}
}
}
}
