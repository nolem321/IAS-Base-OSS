/*
 * File: IAS-LangLib/src/lang/interpreter/exe/exception/InterpreterProgramException.h
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

#ifndef _IAS_AS_Lang_Interpreter_Exe_Exception_InterpreterProgramException_H_
#define _IAS_AS_Lang_Interpreter_Exe_Exception_InterpreterProgramException_H_


#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "InterpreterException.h"

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Exe{

/** The class. */
 class InterpreterProgramException : public InterpreterException {

public:
	InterpreterProgramException(DM::DataObject* dmValue);

	virtual ~InterpreterProgramException() throw();

	virtual const char*  getName();

	DM::DataObject* getValue()const;

protected:
	DM::DataObjectPtr dmValue;
};

}
}
}
}
#endif /*_IAS_AS_Lang_Interpreter_Exe_Exception_InterpreterProgramException_H_*/
