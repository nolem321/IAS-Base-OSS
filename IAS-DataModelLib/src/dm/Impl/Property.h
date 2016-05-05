/*
 * File: IAS-DataModelLib/src/dm/Impl/Property.h
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
#ifndef _IAS_DM_Impl_PROPERTY_H_
#define _IAS_DM_Impl_PROPERTY_H_

#include "../../dm/Property.h"

namespace IAS {
namespace DM {
namespace Impl {

/*************************************************************************/
class Property : public virtual ::IAS::DM::Property {
public:

	virtual ~Property() throw();

	virtual const String& getName() const;
	virtual const String& getDescription() const;

	virtual const ::IAS::DM::Type*   getType() const;
	virtual bool 	       isMulti() const;
	virtual bool 	       isXMLAttribute() const;
	virtual int 	       getIdx() const;

protected:
	Property(const String& strName,
			 const ::IAS::DM::Type* pType,
			 int iIdx,
			 bool bIsMulti,
			 bool bIsXMLAttribute,
			 const String& strDescription);

	//TODO (H) allocator in property strings !
	String strName;
	String strDescription;

	const ::IAS::DM::Type *pType;
	bool bIsMulti;
	bool bIsXMLAttribute;
	int  iIdx;

	friend class ::IAS::Factory<Property>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_PROPERTY_H_ */
