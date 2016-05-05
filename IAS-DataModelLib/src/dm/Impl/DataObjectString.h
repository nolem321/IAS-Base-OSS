/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectString.h
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
#ifndef _IAS_DM_Impl_DATAOBJECTSTRING_H_
#define _IAS_DM_Impl_DATAOBJECTSTRING_H_

#include "../../dm/Impl/DataObjectBasic.h"
#include "../../dm/Impl/MemoryManager.h"

namespace IAS {
namespace DM {
namespace Impl {

class Type;

/*************************************************************************/
class DataObjectString :
	public ::IAS::DM::Impl::DataObjectBasic{
public:

	virtual ~DataObjectString() throw();

	virtual void setString(const ::IAS::String& strValue);
	virtual void setInteger(int iValue);
	virtual void setBoolean(bool bValue);
	virtual void setFloat(Float fValue);
	virtual void setDateTime(const IAS::DateTime& tValue);
	virtual void setDate(const IAS::Date& tValue);
	virtual void setTime(const IAS::Time& tValue);
	virtual void setDataObject(const IAS::DM::DataObject* pDataObject);

	virtual ::IAS::String toString()const;
	virtual bool    toBoolean()const;
	virtual int     toInteger()const;
	virtual Float   toFloat()const;

	virtual IAS::Date  toDate()const;
	virtual IAS::Time  toTime()const;
	virtual IAS::DateTime  toDateTime()const;

protected:
	DataObjectString(const Type *pType);


	typedef std::basic_string< char,
				std::char_traits<char>,
				DataAllocator< char >
			> StringContentBase;

	class StringContent : public StringContentBase {
		public:
		 inline StringContent(const String& other):StringContentBase(other.c_str()){}
		 operator String() const { return String(c_str()); };
	};


	StringContent strValue;

	friend class ::IAS::Factory<DataObjectString>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAOBJECTSTRING_H_ */
