/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/Context.cpp
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
#include <qs/log/LogLevel.h>


#include "Context.h"
#include "exception/JavaScriptException.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS {

/* The error reporter callback. */

/*************************************************************************/
static void _reportError(JSContext *cx, const char *message, JSErrorReport *report) {
	IAS_TRACER

	//TODO how to write back to JS::Context ?

     StringStream ssInfo;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Error:"<<(report->filename ? report->filename : "[no filename]")
          <<":"<<(unsigned int) report->lineno<<" "<<message);

	//IAS_THROW(JavaScriptException(ssInfo.str()));
}

/*************************************************************************/
Context::Context():
	pJSRuntime(JS_NewRuntime(8L * 1024L * 1024L, JS_NO_HELPER_THREADS)),
	pJSContext(JS_NewContext(pJSRuntime, 8192)){
	IAS_TRACER;

	if (!pJSRuntime)
		IAS_THROW(JavaScriptException("Cannot initialize runtime !"));

	if (!pJSContext)
		IAS_THROW(JavaScriptException());

	JSAutoRequest jsAutoRequest(pJSContext);

	JS_SetOptions(pJSContext, JSOPTION_VAROBJFIX);
	JS_SetErrorReporter(pJSContext, _reportError);
}
/*************************************************************************/
Context::~Context() throw(){
	IAS_TRACER;
	JS_DestroyContext(pJSContext);
}
/*************************************************************************/
}
}
}
}
}
}
