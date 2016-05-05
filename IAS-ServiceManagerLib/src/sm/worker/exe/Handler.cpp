/*
 * File: IAS-ServiceManagerLib/src/sm/worker/exe/Handler.cpp
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
#include "Handler.h"

#include <commonlib/commonlib.h>

#include "ExecutorFactory.h"
#include "ExecutorSimpleFactory.h"
#include "ExecutorSudoFactory.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {
namespace Exe {

/*************************************************************************/
Handler::Handler(){
	IAS_TRACER;

	hmExecutorFactories[DataFactory::GetInstance()->getResourceGroupExeType()->getName()] =
				IAS_DFT_FACTORY<ExecutorSimpleFactory>::Create();

	hmExecutorFactories[DataFactory::GetInstance()->getResourceGroupExeSudoType()->getName()] =
			IAS_DFT_FACTORY<ExecutorSudoFactory>::Create();

}
/*************************************************************************/
Handler::~Handler() throw () {
	IAS_TRACER;
}
/*************************************************************************/
::IAS::SYS::Proc::Executor * Handler::createExecutor(const ::org::invenireaude::sm::cfg::ResourceGroupExe* pExeSpec,
		const ::org::invenireaude::sm::cfg::Command* pCommand) const {
	IAS_TRACER;

	return getFactory(pExeSpec->getType())->create(pExeSpec,pCommand);
}
/*************************************************************************/
const ExecutorFactory* Handler::getFactory(const DM::Type* pType) const {
	IAS_TRACER;
	if (hmExecutorFactories.count(pType->getName()) == 0)
		IAS_THROW(ItemNotFoundException("getExecutor"));

	return hmExecutorFactories.at(pType->getName());
}
/*************************************************************************/
}
}
}
}
