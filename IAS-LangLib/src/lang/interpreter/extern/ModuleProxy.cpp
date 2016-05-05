/*
 * File: IAS-LangLib/src/lang/interpreter/extern/ModuleProxy.cpp
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
#include "ModuleProxy.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/interpreter/exe/stmt/Statement.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {

/*************************************************************************/
ModuleProxy::ModuleProxy():pDataFactory(0) {
	IAS_TRACER;
}
/*************************************************************************/
ModuleProxy::~ModuleProxy() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void ModuleProxy::setup(const DM::DataFactory* pDataFactory) {
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDataFactory);
	this->pDataFactory = pDataFactory;
	setupImpl();
}
/*************************************************************************/
Statement *ModuleProxy::createStatement(const String& strSymbol,
										const StringList& lstParameters) {
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"symbol["<<strSymbol<<"]");

	SymbolToFactoryMap::const_iterator it=hmSymbolToFactory.find(strSymbol);

	if(it == hmSymbolToFactory.end()) {
		IAS_THROW(ItemNotFoundException("symbol not found:")<<strSymbol);
	}

	return (*(it->second))(lstParameters);
}
/*************************************************************************/
void ModuleProxy::cleanUp(){
	IAS_TRACER;
	cleanUpImpl();
}
/*************************************************************************/
void ModuleProxy::registerSymbol(const String& strSymbol,
								 StatementFactoryPtr pStatementFactory) {
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pStatementFactory);
	hmSymbolToFactory[strSymbol]=pStatementFactory;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"symbol["<<strSymbol<<"]="<<(void*)pStatementFactory);
}
/*************************************************************************/
void ModuleProxy::setupImpl(){
	IAS_TRACER;
}
/*************************************************************************/
void ModuleProxy::cleanUpImpl(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
