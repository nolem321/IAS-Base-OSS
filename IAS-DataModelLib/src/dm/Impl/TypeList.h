/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeList.h
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
#ifndef _IAS_DM_Impl_TypeList_H_
#define _IAS_DM_Impl_TypeList_H_

#include "../../dm/TypeList.h"

#include <commonlib/commonlib.h>

#include <vector>

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
class TypeList : public virtual ::IAS::DM::TypeList{
public:

	virtual ~TypeList() throw();

	virtual const ::IAS::DM::Type* at(unsigned int iIdx) const;

	virtual unsigned int getSize () const;
	virtual void insert (const ::IAS::DM::Type* pType);


protected:
	TypeList();

	typedef std::vector<const DM::Type*> TypesPtrVector;
	TypesPtrVector  lstTypes;

	friend class ::IAS::Factory<TypeList>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_TypeList_H_ */
