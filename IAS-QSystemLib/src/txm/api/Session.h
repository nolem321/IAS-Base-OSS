/*
 * File: IAS-QSystemLib/src/txm/api/Session.h
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
#ifndef _IAS_TXM_API_Session_H_
#define _IAS_TXM_API_Session_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace TXM {
namespace API {

/*************************************************************************/
/** The Session class.
 *
 */
class Session {
public:

	virtual ~Session() throw(){};

	virtual void begin()=0;
	virtual void commit()=0;
	virtual void rollback()=0;

	typedef IAS_DFT_FACTORY<Session>::PtrHolder PtrHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Session_H_ */
