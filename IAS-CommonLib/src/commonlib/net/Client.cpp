/*
 * File: IAS-CommonLib/src/commonlib/net/Client.cpp
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
#include "Client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "PeerAddrInfo.h"

#include <commonlib/logger/logger.h>

namespace IAS {
namespace Net {

/*************************************************************************/
Client::Client(const Peer& peerRemote):
	peerRemote(peerRemote){}
/*************************************************************************/
Client::Client(const Peer& peerRemote, const Peer& peerLocal):
	TCPConnectionBase(peerLocal),
	peerRemote(peerRemote){}
/*************************************************************************/
Client::~Client() throw(){
	IAS_TRACER;
}
/*************************************************************************/
FileHandle* Client::connect()const{
	IAS_TRACER;

	PeerAddrInfo aiLocal(peerLocal);
	PeerAddrInfo aiRemote(peerRemote);

	IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrSocketHandle;

	for(PeerAddrInfo::const_iterator itLocal=aiLocal.begin(); itLocal != aiLocal.end(); ++itLocal)
		for(PeerAddrInfo::const_iterator itRemote=aiRemote.begin(); itRemote != aiRemote.end(); ++itRemote){

		int iSocket;

		if((iSocket = socket((*itLocal)->ai_family, (*itLocal)->ai_socktype, (*itLocal)->ai_protocol)) < 0)
			IAS_THROW(SystemException("socket(): ")<<peerLocal);

		IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"Local: "<<peerLocal);


		if(::bind(iSocket, (*itLocal)->ai_addr, (*itLocal)->ai_addrlen) == 0){

			IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"Remote: "<<peerRemote);

			if(::connect(iSocket, (*itRemote)->ai_addr, (*itRemote)->ai_addrlen) == 0){

				ptrSocketHandle=IAS_DFT_FACTORY<FileHandle>::Create(iSocket);
				ptrSocketHandle->setPeer(peerRemote);
				return ptrSocketHandle.pass();
			}

		}
	}

	IAS_THROW(SystemException("Couldn't connect any any address from: ")<<peerLocal<<", to: "<<peerRemote);
}
/*************************************************************************/
void Client::setLocalPeer(const Peer& peerLocal){
	IAS_TRACER;
	this->peerLocal=peerLocal;
}
/*************************************************************************/
}
}
