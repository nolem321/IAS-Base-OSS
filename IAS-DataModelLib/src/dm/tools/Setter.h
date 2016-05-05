/*
 * File: IAS-DataModelLib/src/dm/tools/Setter.h
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
#ifndef _IAS_DM_Tools_Setter_H_
#define _IAS_DM_Tools_Setter_H_

#include <commonlib/commonlib.h>

#include "../../dm/DataObject.h"
#include "../../dm/Type.h"

namespace IAS {
namespace DM {
namespace Tools {

/*************************************************************************/
/** The Setter class.
 *
 */
class Setter {
public:

	virtual ~Setter() throw();

	const DM::Type*       getTargetType() const;
	const DM::Type::Types getTargetTypeEnum() const;

	void setDataObject(DataObjectPtr& dm,DM::DataObject* pDMValue)const;

	void setString(DataObjectPtr& dm,const String& strValue)const;
	void setInteger(DataObjectPtr& dm,int iValue)const;
	void setFloat(DataObjectPtr& dm,Float fValue)const;
	void setBoolean(DataObjectPtr& dm,bool bValue)const;

	void setDate(DataObjectPtr& dm,const IAS::Date& tsValue)const;
	void setTime(DataObjectPtr& dm,const IAS::Time& tsValue)const;
	void setDateTime(DataObjectPtr& dm,const IAS::DateTime& tsValue)const;

	DM::DataObject* getValue(DM::DataObject* dm)const;
	const DM::DataObject* getValue(const DM::DataObject* dm)const;
	bool isSet(const DM::DataObject* dm)const;
	void unset(DM::DataObjectPtr& dm);

	DM::DataObject* create(DataObjectPtr& dm)const;

	inline const String& getXPath()const {return strXPath; }

protected:
	Setter(const String& strXPath,
		   const Type* pType);

	String strXPath;
	const Type* pType;

    const DM::Type* pTargetType;

    struct Element{

    	inline Element(const DM::Property *pProperty, int iIdx):pProperty(pProperty),iIdx(iIdx){};

    	inline Element& operator=(const Element& o){
    		pProperty=o.pProperty;
    		iIdx=o.iIdx;
    		return *this;
    	}

    	inline bool isMulti()const { return iIdx != CSingle; };

    	const DM::Property *pProperty;
    	int iIdx;

    	static const int CSingle=-1;
    };

    DM::DataObject* getParent(DM::DataObject* pCursor, bool bCreateIfNeeded=false)const;

    void buildElementList();

    typedef std::list<Element> ElementList;
    ElementList                    lstPath;

	friend class Factory<Setter>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Tools_Setter_H_ */
