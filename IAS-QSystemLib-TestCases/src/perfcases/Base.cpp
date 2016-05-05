/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/Base.cpp
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
#include "commonlib/commonlib.h"

#include "Base.h"
#include <qs/api.h>

#include <qs/workers/proc/io/IOFactory.h>
#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <dm/tools/Formatter.h>

#include <qs/Impl/shm/Administrator.h>

namespace IAS{
using namespace QS::API;
using namespace QS::Workers::Proc;

namespace TCT{


/*************************************************************************/
void Base::reset(){
	IAS_TRACER;

	dmConnection=org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createConnection();

	URI uri("shm://QS.Perf.Test");

	IO::IOFactory::UpdateConnection(uri,dmConnection);

	org::invenireaude::qsystem::Ext::SystemPtr dmSystem(
			org::invenireaude::qsystem::DataFactory::GetInstance()->getSystemType()->cast(
			DM::Tools::Formatter::LoadFile("samples/perftest/system.qs.xml",
			org::invenireaude::qsystem::DataFactory::GetInstance()->getContaingDataFactory())));

	QS::SHM::Administrator::CreateSystem(dmSystem);
}
/*************************************************************************/
Base::~Base() throw(){
	IAS_TRACER;
	Environment* TheEnvironment = Environment::GetInstance();
	TheEnvironment->shutdown();
}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
