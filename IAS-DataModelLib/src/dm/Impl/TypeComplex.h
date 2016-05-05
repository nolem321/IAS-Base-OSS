/*
 * File: IAS-DataModelLib/src/dm/Impl/TypeComplex.h
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
#ifndef _IAS_DM_Impl_TYPECOMPLEX_H_
#define _IAS_DM_Impl_TYPECOMPLEX_H_

#include "../../dm/Impl/Type.h"


namespace IAS {
namespace DM {
namespace Impl {

class PropertyList;

/*************************************************************************/
class TypeComplex :
	public ::IAS::DM::Impl::Type,
	public virtual ::IAS::DM::ComplexType{
public:

	virtual ~TypeComplex() throw();

	virtual const ::IAS::DM::Property*   defineProperty(const String& strName,
															const ::IAS::DM::Type* pType,
															bool bIsMulti = false,
															bool bIsXMLAttribute = false,
															const String& strDescription = "");

	virtual const IAS::DM::PropertyList& getProperties() const;


    virtual bool isDataObjectType() const;
    virtual bool isBaseTypeRestriction() const;

    virtual ::IAS::DM::Type::Types getTypeEnum() const;

    virtual ::IAS::DM::ComplexType* asComplexType();
    virtual const ::IAS::DM::ComplexType* asComplexType() const;


protected:
	TypeComplex(const String& strURI,
				  const String& strName,
				  const ::IAS::DM::Type    *pBaseType);

	virtual DataObject* createDataObjectImpl() const;

	ModelAllocator<PropertyList>::PtrHolder ptrProperties;

	friend class ::IAS::Factory<TypeComplex>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_TYPECOMPLEX_H_ */
