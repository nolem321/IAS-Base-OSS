/*
 * File: IAS-ServiceManagerLib/src/sm/worker/exe/ExecutorSudoFactory.cpp
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
#include "ExecutorSudoFactory.h"

#include <commonlib/commonlib.h>

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {
namespace Exe {

/*************************************************************************/
ExecutorSudoFactory::ExecutorSudoFactory(){
	IAS_TRACER;
}
/*************************************************************************/
ExecutorSudoFactory::~ExecutorSudoFactory() throw () {
	IAS_TRACER;
}
/*************************************************************************/
::IAS::SYS::Proc::Executor * ExecutorSudoFactory::create(const ::org::invenireaude::sm::cfg::ResourceGroupExe* pExeSpec,
		const ::org::invenireaude::sm::cfg::Command* pCommand) const {
	IAS_TRACER;

	Mutex::Locker locker(mutexDM);

	const ::org::invenireaude::sm::cfg::ResourceGroupExeSudo* pSudoSpec = DataFactory::GetInstance()->getResourceGroupExeSudoType()->cast(pExeSpec);

	String strUserName(pSudoSpec->getUser());
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute: "<<pCommand->getExe()<<", as: "<<strUserName);

	IAS_DFT_FACTORY<SYS::Proc::Executor>::PtrHolder ptrExecutor(IAS_DFT_FACTORY<SYS::Proc::Executor>::Create("sudo"));

	ptrExecutor->appendArg("-u");
	ptrExecutor->appendArg(strUserName);
	ptrExecutor->appendArg(pCommand->getExe());

	const DM::Default::Ext::StringList& lstArgs(pCommand->getArgsList());

	for (int iIdx = 0; iIdx < lstArgs.size(); iIdx++)
		ptrExecutor->appendArg(lstArgs.at(iIdx));

	return ptrExecutor.pass();
}
/*************************************************************************/
}
}
}
}
