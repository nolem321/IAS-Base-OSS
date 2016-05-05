/*
 * File: IAS-QSystemLib/src/qs/api/Destination.h
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
#ifndef _IAS_QS_API_Destination_H_
#define _IAS_QS_API_Destination_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace API {

/*************************************************************************/
/** The Destination class.
 *
 */
class Destination {
public:

	Destination(const String& strQName="_not_set_"):strQName(strQName){};
	Destination(const Destination& other):strQName(other.strQName){};

	Destination& operator=(const Destination& other){
		strQName=other.strQName;
		return *this;
	}

	virtual ~Destination() throw(){};

	inline const void setName(const String& strQName){ this->strQName=strQName; }

	inline const String& getName()const { return strQName; }

protected:
	String strQName;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Destination_H_ */

