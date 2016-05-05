/*
 * File: IAS-QSystemLib/src/qs/api/exception/EndOfDataException.h
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

#ifndef _IAS_QS_API_EndOfDataException_H_
#define _IAS_QS_API_EndOfDataException_H_

#include "Exception.h"

namespace IAS{
namespace QS{
namespace API{

/*************************************************************************/
/** The EndOfDataException exception class.
 */

class EndOfDataException : public ::IAS::QS::API::Exception {

public:
	EndOfDataException();
	EndOfDataException(const String& strItemName);
	virtual ~EndOfDataException() throw();
	
	virtual const char*  getName();

};

}
}
}

#endif /*_IAS_QS_API_EndOfDataException_H_*/
