/*
 * File: IAS-CommonLib/src/commonlib/exception/ItemNotFoundException.h
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

#ifndef _IAS_ItemNotFoundException_H_
#define _IAS_ItemNotFoundException_H_

#include "Exception.h"

namespace IAS{

/*************************************************************************/
/** The ItemNotFoundException exception class.
 */

class ItemNotFoundException : public IAS::Exception
{
public:
	ItemNotFoundException();
	ItemNotFoundException(const String& strItemName);
	virtual ~ItemNotFoundException() throw();
	
	virtual const char*  getName();

};

}

#endif /*ITEMNOTFOUNDEXCEPTION_H_*/
