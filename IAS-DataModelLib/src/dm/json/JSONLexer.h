/*
 * File: IAS-DataModelLib/src/dm/json/JSONLexer.h
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
#ifndef _IAS_DM_JSON_LEXER_H_
#define _IAS_DM_JSON_LEXER_H_

#include <commonlib/commonlib.h>

#include <libxml/xmlreader.h>

#include "../../dm/json/exception/JSONHelperException.h"

namespace IAS {
namespace DM {
namespace JSON {

/*************************************************************************/
/** The class. */
 class JSONLexer {
public:

	virtual ~JSONLexer() throw();

	enum Token{
		T_None              = 0,
		T_StringValue       = 1,
		T_NumericValue      = 2,
		T_BooleanValue      = 4,
		T_Null              = 5,
		T_LeftBrace			= '{',
		T_RightBrace        = '}',
		T_LeftBracket       = '[',
		T_RightBracket      = ']',
		T_Colon             = ':',
		T_Comma             = ','
	};

	Token  getToken()const { return iToken; };

	const String& getCharValue()const    { return strValue; };

	Token next();

	void  asset(Token iToken);

	inline Token assetAndNext(Token iToken){ asset(iToken); return next(); }

protected:

	JSONLexer(std::istream& is);
	std::istream& is;

	Token   iToken;
	String  strValue;

	enum State{
		S_Start,
		S_String,
		S_StringExcape,
		S_Number,
		S_Symbol
	};

	State iState;

	void nextChar();
	void skipWhiteChars();
	void handleStart();
	void handleString();
	void handleNumber();
	void handleSymbol();

	char cCurrent;

	int iLineNo;

	friend class ::IAS::Factory<JSONLexer>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_JSON_LEXER_H_ */
