/*
 * File: IAS-LangLib/src/lang/interpreter/extern/ModuleStore.cpp
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
#include "ModuleStore.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "Module.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {

/*************************************************************************/
ModuleStore::ModuleStore(const ::IAS::DM::DataFactory  *pDataFactory):
	pDataFactory(pDataFactory){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);
}
/*************************************************************************/
ModuleStore::~ModuleStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Module *ModuleStore::getModule(const String& strModule,
								const String& strProxy){
	IAS_TRACER;

	String strRealProxyName(strProxy);

	if(strProxy.empty())
		strRealProxyName="ias_lang_std_proxy";

	ModuleMap::Key key(strModule,strRealProxyName);

	if(hmModules.hasKey(key) == 0)
		loadModule(strModule,strRealProxyName);

	return hmModules.at(key);
}
/*************************************************************************/
void ModuleStore::loadModule(const String& strModule,
							 const String& strProxy){
	IAS_TRACER;

	ModuleMap::Key key(strModule,strProxy);

	hmModules[key]=IAS_DFT_FACTORY<Module>::Create(strModule,strProxy,pDataFactory);
}
/*************************************************************************/
}
}
}
}
