/*
 * File: IAS-CommonLib/src/commonlib/exception/Exception.h
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


#ifndef _IAS_Exception_H_
#define _IAS_Exception_H_

#include "../types.h"
#include <iostream>

namespace IAS{

/*************************************************************************/
/** The base exception class.
 */

 class Exception{
public:
	
	Exception();
	Exception(const String& strInfo);

	virtual ~Exception() throw();
	virtual const char*  getName();
	const String& getInfo();
	virtual String       toString();	
	virtual void  printToStream(std::ostream& os);	

	Exception& operator<< (const String& strInfo);
	Exception& operator<< (const char *sValue);
	Exception& operator<< (int iValue);
	Exception& operator<< (long iValue);
	Exception& operator<< (unsigned long iValue);
	Exception& operator<< (Float fValue);
	Exception& operator<< (void* ptrValue);

protected:
	virtual void setInfo(const char *sInfo);
	virtual void setInfo(const String& strInfo);
	virtual void appendStackTrace();
	

private:
	String strInfo;
	String strStackTrace;
};

}

#endif /*EXCEPTION_H_*/
