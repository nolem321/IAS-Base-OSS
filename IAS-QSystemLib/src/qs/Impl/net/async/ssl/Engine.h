/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/ssl/Engine.h
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
#ifndef _IAS_QS_Net_Async_SSL_Engine_H_
#define _IAS_QS_Net_Async_SSL_Engine_H_

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/ssl.h>

#include "../Engine.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {
namespace SSL {


/*************************************************************************/
/** The Engine class.
 *
 */
class Engine : public Async::Engine{
public:

	virtual ~Engine() throw();

	IAS::Net::SSL::Context* getContext();

protected:
	Engine(const ::org::invenireaude::qsystem::workers::Connection* dmConnection, System *pSystem);

	IAS_DFT_FACTORY<IAS::Net::SSL::Context>::PtrHolder  ptrContext;

	friend class Factory<Engine>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Net_Async_SSL_Engine_H_ */
