/*
 * File: IAS-CommonLib/src/commonlib/tools/SerializationHelper.h
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
#ifndef _IAS_SerializationHelper_H
#define _IAS_SerializationHelper_H

#include <ostream>
#include "../types.h"

namespace IAS {

/** The class. */
 class SerializationHelper{
 public:

	 void write(int iValue,             std::ostream& os) const;
	 void write(const String& strValue, std::ostream& os) const;

	 void read(int &iValue,      std::istream& is) const;
	 void read(String& strValue, std::istream& is) const;

};

}
#endif /* _IAS_SerializationHelper_H */

