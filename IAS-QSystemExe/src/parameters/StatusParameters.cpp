/*
 * File: IAS-QSystemExe/src/parameters/StatusParameters.cpp
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
#include "StatusParameters.h"

#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ds/DataFactory.h>
#include <org/invenireaude/qsystem/workers/cache/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ec/DataFactory.h>
#include <org/invenireaude/qsystem/workers/txm/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/DataFactory.h>

#include <lang/model/Model.h>


#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
StatusParameters::StatusParameters(int argc, char* argv[]){
	IAS_TRACER;

    Lang::Model::Model::RegisterBuildInTypes();

		org::invenireaude::qsystem::workers::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::io::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::ds::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::txm::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::cache::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::ec::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::logic::DataFactory::GetInstance();


	::IAS::QS::Parameters::ProgramParameters::init(argc,argv,"hs:");

}
/*************************************************************************/
const String& StatusParameters::getSystemName()const{

	if(!hmIndicators.count('s'))
			IAS_THROW(ConfigException("Missing -s option."));

	return hmValues.find('s')->second;
}
/*************************************************************************/
StatusParameters::~StatusParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatusParameters::printCmdDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
void StatusParameters::printArgsDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
