/*
 * File: IAS-CommonLib/src/commonlib/net/Server.h
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
#ifndef _IAS_Net_Server_H_
#define _IAS_Net_Server_H_


#include "FileHandle.h"
#include "Peer.h"
#include "TCPConnectionBase.h"
namespace IAS {
namespace Net {

/*************************************************************************/
/** The Server class.
 *
 */
class Server : public TCPConnectionBase {
public:

	Server(const Peer& peerLocal);

	void bind();

	~Server() throw();

	FileHandle* accept()const;

	FileHandle* getSocket()const{
		return ptrSocketHandle;
	}

protected:

	IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrSocketHandle;
};

/*************************************************************************/
}
}

#endif /* _IAS_Net_Server_H_ */
