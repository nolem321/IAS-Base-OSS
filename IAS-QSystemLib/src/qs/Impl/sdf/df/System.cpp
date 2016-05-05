/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/df/System.cpp
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

#include "BrowseDriver.h"
#include "InputDriver.h"
#include "OutputDriver.h"

namespace IAS {
namespace QS {
namespace SDF {
namespace DF {


/*************************************************************************/
System::System():SDF::System(){
	IAS_TRACER;
}
/*************************************************************************/
SDF::InputDriver* System::createBrowserDriver(const API::Destination& destination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<BrowseDriver>::Create(destination);
}
/*************************************************************************/
SDF::InputDriver* System::createInputDriver(const API::Destination& destination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<InputDriver>::Create(destination);
}
/*************************************************************************/
SDF::OutputDriver* System::createOutputDriver(const API::Destination& destination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<OutputDriver>::Create(destination);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
