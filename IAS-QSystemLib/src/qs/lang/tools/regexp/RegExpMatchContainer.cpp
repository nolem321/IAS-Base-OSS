/*
 * File: IAS-QSystemLib/src/qs/lang/tools/regexp/RegExpMatchContainer.cpp
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
#include "RegExpMatchContainer.h"
#include <qs/log/LogLevel.h>

#include "RegExpMatch.h"
#include "Lexer.h"

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {
namespace RegExp {

/*************************************************************************/
RegExpMatchContainer::RegExpMatchContainer(const String& strSpec, const DM::DataFactory* pDataFactory){
	IAS_TRACER;

	parse(strSpec,pDataFactory);
}
/*************************************************************************/
RegExpMatchContainer::~RegExpMatchContainer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void RegExpMatchContainer::addMatch(RegExpMatch* pMatch){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pMatch);
	tabMatches.push_back(pMatch);
}
/*************************************************************************/
bool RegExpMatchContainer::match(const String& strValue, DM::DataObjectPtr& dm)const{
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo()," match: "<<strValue<<tabMatches.size());

	for(MatchVector::const_iterator it=tabMatches.begin();
			it != tabMatches.end(); it++){

		if( (*it)->match(strValue,dm))
			return true;
	}

	return false;
}
/*************************************************************************/
void RegExpMatchContainer::parse(const String& strSpec, const DM::DataFactory* pDataFactory){
	IAS_TRACER;

	IAS_DFT_FACTORY<Lexer>::PtrHolder ptrLexer(IAS_DFT_FACTORY<Lexer>::Create(strSpec));

	do{

		ptrLexer->assetNext(Lexer::T_STRING);
		String strRegExp(ptrLexer->getValue());

		ptrLexer->assetNext(Lexer::T_ARROW);

		ptrLexer->assetNext(Lexer::T_SYMBOL);
		String strTypeName(ptrLexer->getValue());

		ptrLexer->assetNext(Lexer::T_COLON);

		ptrLexer->assetNext(Lexer::T_STRING);
		String strTypeURI(ptrLexer->getValue());

		const DM::Type* pType = pDataFactory->getType(strTypeURI,strTypeName);

		IAS_DFT_FACTORY<RegExpMatch>::PtrHolder ptrMatch;
		try{
			ptrMatch=IAS_DFT_FACTORY<RegExpMatch>::Create(strRegExp,pType);
		}catch(std::exception& e){
			IAS_THROW(BadUsageException(strRegExp));
		}

		ptrLexer->assetNext(Lexer::T_OPENPAR);

		bool bFirst=true;

		while(ptrLexer->nextToken() != Lexer::T_CLOSEPAR){

			if(!bFirst){
				ptrLexer->assetToken(Lexer::T_COMMA);
				ptrLexer->nextToken();
			}

			ptrLexer->assetToken(Lexer::T_NUMBER);
			unsigned int id = TypeTools::StringToInt(ptrLexer->getValue());

			ptrLexer->assetNext(Lexer::T_ARROW);
			ptrLexer->assetNext(Lexer::T_SYMBOL);

			String strXPath(ptrLexer->getValue());

			ptrMatch->addXPath(id,strXPath);

			bFirst=false;
		}

		tabMatches.push_back(ptrMatch.pass());

		if(ptrLexer->nextToken() == Lexer::T_END)
			return;

		ptrLexer->assetNext(Lexer::T_COMMA);

	}while(true);
}
/*************************************************************************/
}
}
}
}
}
