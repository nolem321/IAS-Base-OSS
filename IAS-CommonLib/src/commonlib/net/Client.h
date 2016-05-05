/*
 * File: IAS-CommonLib/src/commonlib/net/Client.h
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
#ifndef _IAS_Net_Client_H_
#define _IAS_Net_Client_H_

#include "Peer.h"
#include "FileHandle.h"
#include "TCPConnectionBase.h"
namespace IAS {
namespace Net {

/*************************************************************************/
class Client : public TCPConnectionBase {
public:

	Client(const Peer& peerRemote);
	Client(const Peer& peerRemote, const Peer& peerLocal);

	~Client() throw();

	FileHandle* connect()const;

	void setLocalPeer(const Peer& peerLocal);

	const Peer& getRemote()const{
		return peerRemote;
	}

private:

	Peer peerRemote;
};
/*************************************************************************/
}
}

#endif /* _IAS_Net_Client_H_ */
