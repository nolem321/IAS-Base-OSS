/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/System.cpp
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
#include "System.h"

#include <commonlib/commonlib.h>

#include "Connection.h"
#include "log/LogLevel.h"

#include "SQLTricks.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
System::System():
 IAS::DS::Impl::System(IAS_DFT_FACTORY<PostgreSQL::SQLTricks>::Create()){

	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** PostgreSQL instance created.");

}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;
	 	 return IAS_DFT_FACTORY<PostgreSQL::Connection>::Create< PostgreSQL::System* >(this, dmParameter);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** PostgreSQL instance destroyed.");
}
/*************************************************************************/
}
}
}
}

/*************************************************************************/
extern "C"{
::IAS::DS::Impl::System* _ias_ds_system_postgresql(){
	return IAS_DFT_FACTORY< ::IAS::DS::Impl::PostgreSQL::System >::Create();
  }

}
/*************************************************************************/