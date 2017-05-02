/*
 * File: IAS-DataModelLib/src/dm/Impl/storage.h
 *
 * Copyright (C) 2017, Albert Krzymowski
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
#ifndef _IAS_DM_Impl_Storage_H_
#define _IAS_DM_Impl_Storage_H_

#include "../../dm/Property.h"

namespace IAS {
namespace DM {
namespace Impl {

  typedef std::basic_string< char,
				std::char_traits<char>,
				DataAllocator< char >
			> StringContentBase;

class StringContent : public StringContentBase {
	public:
	 inline StringContent(const String& other):StringContentBase(other.c_str()){}
	 operator String() const { return String(c_str()); };
};


}
}
}
#endif /* _IAS_DM_Impl_Storage_H_ */