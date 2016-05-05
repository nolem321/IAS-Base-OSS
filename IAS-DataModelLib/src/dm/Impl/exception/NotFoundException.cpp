/*
 * File: IAS-DataModelLib/src/dm/Impl/exception/NotFoundException.cpp
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
#include "../../../dm/Impl/exception/NotFoundException.h"
#include <commonlib/commonlib.h>

#include "../../../dm/Impl/Type.h"

namespace IAS{
namespace DM {
namespace Impl {

/*************************************************************************/
NotFoundException::NotFoundException()throw(){
	IAS_TRACER;
}
/*************************************************************************/
NotFoundException::NotFoundException(const String& strInfo)throw(){
	IAS_TRACER;

	this->setInfo(strInfo);
}

/*************************************************************************/
NotFoundException::~NotFoundException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* NotFoundException::getName(){
	IAS_TRACER;
	return "NotFoundException";
}


/*************************************************************************/

} /* namespace Impl */
} /* namespace DM */
} /* namespace IAS */
