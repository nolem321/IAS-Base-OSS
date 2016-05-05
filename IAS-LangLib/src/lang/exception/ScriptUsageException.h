/*
 * File: IAS-LangLib/src/lang/exception/ScriptUsageException.h
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
/* ChangeLog:
 *
 */

#ifndef _IAS_AS_Lang_Exception_ScriptUsageException_H_
#define _IAS_AS_Lang_Exception_ScriptUsageException_H_


#include <commonlib/commonlib.h>
#include "lang/tools/parser/LexerIStreamWrapper.h"

namespace IAS {
namespace Lang {


/** The class. */
 class ScriptUsageException : public IAS::Exception {

public:
	ScriptUsageException();
	ScriptUsageException(const String& strInfo);
	ScriptUsageException(const String& strInfo, const String& strFile, int iLine);
	ScriptUsageException(const String& strInfo, ::IAS::Lang::Tools::Parser::LexerIStreamWrapper* pLexerIStreamWrapper);
	virtual ~ScriptUsageException() throw();

	virtual const char*  getName();
};

}
}

#endif /*_IAS_AS_Lang_Exception_ScriptUsageException_H_*/
