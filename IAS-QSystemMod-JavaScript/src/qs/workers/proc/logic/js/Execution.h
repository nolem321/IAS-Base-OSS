/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/Execution.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_JS_Execution_H_
#define _IAS_QS_Workers_Proc_Logic_JS_Execution_H_

#include <commonlib/commonlib.h>

#include "jsapi.h"

#include "JSString.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS {

class Runtime;
class Context;

/*************************************************************************/
/** The Execution class.
 *
 */
class Execution {
public:
	virtual ~Execution() throw();

	bool run(const JSString& strCtx,
			const JSString& strInput,
			std::ostream& osCtx,
			std::ostream& osOutput);

	void load(const String& strScriptName);

protected:
	Execution(Context *pContext);

	Context *pContext;
	JSObject *pJSGlobal;
	JSAutoCompartment jsAutoCompartment;

	static const String CSearchPathEnvVar;
	static const String CJavaScriptWrapper;

	StringList  lstSearchPath;

	bool tryFile(const String& strFileName);
	void compile(const String& strScript, const String& strFileName);

	jsval jsSpace;

	friend class Factory<Execution>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_JS_Execution_H_ */
