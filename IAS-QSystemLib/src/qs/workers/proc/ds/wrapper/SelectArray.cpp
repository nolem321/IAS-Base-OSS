/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/SelectArray.cpp
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
#include "SelectArray.h"
#include<qs/log/LogLevel.h>
#include "Lexer.h"

#include <dm/datamodel.h>

#include "exception/ParseException.h"
#include "limits.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
SelectArray::SelectArray(::IAS::DS::API::Session* pSession,
			   Lexer *pLexer,
			   const ::IAS::DM::DataFactory* pDataFactory,
			   ::IAS::DM::DataObject* dm):
			   iOffset(0),
			   iPageSize(/*UINT_MAX*/9999999),
			   iSkip(0),
			   Select(pSession,dm->getType()){

	IAS_TRACER;

	pLexer->assetNext(Lexer::T_INTO);
	pLexer->assetNext(Lexer::T_SYMBOL);

	ptrArraySetter=IAS_DFT_FACTORY<DM::Tools::Setter>::Create(pLexer->getXPathValue(),dm->getType());
	tabResultSetSetters.setType(ptrArraySetter->getTargetType());

	Lexer::Token iToken = pLexer->nextToken();

	if(iToken == Lexer::T_PAGE){

		pLexer->assetNext(Lexer::T_OPENPAR);
		pLexer->assetNext(Lexer::T_SYMBOL);
		String strArgOne(pLexer->getXPathValue());

		iToken = pLexer->nextToken();

		if(iToken == Lexer::T_COMMA){

			pLexer->assetNext(Lexer::T_SYMBOL);
			String strArgTwo(pLexer->getXPathValue());

			ptrPageOffsetSetter = IAS_DFT_FACTORY<DM::Tools::Setter>::Create(strArgOne,dm->getType());
			ptrPageSizeSetter   = IAS_DFT_FACTORY<DM::Tools::Setter>::Create(strArgTwo,dm->getType());

			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Page:["<<strArgOne<<","<<strArgTwo<<"]");

			pLexer->nextToken();
		}else {
			ptrPageSizeSetter=IAS_DFT_FACTORY<DM::Tools::Setter>::Create(strArgOne,dm->getType());
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Page:["<<strArgOne<<"]");
		}

		pLexer->assetToken(Lexer::T_CLOSEPAR);
		iToken = pLexer->nextToken();
	}


	int iCount=0;

	String strTypeSelectionColumn;
	if(iToken == Lexer::T_MAP){

		iSkip++;

		pLexer->assetNext(Lexer::T_SYMBOL);

		strTypeSelectionColumn=pLexer->getValue();

		if(pLexer->isQuoted())
			strSQLText += "\""+strTypeSelectionColumn+"\"";
		else
			strSQLText += strTypeSelectionColumn;

		pLexer->assetNext(Lexer::T_OPENPAR);

		iToken = pLexer->nextToken();

		while(iToken == (iCount ? Lexer::T_COMMA : Lexer::T_SYMBOL)){

				if(iCount++){
					pLexer->assetToken(Lexer::T_COMMA);
					pLexer->nextToken();
				}

				String strValue=pLexer->getValue();

				pLexer->assetNext(Lexer::T_ARROW);
				pLexer->assetNext(Lexer::T_SYMBOL);
				String strType=pLexer->getValue();

				pLexer->assetNext(Lexer::T_COLON);
				pLexer->assetNext(Lexer::T_SYMBOL);
				String strURI=pLexer->getValue();

				iToken = pLexer->nextToken();

				if(strValue.compare("_")){

					ResultSetSettersTableWithOffset& tabResultSetSetters(hmTypes.add(strValue,pDataFactory->getType(strURI,strType)));
					tabResultSetSetters.setOffset(iSkip);
					if(iToken == Lexer::T_OPENPAR){
						parseResult(pLexer, tabResultSetSetters, Lexer::T_CLOSEPAR, false);
						pLexer->assetToken(Lexer::T_CLOSEPAR);
						iToken = pLexer->nextToken();
					}

					iSkip+=tabResultSetSetters.size();
				}
				else
					hmTypes.setDefault(pDataFactory->getType(strURI,strType));

			}


		if(iToken != Lexer::T_CLOSEPAR)
			IAS_THROW(ParseException(String("Expected ')', got:")+TypeTools::IntToString(iToken),pLexer->getLine()));

	}else{
		pLexer->unGet();
	}

	if(iToken == Lexer::T_DISTINCT){

		strSQLText +=" DISTINCT ";

		pLexer->nextToken();
	}

	parseResultAndFromAndWhere(pLexer,dm,tabResultSetSetters,strTypeSelectionColumn.empty());

	ptrSelect->setSQLText(strSQLText);
	ptrSelect->prepare();

	tabInputSetters.bind(ptrSelect);

	if(!strTypeSelectionColumn.empty()){
		ptrTypeColumnSetter=IAS_DFT_FACTORY<DM::Tools::Setter>::Create("",pDataFactory->getDefaultType(DM::Type::TextType));
		ptrSelect->addResultSetOutput(ptrTypeColumnSetter,false);
	}

	hmTypes.bind(ptrSelect);
	tabResultSetSetters.bind(ptrSelect);

}
/*************************************************************************/
SelectArray::~SelectArray() throw(){
	IAS_TRACER;
}
/*************************************************************************/
SelectArray::TypesMap::TypesMap()throw(){};
/*************************************************************************/
SelectArray::ResultSetSettersTableWithOffset::ResultSetSettersTableWithOffset(const DM::Type* pType):
		ResultSetSettersTable(pType),iOffset(0){};
