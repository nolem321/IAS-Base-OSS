/*
 * File: IAS-DataModelLib/src/dm/Impl/Type.h
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
#ifndef _IAS_DM_Impl_TYPE_H_
#define _IAS_DM_Impl_TYPE_H_

#include "../Type.h"
#include <unordered_map>

#include "../../dm/Impl/DataObject.h"
#include "../../dm/Impl/MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {

class DataFactory;

/*************************************************************************/
class Type : public virtual ::IAS::DM::Type {
public:

	typedef DataAllocator<DataObject>::PtrHolder PtrHolder;

	virtual ~Type() throw();

	virtual const String getName() const;
	virtual const String getURI()  const;
	virtual const String getFullName()  const;

	virtual const String getDescription()  const;
	virtual void setDescription(const String& strDescription);

	virtual void setBaseType(const ::IAS::DM::Type* pBaseType);
    virtual const ::IAS::DM::Type* getBaseType() const;

    virtual bool isAssignableTo(const ::IAS::DM::Type* pType) const;

    virtual bool isRootType() const;
    virtual bool isNSElementsType() const;

    virtual bool equals(const ::IAS::DM::Type *pType) const;

    virtual IAS::DM::DataObject* createDataObject() const;
	virtual IAS::DM::DataObject* createDataObject(const char*  sValue) const;
    virtual IAS::DM::DataObject* createDataObject(const String& strValue) const;
    virtual IAS::DM::DataObject* createDataObject(int iValue) const;
    virtual IAS::DM::DataObject* createDataObject(bool bValue) const;
    virtual IAS::DM::DataObject* createDataObject(Float fValue) const;
    virtual IAS::DM::DataObject* createDataObject(const IAS::Time& tsValue) const;
    virtual IAS::DM::DataObject* createDataObject(const IAS::Date& tsValue) const;
    virtual IAS::DM::DataObject* createDataObject(const IAS::DateTime& tsValue) const;

	virtual IAS::DM::DataObject* createDataObject(const IAS::DM::DataObject* pDataObject) const;

    static ::IAS::DM::Type* Create(const String& strURI,
									const String& strName,
									::IAS::DM::Type::Types iType = DataObjectType,
									const ::IAS::DM::Type* pBaseType=NULL);

protected:

	Type( const String& strURI,
		  const String& strName,
		  const ::IAS::DM::Type *pBaseType);


	typedef std::basic_string< char,
				std::char_traits<char>,
				ModelAllocator< char >
			> StringContentBase;

	class StringContent : public StringContentBase {
		public:
		 inline StringContent(const String& other):StringContentBase(other.c_str()){}
		 operator String() const { return String(c_str()); };
	};


	StringContent strName;
	StringContent strURI;
	StringContent strDescription;

	const ::IAS::DM::Type*  pBaseType;


	void setIsNSElementsType(bool bIsNSElementsType);

	virtual DataObject* createDataObjectImpl() const =0;

private:
	bool bIsNSElementsType;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_TYPE_H_ */
