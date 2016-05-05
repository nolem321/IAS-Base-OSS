/*
 * File: IAS-DataModelLib/src/dm/TypeList.h
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
#ifndef _IAS_DM_TypeList_H_
#define _IAS_DM_TypeList_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {
class Type;

/*************************************************************************/
/** The class. */
//TODO remove this and create type iterator.
 class TypeList {
public:
	virtual ~TypeList(){};
	virtual const Type* at(unsigned int iIdx) const =0;

	virtual unsigned int getSize () const=0;
	virtual void insert (const Type* pType)=0;

	inline const Type* operator[] (unsigned int iIdx) const { return at(iIdx);};
};

/*************************************************************************/
}
}

#endif /* _IAS_DM_TypeList_H_ */
