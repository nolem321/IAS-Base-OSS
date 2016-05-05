/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Receiver.h
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
#ifndef _IAS_QS_SDF_Receiver_H_
#define _IAS_QS_SDF_Receiver_H_

#include "Receiver.h"

#include <qs/api/Receiver.h>
#include <qs/api/Destination.h>

#include "Manageable.h"


namespace IAS {
namespace QS {
namespace SDF {

class InputDriver;

/*************************************************************************/
/** The Receiver class.
 *
 */
class Receiver : public Manageable,
 	 	 	 	 public virtual API::Receiver{

 public:

	virtual ~Receiver() throw();

	virtual API::Message* receive(int iTimeWait, API::Attributes* pSelector);

protected:
	Receiver(Session* pSession);

	void open(const API::Destination& refDestination);

	API::Destination myDestination;

	InputDriver*	 pDriver;

	friend class Factory<Receiver>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_SDF_Receiver_H_ */
