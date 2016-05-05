/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/System.cpp
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

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

/*************************************************************************/
System::System(){

	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** SQLite instance created.");
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;
	 	 return IAS_DFT_FACTORY<SQLite::Connection>::Create< SQLite::System* >(this,dmParameter);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** SQLite instance destroyed.");
}
/*************************************************************************/
}
}
}
}

/*************************************************************************/
extern "C"{
::IAS::DS::Impl::System* _ias_ds_system_sqlite(){
	return IAS_DFT_FACTORY< ::IAS::DS::Impl::SQLite::System >::Create();
  }

}
/*************************************************************************/
