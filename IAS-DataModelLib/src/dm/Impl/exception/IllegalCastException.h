/*
 * File: IAS-DataModelLib/src/dm/Impl/exception/IllegalCastException.h
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

#ifndef _IAS_DM_Impl_Exception_IllegalCastException_H_
#define _IAS_DM_Impl_Exception_IllegalCastException_H_


#include "../../../dm/IllegalCastException.h"

#include <commonlib/commonlib.h>


namespace IAS {
namespace DM {
class Type;
namespace Impl {

class IllegalCastException :
	public ::IAS::DM::IllegalCastException {

public:

	IllegalCastException(const ::IAS::DM::Type* pTypeSrc,
							  const ::IAS::DM::Type* pTypeDst);

	IllegalCastException(const ::IAS::DM::Type* pTypeSrc,
							   const String& strTypeDst);

	IllegalCastException(const String& strTypeSrc,
							  const String& strTypeDst);

	virtual ~IllegalCastException() throw();

	virtual const char*  getName();
};


}
}
}

#endif /*_IAS_DM_IllegalCastException_H_*/
