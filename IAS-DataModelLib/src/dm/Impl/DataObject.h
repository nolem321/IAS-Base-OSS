/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObject.h
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
#ifndef _IAS_DM_Impl_DATAOBJECT_H_
#define _IAS_DM_Impl_DATAOBJECT_H_

#include "../../dm/DataObject.h"

#include "../../dm/Impl/TypeRefFeature.h"

namespace IAS {
namespace DM {
class Property;
namespace Impl {

class Type;
/*************************************************************************/
class DataObject :
	public virtual ::IAS::DM::DataObject,
	public TypeRefFeature {
public:

	virtual ~DataObject() throw();

	virtual IAS::DM::DataObject* getDataObject(const String& strXPath);
	virtual const IAS::DM::DataObject* getDataObject(const String& strXPath) const;

	virtual IAS::DM::DataObject* getDataObject(const IAS::DM::Property* pProperty);
	virtual const IAS::DM::DataObject* getDataObject(const IAS::DM::Property* pProperty) const;

	virtual IAS::DM::DataObjectList& getList(const String& strXPath);
	virtual const IAS::DM::DataObjectList& getList(const String& strXPath)const;


	virtual IAS::DM::DataObjectList& getList(const ::IAS::DM::Property* pProperty);
	virtual const IAS::DM::DataObjectList& getList(const ::IAS::DM::Property* pProperty)const;

	virtual bool isSet(const String& strXPath)const;
	virtual bool isSet(const IAS::DM::Property* pProperty)const;

	virtual bool    getBoolean(const String& strXPath)const;
	virtual int     getInteger(const String& strXPath)const;
	virtual Float   getFloat(const String& strXPath)const;
	virtual IAS::DateTime  getDateTime(const String& strXPath)const;
	virtual IAS::Date  getDate(const String& strXPath)const;
	virtual IAS::Time  getTime(const String& strXPath)const;
	virtual String  getString(const String& strXPath)const;
	virtual void    getRaw(const String& strXPath, RawContent* pRawContent)const;

	virtual bool    getBoolean(const IAS::DM::Property* pProperty) const;
	virtual int     getInteger(const IAS::DM::Property* pProperty) const;
	virtual Float   getFloat(const IAS::DM::Property* pProperty) const;
	virtual IAS::DateTime  getDateTime(const IAS::DM::Property* pProperty) const;
	virtual IAS::Date  getDate(const IAS::DM::Property* pProperty) const;
	virtual IAS::Time  getTime(const IAS::DM::Property* pProperty) const;
	virtual String  getString(const IAS::DM::Property* pProperty)const;
	virtual void    getRaw(const Property* pProperty, RawContent* pRawContent)const;

	virtual String  toString() const;
	virtual bool    toBoolean() const;
	virtual int     toInteger() const;
	virtual Float   toFloat() const;
	virtual IAS::DateTime  toDateTime() const;
	virtual IAS::Date  toDate() const;
	virtual IAS::Time  toTime() const;
	virtual void toRaw(RawContent* pRawContent)const;

	virtual const ::IAS::DM::Type*   getType() const;

	virtual ::IAS::DM::DataObject *createDataObject(const String& strXPath);
	virtual ::IAS::DM::DataObject * createDataObject(const IAS::DM::Property* pProperty);

	virtual void setDataObject(const String& strXPath, ::IAS::DM::DataObject *pDataObject);

	virtual void  setInteger(const String& strXPath, int aValue);
	virtual void  setFloat(const String& strXPath, Float fValue);
	virtual void  setDateTime(const String& strXPath,const IAS::DateTime& tValue);
	virtual void  setDate(const String& strXPath,const IAS::Date& tValue);
	virtual void  setTime(const String& strXPath,const IAS::Time& tValue);
	virtual void  setBoolean(const String& strXPath, bool bValue);
	virtual void  setString(const String& strXPath, const String& strValue);
	virtual void  setRaw(const String& strXPath, const RawContent* pRawContent);

	virtual void setDataObject(const IAS::DM::Property* pProperty, ::IAS::DM::DataObject *pDataObject);

	virtual void  setInteger(const IAS::DM::Property* pProperty, int aValue);
	virtual void  setFloat(const IAS::DM::Property* pProperty, Float fValue);
	virtual void  setDateTime(const IAS::DM::Property* pProperty,const IAS::DateTime& tValue);
	virtual void  setDate(const IAS::DM::Property* pProperty,const IAS::Date& tValue);
	virtual void  setTime(const IAS::DM::Property* pProperty,const IAS::Time& tValue);
	virtual void  setBoolean(const IAS::DM::Property* pProperty, bool bValue);
	virtual void  setString(const IAS::DM::Property* pProperty, const String& strValue);
	virtual void  setRaw(const IAS::DM::Property* pProperty, const RawContent* pRawContent);

	virtual void unset(const String& strXPath);
	virtual void unset(const ::IAS::DM::Property* pProperty);

	virtual IAS::DM::DataObject* getParent() const;
	virtual IAS::DM::DataObject* getParentRoot() const;
	virtual void setParent(IAS::DM::DataObject* pParent);
	virtual void unsetParent();

	virtual ::IAS::DM::DataObject* duplicate() const;

	virtual void setString(const String& strValue);
	virtual void setRaw(const RawContent* pRawContent);
	virtual void setInteger(int iValue);
	virtual void setBoolean(bool bValue);
	virtual void setFloat(Float fValue);
	virtual void setDateTime(const IAS::DateTime& tValue);
	virtual void setDate(const IAS::Date& tValue);
	virtual void setTime(const IAS::Time& tValue);

	virtual void setDataObject(const IAS::DM::DataObject* pDataObject);


protected:

	DataObject(const Type *pType);

	IAS::DM::DataObject *pParent;

	friend class ::IAS::Factory<DataObject>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAOBJECT_H_ */
