/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectComplex.h
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
#ifndef _IAS_DM_Impl_DATAOBJECTCOMPLEX_H_
#define _IAS_DM_Impl_DATAOBJECTCOMPLEX_H_

#include "../../dm/Impl/DataObject.h"
#include "../../dm/Impl/DataObjectList.h"
#include "../../dm/Impl/MemoryManager.h"
#include "commonlib/commonlib.h"


namespace IAS {
namespace DM {
namespace Impl {

class Type;
/*************************************************************************/
class DataObjectComplex :
	public ::IAS::DM::Impl::DataObject {
public:

	virtual ~DataObjectComplex() throw();

	virtual const IAS::DM::DataObject* getDataObject(const IAS::DM::Property* pProperty)const;
	virtual bool isSet(const IAS::DM::Property* pProperty)const;

	virtual const IAS::DM::DataObjectList& getList(const ::IAS::DM::Property* pProperty)const;

	virtual ::IAS::DM::DataObject * createDataObject(const IAS::DM::Property* pProperty);

	virtual void setDataObject(const IAS::DM::Property* pProperty,
								  ::IAS::DM::DataObject *pDataObject);

	virtual void  setInteger(const IAS::DM::Property* pProperty, int aValue);
	virtual void  setFloat(const IAS::DM::Property* pProperty, Float fValue);
	virtual void  setDate(const IAS::DM::Property* pProperty,const IAS::Date& tValue);
	virtual void  setTime(const IAS::DM::Property* pProperty,const IAS::Time& tValue);
	virtual void  setDateTime(const IAS::DM::Property* pProperty,const IAS::DateTime& tValue);
	virtual void  setBoolean(const IAS::DM::Property* pProperty, bool bValue);
	virtual void  setString(const IAS::DM::Property* pProperty, const String& strValue);
	virtual void  setRaw(const IAS::DM::Property* pProperty, const RawContent* pRawContent);

	virtual void setDataObject(const IAS::DM::DataObject* pDataObject);

	virtual void unset(const ::IAS::DM::Property* pProperty);

	virtual bool    getBoolean(const IAS::DM::Property* pProperty) const;
	virtual int     getInteger(const IAS::DM::Property* pProperty) const;
	virtual Float   getFloat(const IAS::DM::Property* pProperty) const;
	virtual IAS::DateTime  getDateTime(const IAS::DM::Property* pProperty) const;
	virtual String  getString(const IAS::DM::Property* pProperty) const;
	virtual void    getRaw(const IAS::DM::Property* pProperty, RawContent* pRawContent)const;

	virtual bool    equals(const IAS::DM::DataObject* dmValue)const;

protected:
	DataObjectComplex(const Type *pType);
	void init();

	struct Entry{
		Entry():bSet(false){};
		bool bSet;

		/* used as union, no polymorphism for the performance sake  */
		DataObjectPtr               ptrDataObject;

		//TODO hack !!
		DataAllocator<DataObjectList>::RefCountingPtr   ptrDataObjectList;
	};

	typedef std::vector<Entry, DataAllocator<Entry> > ContentTab;

	ContentTab tabDataObjects;

	void clear();

	friend class ::IAS::Factory<DataObjectComplex>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAOBJECTCOMPLEX_H_ */

