/*
 * File: IAS-DataModelLib/src/dm/gen/DataObjectList.h
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
#ifndef _IAS_DM_Gen_DATAOBJECTLIST_H_
#define _IAS_DM_Gen_DATAOBJECTLIST_H_

#include "../../dm/DataObjectList.h"

#include <commonlib/commonlib.h>
#include "../../dm/DataObject.h"
#include "../../dm/Type.h"

namespace IAS {
namespace DM {
namespace Gen {

class DataObject;

/*************************************************************************/
/** The class. */
 class DataObjectListProxy {
public:

	inline int size() const { return refDataObjectList.size(); };

	inline void  remove(int iIdx) { refDataObjectList.remove(iIdx); };
	inline void  add(::IAS::DM::DataObject* pDataObject){ refDataObjectList.add(pDataObject); };

	inline void  clear() { refDataObjectList.clear(); };

	inline ::IAS::DM::DataObject* operator [](int iIdx) { return refDataObjectList.at(iIdx);};
	inline const ::IAS::DM::DataObject* operator [](int iIdx) const { return refDataObjectList.at(iIdx); };
	inline ::IAS::DM::DataObject* at(int iIdx) { return refDataObjectList.at(iIdx); };
	inline const ::IAS::DM::DataObject* at(int iIdx) const { return refDataObjectList.at(iIdx); };

protected:

	DataObjectListProxy(DataObjectList& refDataObjectList) throw():
		refDataObjectList(refDataObjectList){
	};

	DataObjectList& refDataObjectList;
};

/*************************************************************************/
/** The class. */
 class DataObjectListStringProxy : public DataObjectListProxy{

	public:

	DataObjectListStringProxy(DataObjectList& refDataObjectList) throw():
		DataObjectListProxy(refDataObjectList){
	};

	DataObjectListStringProxy(DataObjectListStringProxy& other) throw():
		DataObjectListProxy(refDataObjectList){
	};

	DataObjectListStringProxy& operator=(const DataObjectListStringProxy& other){
		this->refDataObjectList=other.refDataObjectList;
		return *this;
	};


	inline void  add(const String& strValue){
		refDataObjectList.add(refDataObjectList.getType()->createDataObject(strValue));
	};

	inline String operator [](int iIdx) { return refDataObjectList.at(iIdx)->toString();};
	inline const String operator [](int iIdx) const { return refDataObjectList.at(iIdx)->toString(); };
	inline String at(int iIdx) { return refDataObjectList.at(iIdx)->toString(); };
	inline const String at(int iIdx) const { return refDataObjectList.at(iIdx)->toString(); };

};

}
}
}
#endif /* _IAS_DM_DATAOBJECTLIST_H_ */
