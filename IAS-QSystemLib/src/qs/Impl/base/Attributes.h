/*
 * File: IAS-QSystemLib/src/qs/Impl/base/Attributes.h
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
#ifndef _IAS_QS_base_Attributes_H_
#define _IAS_QS_base_Attributes_H_

#include <qs/api/Attributes.h>

namespace IAS {
namespace QS {
namespace Base {

/*************************************************************************/
/** The Attributes class.
 *
 */
class Attributes : public virtual API::Attributes {
public:

	virtual ~Attributes() throw();

	void read(std::istream& inStream);
	void write(std::ostream& outStream) const;

protected:

	Attributes();
	Attributes(const API::Attributes& other);

	friend class Factory<Attributes>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Attributes_H_ */
