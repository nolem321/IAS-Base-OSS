/*
 * File: IAS-LangLib/src/lang/interpreter/proc/exception/ProcessorException.h
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

#ifndef _IAS_AS_Lang_Interpreter_Proc_Exception_ProcessorException_H_
#define _IAS_AS_Lang_Interpreter_Proc_Exception_ProcessorException_H_


#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {

/*************************************************************************/
/** The class. */
 class ProcessorException : public IAS::Exception {

public:
	ProcessorException();
	ProcessorException(const String& strInfo);

	virtual ~ProcessorException() throw();

	virtual const char*  getName();
};
/*************************************************************************/

}
}
}
}

#endif /*_IAS_AS_Lang_Exception_ProcessorException_H_*/
