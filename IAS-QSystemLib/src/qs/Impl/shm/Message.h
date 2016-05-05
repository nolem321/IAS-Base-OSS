/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Message.h
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
#ifndef _IAS_QS_System_Message_H_
#define _IAS_QS_System_Message_H_

#include <qs/api/Message.h>
#include <qs/api/Content.h>

#include "Content.h"
#include "../base/Attributes.h"
#include "shared/MsgEntry.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
class MsgEntry;
}
}
namespace SHM {

/*************************************************************************/
/** The Message class.
 *
 */
class Message : public virtual API::Message {
public:

	virtual ~Message() throw();

	virtual API::Content*    getContent();
	virtual API::Attributes* getAttributes();


	const Shared::MsgEntry& getEntry();

protected:
	Message(const Shared::MsgEntry& entry);

	IAS_DFT_FACTORY<Content>::PtrHolder ptrContent;
	IAS_DFT_FACTORY<QS::Base::Attributes>::PtrHolder ptrAttributes;

	Shared::MsgEntry entry;

	friend class Factory<Message>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Message_H_ */
