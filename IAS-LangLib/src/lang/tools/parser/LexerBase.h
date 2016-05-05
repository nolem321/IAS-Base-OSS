/*
 * File: IAS-LangLib/src/lang/tools/parser/LexerBase.h
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
#ifndef _IAS_AS_Lang_Tools_Parser_LEXERBASE_H_
#define _IAS_AS_Lang_Tools_Parser_LEXERBASE_H_


#include <commonlib/commonlib.h>
#include <stack>

#include "LexerIStreamWrapper.h"
#include "SourceLocation.h"

namespace IAS {
namespace Lang {
namespace Tools {
namespace Parser {

class LexerIStreamFactory;
class LexerLocation;
class ISourceLocationStore;

/*************************************************************************/
/** The class. */
 class LexerBase {
public:

	template <class T> class TokenInfo{
		public:

			TokenInfo():bHasInfo(false){};

			const String& getInfo() const { return strInfo; };
			T getToken() const { return iToken; };

			inline void setToken(T iToken, bool bHasInfo=false) { this->iToken=iToken; this->bHasInfo=bHasInfo;};
			inline void setInfo(const String& strInfo) { this->strInfo=strInfo;};
			inline void addChar(char c) { strInfo+=c;};
			inline void clearInfo() { strInfo.clear(); bHasInfo=false; };
			inline bool hasInfo() const { return bHasInfo; }

		protected:
			String strInfo;
			T 	   iToken;
			bool  bHasInfo;
	};

	virtual ~LexerBase() throw();


	void openObject(const String& strObjectName);

	const LexerLocation* getLocation() const;
	SourceLocation       getCachedLocation()const;

protected:


	LexerIStreamWrapper* getActiveWrapper();

	LexerBase(LexerIStreamFactory* pLexerIStreamFactory,
			  ISourceLocationStore *pSourceLocationStore);

	int iLineNo;

	void pushIStreamWrapper(LexerIStreamWrapper* pWrapper);
	void popIStreamWrapper();

	int getStackSize()const;

private:

	ISourceLocationStore *pSourceLocationStore;

	std::stack<LexerIStreamWrapper*>          stackStreams;

	IAS_DFT_FACTORY<LexerIStreamWrapper>::PtrHoldersCollection phcStreams;
	IAS_DFT_FACTORY<LexerIStreamFactory>::PtrHolder ptrLexerIStreamFactory;

	typedef HashMapWithStringKey<bool> ProcessedObjectsMap;
	ProcessedObjectsMap				   hmProcessedObjects;

	std::stack<SourceLocation::SourceID>       stackSourceID;

	friend class ::IAS::Factory<LexerBase>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Tools_Parser_LEXERBASE_H_ */
