/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/client/BlockIOWrapperFactory.h
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
#ifndef _IAS_QS_Net_Sync_Client_BlockIOWrapperFactory_H_
#define _IAS_QS_Net_Sync_Client_BlockIOWrapperFactory_H_

#include <commonlib/commonlib.h>

#include "../BlockIOWrapperFactory.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{
namespace Client {

/*************************************************************************/
/** The BlockIOWrapperFactory class.
 *
 */
class BlockIOWrapperFactory :
		public QS::Net::Sync::BlockIOWrapperFactory,
		public ::IAS::Net::Client {
public:

	virtual ~BlockIOWrapperFactory() throw();

	virtual Sync::BlockIOWrapper* createBlockIOWrapper()const;

	inline bool hasProxy()const;

protected:
	BlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	String getHost(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);
	int getPort(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	bool bHasProxy;

	friend class Factory<BlockIOWrapperFactory>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Net_Sync_ServerBlockIOWrapperFactory_H_ */
