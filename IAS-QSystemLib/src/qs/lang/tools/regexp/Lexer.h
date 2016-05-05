/*
 * File: IAS-QSystemLib/src/qs/lang/tools/regexp/Lexer.h
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
#ifndef _IAS_QS_Lang_Tools_RegExp_Lexer_H_
#define _IAS_QS_Lang_Tools_RegExp_Lexer_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {
namespace RegExp {

/*************************************************************************/
/** The Lexer class.
 *
 */
class Lexer{
public:

	virtual ~Lexer() throw();

	enum Token{
		T_NONE        = 0,

		T_STRING      = 1,
		T_SYMBOL      = 2,
		T_NUMBER      = 3,

		T_ARROW       = 10,
		T_COMMA       = 11,
		T_OPENPAR     = 12,
		T_CLOSEPAR    = 13,
		T_COLON       = 14,

		T_END     = 99
	};

	inline const String& getValue()const { return strValue; };

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

	Token		iToken;

	void skipBlanks();

	void handleString();
	void handleSymbol();
	void handleNumber();
	void handleEQ();

	int       iUnGet;
	bool      bQuoted;

	struct PrintableSymbolMap : std::map<Token, String>,
		InstanceFeature<PrintableSymbolMap>{
		PrintableSymbolMap();
	};

	friend class Factory<Lexer>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Lang_Tools_RegExp_Lexer_H_ */
