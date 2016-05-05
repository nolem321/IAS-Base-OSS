/*
 * File: IAS-CommonLib/src/commonlib/net/socket/EventHandler.h
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
#ifndef _IAS_Net_Socket_EventHandler_H_
#define _IAS_Net_Socket_EventHandler_H_

#include <commonlib/commonlib.h>
#include "../EventHandler.h"
#include "../Server.h"
#include "../FileHandle.h"

namespace IAS {
namespace Net {
namespace Socket {

/*************************************************************************/
class ServiceHandleFactory {
	public:
	virtual ~ServiceHandleFactory() throw(){};
	virtual void createService(FileHandle* pFileHandle)=0;
};

/*************************************************************************/
/** The EventHandler class.
 *
 */
class EventHandler : public ::IAS::Net::EventHandler{
public:

	virtual ~EventHandler() throw();

protected:
	EventHandler(ServiceHandleFactory* pServiceHandleFactory,
			     Server*               pServer);


	virtual void onInputReady();
	virtual void onTimeout();
	virtual void onError();

	Server*               pServer;

	IAS_DFT_FACTORY<ServiceHandleFactory>::PtrHolder ptrServiceHandleFactory;

	friend class Factory<EventHandler>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Socket_EventHandler_H_ */
