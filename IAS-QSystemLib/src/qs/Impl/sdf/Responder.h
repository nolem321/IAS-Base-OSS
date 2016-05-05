/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Responder.h
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
#ifndef _IAS_QS_SDF_Responder_H_
#define _IAS_QS_SDF_Responder_H_

#include <qs/api/Responder.h>
#include "Receiver.h"

namespace IAS {
namespace QS {
namespace SDF {

/*************************************************************************/
/** The Responder class.
 *
 */
class Responder :
		public Manageable,
		public virtual API::Responder {
public:

	virtual ~Responder() throw();

	virtual bool respond(API::Message* pMessage, const API::Destination& refDestination);

protected:
	Responder(Session* pSession);

	friend class Factory<Responder>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_SDF_Responder_H_ */
