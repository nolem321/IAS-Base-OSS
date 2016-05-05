/*
 * File: IAS-DataModelLib/src/dm/DataObject.h
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
#ifndef _IAS_DM_DATAOBJECT_H_
#define _IAS_DM_DATAOBJECT_H_

#include <commonlib/commonlib.h>
#include <time.h>

#include "../dm/Impl/MemoryManager.h"

namespace IAS {
namespace DM {

class DataObjectList;
class Type;
class Property;

/*************************************************************************/
class DataObject;
class DataFactory;

typedef AllocatorFactory<DataObject, Impl::MemoryManager::GetAllocatorForData>::RefCountingPtr DataObjectPtr;

typedef ::IAS::Buffer RawContent;

/*************************************************************************/

/** The class. */
 class DataObject : public virtual ::IAS::RefCountingPointee {
public:

	virtual ~DataObject() throw(){};


	virtual DataObject* getDataObject(const String& strXPath)=0;
	virtual DataObject* getDataObject(const Property* pProperty)= 0;

	virtual const DataObject* getDataObject(const String& strXPath) const =0;
	virtual const DataObject* getDataObject(const Property* pProperty) const = 0;

	virtual bool isSet(const String& strXPath)const=0;
	virtual bool isSet(const Property* pProperty)const = 0;

	virtual DataObjectList& getList(const Property* pProperty)=0;
	virtual DataObjectList& getList(const String& strXPath)=0;

	virtual const DataObjectList& getList(const Property* pProperty) const =0;
	virtual const DataObjectList& getList(const String& strXPath) const=0;


	virtual bool    getBoolean(const String& strXPath)const=0;
	virtual int     getInteger(const String& strXPath)const=0;
	virtual Float   getFloat(const String& strXPath)const=0;
	virtual IAS::DateTime  getDateTime(const String& strXPath)const=0;
	virtual IAS::Time  getTime(const String& strXPath)const=0;
	virtual IAS::Date  getDate(const String& strXPath)const=0;
	virtual String  getString(const String& strXPath)const=0;
	virtual void    getRaw(const String& strXPath, RawContent* pRawContent)const=0;


	virtual bool    getBoolean(const Property* pProperty)const=0;
	virtual int     getInteger(const Property* pProperty)const=0;
	virtual Float   getFloat(const Property* pProperty)const=0;
	virtual IAS::DateTime  getDateTime(const Property* pProperty)const=0;
	virtual IAS::Date  getDate(const Property* pProperty)const=0;
	virtual IAS::Time  getTime(const Property* pProperty)const=0;
	virtual String  getString(const Property* pProperty)const=0;
	virtual void    getRaw(const Property* pProperty, RawContent* pRawContent)const=0;

	virtual void setDataObject(const String& strXPath, DataObject *pDataObject)=0;

	virtual void  setInteger(const String& strXPath, int aValue)=0;
	virtual void  setFloat(const String& strXPath, Float fValue)=0;

	virtual void  setDateTime(const String& strXPath,const IAS::DateTime& tsValue)=0;
	virtual void  setDate(const String& strXPath,const IAS::Date& tsValue)=0;
	virtual void  setTime(const String& strXPath,const IAS::Time& tsValue)=0;

	virtual void  setBoolean(const String& strXPath, bool bValue)=0;
	virtual void  setString(const String& strXPath, const String& strValue)=0;
	virtual void  setRaw(const String& strXPath, const RawContent* pRawContent)=0;

	virtual void setDataObject(const Property* pProperty, DataObject *pDataObject)=0;

	virtual void  setInteger(const Property* pProperty, int aValue)=0;
	virtual void  setFloat(const Property* pProperty, Float fValue)=0;
	virtual void  setDateTime(const Property* pProperty,const IAS::DateTime& tsValue)=0;
	virtual void  setDate(const Property* pProperty, const IAS::Date& tsValue)=0;
	virtual void  setTime(const Property* pProperty, const IAS::Time& tsValue)=0;
	virtual void  setBoolean(const Property* pProperty, bool bValue)=0;
	virtual void  setString(const Property* pProperty, const String& strValue)=0;
	virtual void  setRaw(const Property* pProperty, const RawContent* pRawContent)=0;

	virtual String  toString()   const = 0;
	virtual bool    toBoolean()  const = 0;
	virtual int     toInteger()  const = 0;
	virtual Float   toFloat()    const = 0;
	virtual IAS::DateTime  toDateTime() const = 0;
	virtual IAS::Date      toDate() const = 0;
	virtual IAS::Time      toTime() const = 0;
	virtual void toRaw(RawContent* pRawContent)const=0;

	virtual const Type*   getType() const =0;

	virtual DataObject* getParent() const =0;
	virtual DataObject* getParentRoot() const =0;

	virtual DataObject* createDataObject(const String& strXPath)=0;
	virtual DataObject* createDataObject(const Property* pProperty)=0;


	virtual DataObject* duplicate() const =0;

	virtual void setString(const String& strValue)=0;
	virtual void setRaw(const RawContent* pRawContent)=0;
	virtual void setInteger(int iValue)=0;
	virtual void setBoolean(bool bValue)=0;
	virtual void setFloat(Float fValue)=0;
	virtual void setDateTime(const IAS::DateTime& fValue)=0;
	virtual void setDate(const IAS::Date& fValue)=0;
	virtual void setTime(const IAS::Time& fValue)=0;
	virtual void setDataObject(const IAS::DM::DataObject* pDataObject)=0;

	//virtual void setString(const String& strXPath, const String& strValueData)=0;
	//virtual void setString(const Property* pProperty, const String& strValue)=0;

	virtual void unset(const String& strXPath)=0;
	virtual void unset(const Property* pProperty)=0;

protected:
	virtual void setParent(DataObject* pParent)=0;
	virtual void unsetParent()=0;

	//consty ??? virtual DataObjectList* getList(String& strXPath)const =0;

	friend class DataObjectImplProxy;

};

/*************************************************************************/

/** The class. */
 class DataObjectImplProxy {
	public:

	static inline void SetParent(DataObject* pParent,DataObject* pChild){
		pChild->setParent(pParent);
	}

	static inline void UnsetParent(DataObject* pChild){
		pChild->unsetParent();
	}
};

/*************************************************************************/

}
}

#endif /* _IAS_DM_DATAOBJECT_H_ */
