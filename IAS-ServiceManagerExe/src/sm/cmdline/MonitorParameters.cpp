/*
 * File: IAS-ServiceManagerExe/src/sm/cmdline/MonitorParameters.cpp
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
#include "MonitorParameters.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace SM {
namespace CmdLine {

/*************************************************************************/
MonitorParameters::MonitorParameters(int argc, char* argv[]){
	IAS_TRACER;

	::IAS::SM::CmdLine::ProgramParameters::init(argc,argv,"abc");
	if (hmIndicators['m'])
		parse(hmValues['m']);

}
/*************************************************************************/
MonitorParameters::~MonitorParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void MonitorParameters::printCmdDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
void MonitorParameters::printArgsDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
