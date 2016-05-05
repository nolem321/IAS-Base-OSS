/*
 * File: IAS-QSystemMod-FCGI/src/qs/Impl/fcgi/System.cpp
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
#include "org/invenireaude/qsystem/stats/DataFactory.h"


using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace FCGI {

/*************************************************************************/
System::System(){
	IAS_TRACER;
	URI uri;
	strName="FCGI";
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;
	URI uri;
	API::Environment::BuildURI(uri,dmConnection);

	if(uri.getHost().compare("localhost") != 0)
			IAS_THROW(InternalException("Only fcgi://localhost/ is supported."));

	return IAS_DFT_FACTORY<QS::FCGI::Connection>::Create< FCGI::System* >(this,uri.getURIString());
}
/*************************************************************************/
ContentManager*  System::getContentManager(){
	IAS_TRACER;
	IAS_THROW(InternalException("No content created"));
	return 0;
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** FCGI instance destroyed.");
}
/*************************************************************************/
}
}
}

/*************************************************************************/
extern "C"{

::IAS::QS::Impl::System* _ias_qs_system_fcgi(){

	return IAS_DFT_FACTORY< ::IAS::QS::FCGI::System >::Create();

 }

}
/*************************************************************************/
