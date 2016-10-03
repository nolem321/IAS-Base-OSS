/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/System.cpp
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
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "ContentManager.h"
#include "Connection.h"

#include "Driver.h"
#include "org/invenireaude/qsystem/stats/DataFactory.h"


using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace SDF {

/*************************************************************************/
System::System():
	strName("FileBasedQSystem"){
	IAS_TRACER;
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;
	return IAS_DFT_FACTORY<QS::SDF::Connection>::Create(this,dmConnection);
}
/*************************************************************************/
ContentManager*  System::getContentManager(){
	IAS_TRACER;
	IAS_THROW(InternalException("No content created"));
	return 0;
}
/*************************************************************************/
InputDriver*  System::getBrowserDriver(const API::Destination& destination){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	return createBrowserDriver(destination);

}
/*************************************************************************/
InputDriver*  System::getInputDriver(const API::Destination& destination){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(!hmInputDrivers.count(destination.getName()))
		hmInputDrivers[destination.getName()]=createInputDriver(destination);

	return hmInputDrivers.at(destination.getName());

}
/*************************************************************************/
OutputDriver* System::getOutputDriver(const API::Destination& destination){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(!hmOutputDrivers.count(destination.getName()))
		hmOutputDrivers[destination.getName()]=createOutputDriver(destination);

	return hmOutputDrivers.at(destination.getName());
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** SDF instance destroyed.");
}
/*************************************************************************/
}
}
}
