/*
 * File: IAS-LangLib/src/lang/interpreter/exe/exception/InterpreterRuntimeException.h
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

#ifndef _IAS_AS_Lang_Interpreter_Exe_Exception_InterpreterRuntimeException_H_
#define _IAS_AS_Lang_Interpreter_Exe_Exception_InterpreterRuntimeException_H_


#include <commonlib/commonlib.h>
#include "InterpreterProgramException.h"

#include <org/invenireaude/lang/builtin/RuntimeException.h>
#include <org/invenireaude/lang/builtin/DataFactory.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Exe{
/** The class. */
 class InterpreterRuntimeException : public InterpreterProgramException {

public:

	InterpreterRuntimeException(org::invenireaude::lang::builtin::RuntimeException* dmRuntimeException, const String& strInfo);

	virtual void setStatementSource(const String& strSource, const String& strName);

	virtual ~InterpreterRuntimeException() throw();

	virtual const char*  getName();
};

}
}
}
}

#endif /*_IAS_AS_Lang_Interpreter_Exe_Exception_InterpreterRuntimeException_H_*/
