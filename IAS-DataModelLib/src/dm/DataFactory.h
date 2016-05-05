/*
 * File: IAS-DataModelLib/src/dm/DataFactory.h
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
#ifndef _IAS_DM_DATAFACTORY_H_
#define _IAS_DM_DATAFACTORY_H_

#include <commonlib/commonlib.h>

#include "../dm/Type.h"

namespace IAS {
namespace DM {
class TypeList;

/*************************************************************************/
/** The class. */
 class DataFactory {
public:

	virtual ~DataFactory() throw(){};

	virtual Type* getType(const String& strURI, const String& strName) const =0;
	virtual Type* defineType(const String& strURI,
							   const String& strName,
							   const Type* pBaseType=NULL) =0;

	virtual Type* getDefaultType(Type::Types iType) const =0;

	virtual const TypeList& getTypes() const = 0;

	static const String BuildInTypesNamespace;
	static const String RootTypeName;
};

/*************************************************************************/
}
}

#endif /* _IAS_DM_DATAFACTORY_H_ */
