/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/exception/JavaScriptException.h
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
/* ChangeLog:
 * 
 */

#ifndef _IAS_QS_Workers_Proc_Logic_JS_JavaScriptException_H_
#define _IAS_QS_Workers_Proc_Logic_JS_JavaScriptException_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS{


/*************************************************************************/
/** The JavaScriptException exception class.
 */

class JavaScriptException : public ::IAS::Exception {

public:
	JavaScriptException();
	JavaScriptException(const String& strInfo);

	virtual ~JavaScriptException() throw();
	virtual const char*  getName();

};
/*************************************************************************/
}
}
}
}
}
}
#endif /*_IAS_QS_API_JavaScriptException_H_*/
