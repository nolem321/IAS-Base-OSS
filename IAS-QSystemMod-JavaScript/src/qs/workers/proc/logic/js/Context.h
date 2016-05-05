/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/Context.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_JS_Context_H_
#define _IAS_QS_Workers_Proc_Logic_JS_Context_H_

#include <commonlib/commonlib.h>

#include "jsapi.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS {

class Runtime;

/*************************************************************************/
/** The Context class.
 *
 */
class Context {
public:
	virtual ~Context() throw();

	JSContext* getJSContext()const{
		return pJSContext;
	}


protected:
	Context();

	JSRuntime *pJSRuntime;
	JSContext *pJSContext;

	friend class Factory<Context>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_JS_Context_H_ */
