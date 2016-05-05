/*
 * File: IAS-CommonLib/src/commonlib/exception/MemoryException.h
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

#ifndef _IAS_MemoryException_H_
#define _IAS_MemoryException_H_

#include "SystemException.h"

namespace IAS{

/*************************************************************************/
/** The MemoryException exception class.
 */


class MemoryException : public SystemException
{
public:
	MemoryException();
	MemoryException(int iErrno);
	virtual ~MemoryException() throw();
	
	virtual const char*  getName();
	
};

}

#endif /*SYSTEMEXCEPTION_H_*/


