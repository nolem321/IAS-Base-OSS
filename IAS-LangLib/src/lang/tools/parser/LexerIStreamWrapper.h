/*
 * File: IAS-LangLib/src/lang/tools/parser/LexerIStreamWrapper.h
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
#ifndef _IAS_AS_Lang_Tools_Parser_LEXERISTREAMWRAPPER_H_
#define _IAS_AS_Lang_Tools_Parser_LEXERISTREAMWRAPPER_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Tools {
namespace Parser {

/*************************************************************************/
/** The class. */
 class LexerLocation {
public:

	virtual ~LexerLocation(){};
	int getLineNo()const;
	const String& getName() const;
	String asString() const;

protected:
	void setName(const String& strName);
	String strName;
	int    iLineNo;
};

/*************************************************************************/
/** The class. */
 class LexerIStreamWrapper : public LexerLocation{
public:

	int  getChar();
	void ungetChar();
	bool isEOF();

protected:
	virtual std::istream& getIS()=0;

};

/*************************************************************************/
/** The class. */
 class LexerFileIStreamWrapper : public LexerIStreamWrapper{
public:

	virtual ~LexerFileIStreamWrapper() throw();

	static LexerFileIStreamWrapper* Create(InputFile* pFile);
	static LexerFileIStreamWrapper* Create(const String& strFileName);

	virtual std::istream& getIS();

protected:

	LexerFileIStreamWrapper(InputFile* pFile) throw();

	IAS_DFT_FACTORY<InputFile>::PtrHolder ptrFile;

	std::istream& is;

	friend class IAS::Factory<LexerFileIStreamWrapper>;
};
/*************************************************************************/
/** The class. */
 class LexerStringIStreamWrapper : public LexerIStreamWrapper{
public:

	virtual ~LexerStringIStreamWrapper() throw();

	static LexerStringIStreamWrapper* Create(const String& strBuffer);

	virtual std::istream& getIS();

protected:

	LexerStringIStreamWrapper(const String& strBuffer) throw();

	StringStream ssBuffer;

	friend class IAS::Factory<LexerStringIStreamWrapper>;
};
/*************************************************************************/

/*************************************************************************/
class LexerIStreamFactory {
 public:
	virtual ~LexerIStreamFactory(){};
 	virtual LexerIStreamWrapper* createLexerIStream(const String& strObjectName)const=0;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Tools_Parser_LEXERISTREAMWRAPPER_H_ */
