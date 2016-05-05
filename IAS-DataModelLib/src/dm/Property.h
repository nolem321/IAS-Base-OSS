/*
 * File: IAS-DataModelLib/src/dm/Property.h
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
#ifndef _IAS_DM_PROPERTY_H_
#define _IAS_DM_PROPERTY_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DM {

class Type;

/*************************************************************************/
/** The class. */
 class Property {
public:

	virtual ~Property() throw(){};

	virtual const String& getName() const = 0;
	virtual const Type*   getType() const = 0;
	virtual bool 	       isMulti() const = 0;
	virtual bool 	       isXMLAttribute() const = 0;
	virtual int 	       getIdx()  const = 0;
	virtual const String&  getDescription() const = 0;

 };

/*************************************************************************/
}
}

#endif /* _IAS_DM_PROPERTY_H_ */
