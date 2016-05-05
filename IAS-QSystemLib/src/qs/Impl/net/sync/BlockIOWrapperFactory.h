/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/BlockIOWrapperFactory.h
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
#ifndef _IAS_QS_Net_Sync_BlockIOWrapperFactory_H_
#define _IAS_QS_Net_Sync_BlockIOWrapperFactory_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/

class BlockIOWrapper{
	public:
	virtual ~BlockIOWrapper(){};

	virtual IAS::Net::IBlockIO      *getBlockIO()const;
	virtual IAS::Net::FileHandle    *getFileHandle()const;

	const String& getPeer()const;


protected:
	BlockIOWrapper(IAS::Net::FileHandle* pFileHandle);
	IAS_DFT_FACTORY<IAS::Net::FileHandle>::PtrHolder ptrFileHandle;

	void setPeer(const String& strPeer);

private:
	String   strPeer;

	friend class Factory<BlockIOWrapper>;
};
/*************************************************************************/
/** The BlockIOWrapperFactory class.
 *
 */
class BlockIOWrapperFactory{
public:
	virtual ~BlockIOWrapperFactory();
	virtual BlockIOWrapper* createBlockIOWrapper()const=0;

	const ::org::invenireaude::qsystem::workers::Connection* getConnection()const;

protected:
	BlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	::org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection;
};
/*************************************************************************/
}
}
}
}
#endif /* _IAS_QS_Net_Sync_BlockIOWrapperFactory_H_ */

