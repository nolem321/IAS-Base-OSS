/*
 * File: IAS-QSystemLib/src/qs/api/Responder.h
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
#ifndef _IAS_QS_API_Responder_H_
#define _IAS_QS_API_Responder_H_

#include <commonlib/commonlib.h>

#include "Sender.h"
#include "Destination.h"
#include "Receiver.h"

namespace IAS {
namespace QS {
namespace API {

/*************************************************************************/
/** The Responder class.
 *
 */
class Message;

class Responder {
public:

	virtual ~Responder() throw(){};

	virtual bool respond(Message* pMessage, const Destination& destination)=0;

	typedef IAS_DFT_FACTORY<Responder>::PtrHolder PtrHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Responder_H_ */
