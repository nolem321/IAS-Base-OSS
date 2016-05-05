/*
 * File: IAS-ServiceManagerLib/src/sm/worker/exe/ExecutorSimpleFactory.cpp
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
#include "ExecutorSimpleFactory.h"

#include <commonlib/commonlib.h>

using namespace ::org::invenireaude::sm::cfg;
#include <dm/datamodel.h>

namespace IAS {
namespace SM {
namespace Worker {
namespace Exe {

/*************************************************************************/
ExecutorSimpleFactory::ExecutorSimpleFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
ExecutorSimpleFactory::~ExecutorSimpleFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::SYS::Proc::Executor* ExecutorSimpleFactory::create(const ResourceGroupExe* pExeSpec,
														  const Command* pCommand)const{
	IAS_TRACER;

	Mutex::Locker locker(mutexDM);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute: "<<pCommand->getExe());

	IAS_DFT_FACTORY<SYS::Proc::Executor>::PtrHolder ptrExecutor(IAS_DFT_FACTORY<SYS::Proc::Executor>::Create(pCommand->getExe()));

	const DM::Default::Ext::StringList& lstArgs(pCommand->getArgsList());

	for(int iIdx = 0; iIdx<lstArgs.size(); iIdx++)
		ptrExecutor->appendArg(lstArgs.at(iIdx));

	return ptrExecutor.pass();
}
/*************************************************************************/
}
}
}
}
