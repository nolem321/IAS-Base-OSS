/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/http/System.h
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
#ifndef _IAS_QS_Net_Async_HTTP_System_H_
#define _IAS_QS_Net_Async_HTTP_System_H_

#include <commonlib/commonlib.h>

#include "../System.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {
namespace HTTP {
/*************************************************************************/
/** The Net class.
 *
 */
class System :
public ::IAS::QS::Net::Async::System {
public:

	virtual ~System() throw();

protected:

	System();

	friend class Factory<System>;
};
/*************************************************************************/

}
}
}
}
}
#endif /* _IAS_QS_Net_Async_HTTP_System_H_ */
