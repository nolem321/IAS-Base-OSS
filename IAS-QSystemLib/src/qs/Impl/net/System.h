/*
 * File: IAS-QSystemLib/src/qs/Impl/net/System.h
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
#ifndef _IAS_QS_Net_System_H_
#define _IAS_QS_Net_System_H_

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/ssl.h>

#include <qs/api.h>

#include <qs/Impl/System.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Pump{
class MsgPumpFactory;
}

class Connection;

/*************************************************************************/
/** The Net class.
 *
 */
class System :
		public Impl::System {
public:

	virtual ~System() throw();

	API::ContentManager*  	getContentManager()const;

	Pump::MsgPumpFactory* getPumpFactory()const;

protected:

	System();

	IAS_DFT_FACTORY<Pump::MsgPumpFactory>::PtrHolder ptrMsgPumpFactory;
};
/*************************************************************************/

}
}
}

#endif /* _IAS_QS_Net_System_H_ */
