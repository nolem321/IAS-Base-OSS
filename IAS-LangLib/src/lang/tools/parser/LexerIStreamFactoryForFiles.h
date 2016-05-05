/*
 * File: IAS-LangLib/src/lang/tools/parser/LexerIStreamFactoryForFiles.h
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
#ifndef _IAS_Lang_Tools_Parser_LexerIStreamFactoryForFiles_H_
#define _IAS_Lang_Tools_Parser_LexerIStreamFactoryForFiles_H_

#include "LexerIStreamWrapper.h"

namespace IAS {
namespace Lang {
namespace Tools {
namespace Parser {

/*************************************************************************/
/** The LexerIStreamFactoryForFiles class.
 *
 */
class LexerIStreamFactoryForFiles : public ::IAS::Lang::Tools::Parser::LexerIStreamFactory {
public:

	virtual ~LexerIStreamFactoryForFiles() throw();

	virtual LexerIStreamWrapper* createLexerIStream(const String& strObjectName)const;

	InputFile* findAndOpenFile(const String& strName)const;
	void setSearchPath(const StringList& lstSourcePath);

protected:
	LexerIStreamFactoryForFiles();

	StringList lstSourcePath;

	friend class ::IAS::Factory<LexerIStreamFactoryForFiles>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Tools_Parser_LexerIStreamFactoryForFiles_H_ */
