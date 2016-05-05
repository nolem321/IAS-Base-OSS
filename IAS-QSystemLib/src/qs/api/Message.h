/*
 * File: IAS-QSystemLib/src/qs/api/Message.h
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
#ifndef _IAS_QS_API_Message_H_
#define _IAS_QS_API_Message_H_

#include <commonlib/commonlib.h>

#include "Content.h"

namespace IAS {
namespace QS {
namespace API {
class Content;
class Attributes;
/*************************************************************************/
/** The Message class.
 *
 */
class Message {
public:
	virtual ~Message() throw(){};

	//TODO swap const/non-const

	virtual Content*    		getContent()=0;
	virtual Attributes* 		getAttributes()=0;

	inline const Attributes* getAttributes()const{
		return const_cast<Message*>(this)->getAttributes();
	}

	inline const Content* getContent()const{
		return const_cast<Message*>(this)->getContent();
	}

	typedef IAS_DFT_FACTORY<Message>   MessageFactory;
	typedef MessageFactory::PtrHolder  PtrHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Message_H_ */