/*************************************************************************/
void SelectArray::ResultSetSettersTableWithOffset::setOffset(int iOffset){
	this->iOffset=iOffset;
}
/*************************************************************************/
int SelectArray::ResultSetSettersTableWithOffset::getOffset()const{
	return iOffset;
}
/*************************************************************************/
SelectArray::ResultSetSettersTableWithOffset& SelectArray::TypesMap::add(const String& strKey, const DM::Type* pType) {
	IAS_TRACER;
	if(hmEntries.count(strKey))
		IAS_THROW(BadUsageException(strKey+" - already exist."));
	SelectArray::ResultSetSettersTableWithOffset *pResult = hmEntries[strKey]=EntryFactory::Create(pType);
	lstBindOrder.push_back(pResult);
	return *pResult;
}
/*************************************************************************/
void SelectArray::TypesMap::setDefault(const DM::Type* pType) {
	IAS_TRACER;

	if(! ptrDefault.isNull())
		IAS_THROW(BadUsageException("Default type already exist."));

	ptrDefault=EntryFactory::Create(pType);
}
/*************************************************************************/
const SelectArray::ResultSetSettersTableWithOffset& SelectArray::TypesMap::getDefault()const{
	if(!ptrDefault)
		IAS_THROW(ItemNotFoundException("Default key - missing."));
	return *ptrDefault;
}
/*************************************************************************/
const SelectArray::ResultSetSettersTableWithOffset& SelectArray::TypesMap::lookup(const DM::DataObject* dm)const{
	IAS_TRACER;

	if(!dm){

		if(!ptrDefault)
			IAS_THROW(ItemNotFoundException("default value missing."));

		return *ptrDefault;
	}

	String strValue(dm->toString());

	if(!hmEntries.count(strValue)){

		if(!ptrDefault)
			IAS_THROW(ItemNotFoundException(strValue + " - missing."));

		return *ptrDefault;
	}

	return *hmEntries.at(strValue);
}
/*************************************************************************/
void SelectArray::TypesMap::bind(::IAS::DS::API::IResultSetOutput* pResultSetOutput){
	IAS_TRACER;

	for (BindOrderList::iterator it=lstBindOrder.begin(); it != lstBindOrder.end(); ++it)
		(*it)->bind(pResultSetOutput);

}
/*************************************************************************/
void SelectArray::execute(::IAS::DM::DataObjectPtr& dm){
	IAS_TRACER;

	ptrSelect->feedInputs(dm);

	TimeSample ts(true);
	ptrSelect->execute();
	tsrExe.addSample(ts);

	AutoClose ac(ptrSelect);

	if(!ptrPageOffsetSetter.isNull()){
		iOffset=ptrPageOffsetSetter->getValue(dm)->toInteger();
	}

	if(!ptrPageSizeSetter.isNull()){
		iPageSize=ptrPageSizeSetter->getValue(dm)->toInteger();
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Page:["<<iOffset<<","<<iPageSize<<"]");

	unsigned int iCount=0;
	unsigned int iLimit=iPageSize+iOffset;

	DM::DataObjectPtr dmNew;
	DM::DataObjectPtr dmTypeSelect;

	while(ptrSelect->next() && iLimit-- > 0)
	if(iOffset) {
		iOffset--;
	} else {

		if(iSkip) {
			ptrSelect->fetch(0,dmTypeSelect);

			const ResultSetSettersTableWithOffset& tabResultSetSetter(hmTypes.lookup(dmTypeSelect));

			dmNew=tabResultSetSetter.getType()->createDataObject();
			ptrArraySetter->setDataObject(dm,dmNew);

			int iOffset=tabResultSetSetter.getOffset();
			for(int iIdx=0; iIdx<tabResultSetSetter.size(); iIdx++)
				ptrSelect->fetch(iIdx+iOffset,dmNew);

		} else {
			dmNew=ptrArraySetter->create(dm);
		}

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"NEW type: "<<dmNew->getType()->getName()<<" : "<<dmNew->getType()->getURI()<<", at="
				<<(void*)(dmNew.getPointer()));

		for(int iIdx=0; iIdx<tabResultSetSetters.size(); iIdx++) {
			ptrSelect->fetch(iIdx+iSkip,dmNew);
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
