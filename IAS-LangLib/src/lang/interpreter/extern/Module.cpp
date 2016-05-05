/*
 * File: IAS-LangLib/src/lang/interpreter/extern/Module.cpp
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
#include "Module.h"
#include<lang/log/LogLevel.h>

#include "ModuleProxy.h"


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {

/*************************************************************************/
Module::Module(const String& strModule,
		   	   const String& strProxy,
		   	   const DM::DataFactory* pDataFactory):
#ifndef _AIX
			   SYS::DynamicLibrary(strModule+".so", RTLD_LAZY | RTLD_LOCAL){
#else
		   	   SYS::DynamicLibrary(strModule+".a("+strModule+".so)", RTLD_LAZY | RTLD_LOCAL | RTLD_MEMBER ){
#endif

	IAS_TRACER;

	ProxyConstructorPtr pProxyConstructor = (ProxyConstructorPtr)getSymbol(strProxy);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"calling constructor at: "<<(void*)pProxyConstructor);
	ptrModuleProxy=(*pProxyConstructor)();

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"setting up ...");
	ptrModuleProxy->setup(pDataFactory);
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"done!");

}
/*************************************************************************/
Module::~Module() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Statement *Module::createStatement(const String& strSymbol,
   	   	                           const StringList& lstParameters){
	IAS_TRACER;
	return ptrModuleProxy->createStatement(strSymbol,lstParameters);
}
/*************************************************************************/
}
}
}
}
