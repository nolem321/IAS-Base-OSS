/*
 * File: IAS-QSystemLib/src/ds/Impl/Connection.cpp
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
#include "Connection.h"

#include <commonlib/commonlib.h>
#include <qs/log/LogLevel.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

#include "System.h"

namespace IAS {
namespace DS {
namespace Impl {

/*************************************************************************/
Connection::Connection(const System* pSystem, const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter):
	dmParameter(dmParameter->duplicateParameter()),
	pSystem(pSystem){
	IAS_TRACER;
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
	IAS_LOG(::IAS::QS::LogLevel::INSTANCE.bIsInfo,"DS Connection cleanup.")
}
/*************************************************************************/
const System* Connection::getSystem()const{
	IAS_TRACER;
	return pSystem;
}
/*************************************************************************/
}
}
}
