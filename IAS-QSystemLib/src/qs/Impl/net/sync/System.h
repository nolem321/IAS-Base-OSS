/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/System.h
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
#ifndef _IAS_QS_Net_Sync_System_H_
#define _IAS_QS_Net_Sync_System_H_

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/ssl.h>

#include <qs/api.h>

#include "../System.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

class Connection;
class ContentManager;
class BlockIOWrapper;
class BlockIOWrapperFactory;

/*************************************************************************/
/** The Net class.
 *
 */
class System :
		public Net::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

protected:

	System();

	typedef HashMapStringToPointer<BlockIOWrapperFactory> BlockIOWrapperFactoryMap;
	BlockIOWrapperFactoryMap							  hmBlockIOWrapperFactory;

	virtual BlockIOWrapperFactory* createBlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection)const=0;

	friend class Factory<System>;
};
/*************************************************************************/

}
}
}
}
#endif /* _IAS_QS_Net_Sync_System_H_ */

