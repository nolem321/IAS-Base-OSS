/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Lexer.h
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
#ifndef _IAS_QS_Proc_Workers_DS_Wrapper_Lexer_H_
#define _IAS_QS_Proc_Workers_DS_Wrapper_Lexer_H_

#include <commonlib/commonlib.h>

#include "Wrapper.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
/** The Lexer class.
 *
 */
class Lexer{
public:

	virtual ~Lexer() throw();

	enum Token{
		T_NONE        = 0,

		T_SYMBOL      = 1,

		T_ARROW       = 10,
		T_COMMA       = 11,
		T_OPENPAR     = 12,
		T_CLOSEPAR    = 13,
		T_QUESTION_MARK = 14,
		T_COLON         = 15,

		T_SELECT  = 20,
		T_INSERT  = 21,
		T_UPDATE  = 22,
		T_DELETE  = 23,
		T_CALL    = 24,

		T_ONCE    = 50,
		T_INTO    = 51,
		T_ARRAY   = 52,
		T_MAP     = 53,
		T_FROM    = 54,
		T_WHERE   = 55,
		T_SET     = 56,
		T_AND     = 57,
		T_OR      = 58,

		T_PAGE     = 59,
		T_DISTINCT = 60,

		T_EQ      = 70,
		T_DIFF    = 71,
		T_GT      = 72,
		T_LE      = 73,
		T_GT_EQ   = 74,
		T_LE_EQ   = 75,
		T_LIKE    = 76,
		T_IN      = 77,
		T_FOR     = 77,

		T_END     = 99
	};

	inline const String& getValue()const { return strValue; };
	inline const String& getXPathValue()const { return strXPathValue; };

	Token        nextToken();

	Token        getToken()const{ return iToken;}

	void         assetNext(Token iToken);
	void         assetToken(Token iToken);

	inline bool  isToken(Token iToken)const { return this->iToken == iToken; }

	int          getLine()const { return iLine; }

	void         unGet();

	bool isQuoted()const { return bQuoted; }

protected:
	Lexer(const String& strText);

	unsigned int iLine;
	const char* sCur;

	String      strValue;
	String      strXPathValue;

	Token		iToken;

	void skipBlanks();

	void handleSymbol();
	void handleQSymbol();
	void handleEQ();
	void handleLt();
	void handleGt();

	struct SymbolMap : HashMapWithStringKey<Token>,
		InstanceFeature<SymbolMap>{
		SymbolMap();

		Token convert(const String& strValue);
	};

	struct PrintableSymbolMap : std::map<Token, String>,
		InstanceFeature<PrintableSymbolMap>{
		PrintableSymbolMap();
	};

	int       iUnGet;
	bool      bQuoted;

	friend class Factory<Lexer>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Proc_Workers_DS_Wrapper_Lexer_H_ */
