/*
 * File: IAS-QSystemLib/src/qs/api/Publisher.h
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
#ifndef _IAS_QS_API_Publisher_H_
#define _IAS_QS_API_Publisher_H_

#include <commonlib/commonlib.h>

#include "Sender.h"

namespace IAS {
namespace QS {
namespace API {

class Message;

/*************************************************************************/
/** The Publisher class.
 *
 */
class Publisher : protected virtual Sender {
public:

	virtual ~Publisher() throw(){};

	inline bool publish(Message* pMessage){
		return send(pMessage);
	}

	typedef IAS_DFT_FACTORY<Publisher>::PtrHolder PtrHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Publisher_H_ */
