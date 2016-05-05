/*
 * File: IAS-ServiceManagerExe/src/sm/cmdline/ParameterException.h
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
#ifndef _IAS_SM_CmdLine_ParameterException_H_
#define _IAS_SM_CmdLine_ParameterException_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace SM {
namespace CmdLine {

/*************************************************************************/
/** The ParameterException class.
 *
 */
class ParameterException : public ::IAS::Exception{
public:

	virtual ~ParameterException() throw();
	ParameterException(const String& strInfo)throw();

	virtual const char*  getName();
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_CmdLine_ParameterException_H_ */
