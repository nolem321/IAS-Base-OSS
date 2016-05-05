/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/Execution.cpp
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
#include<qs/log/LogLevel.h>


#include "Execution.h"
#include "exception/JavaScriptException.h"

#include "Context.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS {

const String Execution::CSearchPathEnvVar("IAS_JS_SRC_DIRS");

const String Execution::CJavaScriptWrapper(

		"var ctx = { attributes : {} };"
		"var _ias_ctx = {};"

		"function _ias_main(_ctx, _input){"
		"  ctx.attributes = {};"
		"  for(var i=0; i<_ctx.attributes.length;i++)"
		"     ctx.attributes[_ctx.attributes[i].name]=_ctx.attributes[i].value;"
		"  _ias_ctx=_ctx;"
		"  return main(_input);"
		"};"

		"function _ias_getctx(){"
		" _ias_ctx.attributes = []; "
		" for(var key in ctx.attributes)"
		"     { _ias_ctx.attributes.push({name:key, value:ctx.attributes[key]});};"
		"  return _ias_ctx;"
		"};"

		);

/*************************************************************************/

/* The class of the global object. */
static JSClass global_class = { "global",
                                JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS,
                                JS_PropertyStub,
                                JS_DeletePropertyStub,
                                JS_PropertyStub,
                                JS_StrictPropertyStub,
                                JS_EnumerateStub,
                                JS_ResolveStub,
                                JS_ConvertStub,
                                nullptr,
                                JSCLASS_NO_OPTIONAL_MEMBERS
};


/*************************************************************************/
Execution::Execution(Context *pContext):
		pContext(pContext),
		pJSGlobal(JS_NewGlobalObject(pContext->getJSContext(), &global_class, nullptr)),
		jsAutoCompartment(pContext->getJSContext(), pJSGlobal){

	IAS_TRACER;

	if (!pJSGlobal)
		IAS_THROW(JavaScriptException());

	JS_SetGlobalObject(pContext->getJSContext(), pJSGlobal);

	EnvTools::GetEnvTokenized(CSearchPathEnvVar,lstSearchPath,':');

	jsSpace=JS_NumberValue(1);

	compile(CJavaScriptWrapper,"_buildin_");
}
/*************************************************************************/
Execution::~Execution() throw(){
	IAS_TRACER;

}
/*************************************************************************/
JSBool WriteCallback(const jschar *buf, uint32_t len, void *pData){

	std::ostream& os(*(std::ostream*)pData);

	while(len--){
		os.put((char)(*buf++));
	}
    return JS_TRUE;
}
/*************************************************************************/
bool Execution::run(const JSString& strCtx,
					const JSString& strInput,
					std::ostream& osCtx,
					std::ostream& osOutput){

		IAS_TRACER;

    jsval rval;
    JSBool ok;

     ::JS::RootedValue dmContext(pContext->getJSContext());
     ::JS::RootedValue dmInput(pContext->getJSContext());

    ok=JS_ParseJSON(pContext->getJSContext(), strCtx.getChars(), strCtx.length(), &dmContext);
    if(!ok){
    	IAS_THROW(InternalException("JS_ParseJSON for a context."));
    }

    ok=JS_ParseJSON(pContext->getJSContext(), strInput.getChars(), strInput.length(), &dmInput);
    if(!ok){
       	IAS_THROW(InternalException("JS_ParseJSON for an input."));
    }

    jsval args[2];
    args[0]=dmContext;
    args[1]=dmInput;

    rval.setNull();

    ok = JS_CallFunctionName(pContext->getJSContext(),
    					 	 pJSGlobal,
    					 	 "_ias_main",2,args, &rval);


    if(!ok)
    	IAS_THROW(InternalException("_ias_main() failed."));

    if(rval.isNullOrUndefined())
    	return false;

    ok = JS_Stringify(pContext->getJSContext(), &rval, (JSObject*)NULL, jsSpace, &WriteCallback, &osOutput);

    if(!ok)
       	IAS_THROW(InternalException("JSON serialization failed."));

    osOutput.flush();

    ok = JS_CallFunctionName(pContext->getJSContext(),
    					 	 pJSGlobal,
    					 	 "_ias_getctx",0,0, &rval);


    if(!ok)
    	IAS_THROW(InternalException("_ias_getctx() failed."));


    ok = JS_Stringify(pContext->getJSContext(), &rval, (JSObject*)NULL, jsSpace, &WriteCallback, &osCtx);

    if(!ok)
       	IAS_THROW(InternalException("JSON serialization failed."));

    osCtx.flush();

    return true;
}
/*************************************************************************/
void Execution::load(const String& strScriptName){
	IAS_TRACER;

	for(StringList::const_iterator it=lstSearchPath.begin();
		it != lstSearchPath.end(); it++){

		if(tryFile(*it+"/"+strScriptName))
			return;
	}

	IAS_THROW(JavaScriptException(strScriptName+": cannot be found."))
}
/*************************************************************************/
bool Execution::tryFile(const String& strFileName){
	IAS_TRACER;

	String strScript;

	try{
		InputFile::LoadString(strFileName,strScript);
	}catch(SystemException& e){
		return false;
	}

	compile(strScript, strFileName);

	return true;
}
/*************************************************************************/
void Execution::compile(const String& strScript, const String& strFileName){

	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Compiling: "<<strFileName);

	jsval rval; //TODO release this?

    JSBool ok = JS_EvaluateScript(pContext->getJSContext(),
       					   	   	  pJSGlobal,
       					   	   	  strScript.c_str(), strScript.length(),
       					   	   	  strFileName.c_str(), 0,&rval);

    if(!ok){
    	IAS_THROW(InternalException(strFileName+": script failed."));
    }

}
/*************************************************************************/
}
}
}
}
}
}
