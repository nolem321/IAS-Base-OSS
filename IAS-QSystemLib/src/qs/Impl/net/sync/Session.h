/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Session.h
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
#ifndef _IAS_QS_Net_Sync_Session_H_
#define _IAS_QS_Net_Sync_Session_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>

#include <qs/Impl/net/Session.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

class Connection;
class BlockIOWrapper;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public virtual QS::Net::Session {
public:

	virtual ~Session() throw();


	IAS::Net::IBlockIO* getBlockIO();

	void setTimeout(int iTimeout = -1);

	Connection *getConnection()const;

	void updateAttributes(API::Attributes* pAttributes)const;

protected:
	Session(Connection *pConnection);

	BlockIOWrapper* getBlockIOWrapper();
	void            purgeIOWrapper();

	virtual API::Producer*   createProducer(const API::Destination& refDestination);
	virtual API::Consumer*   createConsumer(const API::Destination& refDestination);

	virtual API::Requester*  createRequester(const API::Destination& outDestination,
											   const API::Destination& inDestination);

	virtual API::Responder*  createResponder();

private:

	Connection *pConnection;
	IAS_DFT_FACTORY<BlockIOWrapper>::PtrHolder ptrBlockIOWrapper;

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_QS_Net_Sync_Session_H_ */

