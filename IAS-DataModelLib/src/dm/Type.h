/*
 * File: IAS-DataModelLib/src/dm/Type.h
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
#ifndef _IAS_DM_TYPE_H_
#define _IAS_DM_TYPE_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {

class DataObject;
class Property;
class PropertyList;

class Type;

/*************************************************************************/
/** Complex type interface. */
 class ComplexType{
public:
	virtual ~ComplexType()throw(){};

	virtual const Property*  defineProperty(const String& strName,
											   const Type* pType,
											   bool bIsMulti = false,
											   bool bIsXMLAttribute = false,
											   const String& strDescription = "") = 0;

	virtual const PropertyList& getProperties()const =0;
};

/*************************************************************************/
/** Type interface. This object represents a data type.*/
 class Type {
public:

	/** Type family ids. */

	enum Types{
	    OtherTypes = 0,
	    BooleanType,
	    FloatType,
	    IntegerType,
	    DateTimeType,
	    DateType,
	    TimeType,
	    DataObjectType,
	    TextType,
		RawType,
	    AnyType
	   };

	virtual ~Type() throw(){};

	/** Creates a data object. */
	virtual DataObject* createDataObject() const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(const char*  sValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(const String& strValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(int   iValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(bool  bValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(Float iValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(const IAS::Date& tValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(const IAS::Time& tValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(const IAS::DateTime& tValue) const = 0;

	/** Creates a data object and initializes it to a given value. */
	virtual DataObject* createDataObject(const DataObject* pDataObject) const = 0;

	/** Returns the type name. */
	virtual const String getName() const = 0;

	/** Returns the type URI. */
	virtual const String getURI()  const = 0;

	/** Returns the type URI#Name */
	virtual const String getFullName()  const = 0;

	/** Returns the type description */
	virtual const String getDescription()  const = 0;

	/** Sets the type description */
	virtual void setDescription(const String& strDescription) = 0;

	/** Sets a parent type. */
	virtual void setBaseType(const Type* pBaseType) = 0;

	/** Returns the parent type. */
    virtual const Type* getBaseType() const = 0;

    /** Checks if the type can be assigned to the parameter. */
    virtual bool isAssignableTo(const Type* pType) const = 0;

    /** Returns true if the type is a data object. */
    virtual bool isDataObjectType() const = 0;

    /** Checks if the type is a root type (has no parents). */
    virtual bool isRootType() const = 0;

    /** Returns true if the type is a root elements holder for this URI. */
    virtual bool isNSElementsType() const = 0;

    /** Returns true if the type is a restriction. */
    virtual bool isBaseTypeRestriction() const = 0;

    /** Returns true if the types are the same. */
    virtual bool equals(const Type *pType) const = 0;

    /** Returns the type id.*/
    virtual Type::Types getTypeEnum() const = 0;

    /** Returns true if the type is a complex type. */
    virtual ComplexType* asComplexType() = 0;

    /** Type check and a cast. */
    virtual const ComplexType* asComplexType() const = 0;

    /** Set maximum lenght */
    typedef unsigned int MaxLenghtType;
    virtual void setRestrictionMaxLength(const MaxLenghtType iMaxLength)=0;
    virtual MaxLenghtType getRestrictionMaxLenght()const=0;

    static const MaxLenghtType CDftMaxLength;

};

 /*************************************************************************/
}
}

#endif /* _IAS_DM_TYPE_H_ */
