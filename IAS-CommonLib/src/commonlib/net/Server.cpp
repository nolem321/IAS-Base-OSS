/*
 * File: IAS-CommonLib/src/commonlib/net/Server.cpp
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
#include "Server.h"

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
#include <commonlib/logger/logger.h>
#include <commonlib/threads/Thread.h>
#include <arpa/inet.h>

#include "PeerAddrInfo.h"

namespace IAS {
namespace Net {

/*************************************************************************/
Server::Server(const Peer& peerLocal):TCPConnectionBase(peerLocal){
	IAS_TRACER;
	bind();
}
/*************************************************************************/
Server::~Server() throw(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"closing server: "<<peerLocal);
}
/*************************************************************************/
void Server::bind(){
	IAS_TRACER;

	PeerAddrInfo ai(peerLocal,true);

	for(PeerAddrInfo::const_iterator it=ai.begin(); it != ai.end(); ++it){

		int iSocket;

		if((iSocket = socket((*it)->ai_family, (*it)->ai_socktype, (*it)->ai_protocol)) < 0)
			IAS_THROW(SystemException("socket(): ")<<peerLocal);

		//TODO (L) parameter - for TestCases only - set SO_REUSEADDR on a socket to true (1):

		ptrSocketHandle=IAS_DFT_FACTORY<FileHandle>::Create(iSocket);

		int optval = 1;
		setsockopt(iSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

		IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"Server: "<<iSocket<<", addr="
					<<inet_ntoa(((struct sockaddr_in*)((*it)->ai_addr))->sin_addr)
					<<", port="<<(ntohs(((struct sockaddr_in*)((*it)->ai_addr))->sin_port))
					<<", family="<<((struct sockaddr_in*)((*it)->ai_addr))->sin_family);

		if(::bind(iSocket, (*it)->ai_addr, (*it)->ai_addrlen) == 0){

			if(listen(iSocket, 128)  == -1)
				IAS_THROW(SystemException("listen: ")<<peerLocal);

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Server started: "<<peerLocal<<", fd="<<(int)iSocket);

			return;
		}

	}

	IAS_THROW(SystemException("Couldn't bind on any address for: ")<<peerLocal);

}
/*************************************************************************/
FileHandle* Server::accept()const{
	IAS_TRACER;

	int iFileDescriptor = -1;

	struct sockaddr_in sinRemote;
	socklen_t          socklen=sizeof(sinRemote);
	sinRemote.sin_family = AF_INET;
	{
		Thread::Cancellation ca(true);
		iFileDescriptor = ::accept((ptrSocketHandle->getFD()), (struct sockaddr*)&sinRemote, &socklen);
	}

	if(iFileDescriptor < 0)
		IAS_THROW(SystemException("accept:"));

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo()||true,"accepted:"<<peerLocal<<", fd="<<iFileDescriptor);

	char sTmp[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(sinRemote.sin_addr), sTmp, INET_ADDRSTRLEN);


	IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFileHandle(IAS_DFT_FACTORY<FileHandle>::Create(iFileDescriptor));
	ptrFileHandle->setPeer(Peer(String(sTmp),ntohl(sinRemote.sin_port)));

	return ptrFileHandle.pass();
}
/*************************************************************************/
}
}
