/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/df/System.h
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
#ifndef _IAS_QS_SDF_DF_System_H_
#define _IAS_QS_SDF_DF_System_H_

#include "../System.h"

namespace IAS {
namespace QS {
namespace SDF {
namespace DF {

class InputDriver;
class OutputDriver;

/*************************************************************************/
/** The SDF class.
 *
 */
class System : public SDF::System {
public:

	virtual ~System() throw();

	virtual SDF::InputDriver* createBrowserDriver(const API::Destination& destination);
	virtual SDF::InputDriver* createInputDriver(const API::Destination& destination);
	virtual SDF::OutputDriver* createOutputDriver(const API::Destination& destination);

protected:

	System();

	friend class IAS::Factory<System>;
};
/*************************************************************************/

}
}
}
}

#endif /* _IAS_QS_SDF_System_H_ */
