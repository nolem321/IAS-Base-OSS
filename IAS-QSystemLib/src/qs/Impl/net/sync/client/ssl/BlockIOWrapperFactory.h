/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/client/ssl/BlockIOWrapperFactory.h
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
#ifndef _IAS_QS_Net_Sync_Client_SSL_BlockIOWrapperFactory_H_
#define _IAS_QS_Net_Sync_Client_SSL_BlockIOWrapperFactory_H_

#include <commonlib/net/ssl/ssl.h>

#include "../BlockIOWrapperFactory.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{
namespace Client {
namespace SSL {
/*************************************************************************/
/** The BlockIOWrapperFactory class.
 *
 */
class BlockIOWrapperFactory :
		public Client::BlockIOWrapperFactory {
public:

	virtual ~BlockIOWrapperFactory() throw();

	virtual Sync::BlockIOWrapper* createBlockIOWrapper()const;

protected:
	BlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	IAS_DFT_FACTORY<IAS::Net::SSL::Context>::PtrHolder  ptrContext;

	friend class Factory<BlockIOWrapperFactory>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Net_Sync_Client_SSL_BlockIOWrapperFactory_H_ */
