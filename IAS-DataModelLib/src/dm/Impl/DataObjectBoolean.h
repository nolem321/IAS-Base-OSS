/*
 * File: IAS-DataModelLib/src/dm/Impl/DataObjectBoolean.h
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
#ifndef _IAS_DM_Impl_DATAOBJECTBOOLEAN_H_
#define _IAS_DM_Impl_DATAOBJECTBOOLEAN_H_

#include "../../dm/Impl/DataObjectBasic.h"

namespace IAS {
namespace DM {
namespace Impl {

class TypeBoolean;
/*************************************************************************/
class DataObjectBoolean : public ::IAS::DM::Impl::DataObjectBasic {
public:

	virtual ~DataObjectBoolean() throw();

	virtual void setString(const String& strValue);
	virtual void setInteger(int iValue);
	virtual void setBoolean(bool bValue);
	virtual void setFloat(Float fValue);
	virtual void setDataObject(const IAS::DM::DataObject* pDataObject);

	virtual String toString()const;
	virtual bool   toBoolean()const;
	virtual int    toInteger()const;
	virtual Float  toFloat()const;

protected:
	DataObjectBoolean(const Type *pType);

	bool bValue;

	friend class ::IAS::Factory<DataObjectBoolean>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Impl_DATAOBJECTBOOLEAN_H_ */
