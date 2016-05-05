/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Controller.h
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
#ifndef _IAS_QS_System_Controller_H_
#define _IAS_QS_System_Controller_H_

#include "Controller.h"

#include <qs/api/Controller.h>
#include <qs/api/Destination.h>

#include <qs/Impl/shm/shared/Queue.h>
#include <qs/Impl/shm/shared/JournalObjectEntry.h>
#include "Manageable.h"

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
/** The Controller class.
 *
 */
class Controller : public Manageable,
			   public virtual API::Controller{

public:

	virtual ~Controller() throw();

	virtual unsigned int getNumMessages();

protected:
	Controller(Session* pSession, const API::Destination& refDestination);

	API::Destination myDestination;
	Shared::JournalObjectEntry::Holder joeQueue;

	friend class Factory<Controller>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Controller_H_ */
