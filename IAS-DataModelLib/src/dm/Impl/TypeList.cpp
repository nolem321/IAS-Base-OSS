/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeList.cpp
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
#include "../../dm/Impl/TypeList.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
TypeList::TypeList(){
	IAS_TRACER;
}
/*************************************************************************/
TypeList::~TypeList() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const ::IAS::DM::Type* TypeList::at(unsigned int iIdx) const{
	IAS_TRACER;

	if(iIdx < 0 || iIdx > lstTypes.size() - 1)
			IAS_THROW(ItemNotFoundException("TypeList::at"));

	return lstTypes[iIdx];
}
/*************************************************************************/
unsigned int TypeList::getSize() const{
	IAS_TRACER;
	return lstTypes.size();
}
/*************************************************************************/
void TypeList::insert(const ::IAS::DM::Type* pType){
	IAS_TRACER;
	return lstTypes.push_back(pType);
}
/*************************************************************************/
}
}
}
