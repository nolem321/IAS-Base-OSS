/*
 * File: IAS-QSystemLib/src/qs/Impl/Environment.cpp
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
#include "Environment.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <commonlib/sys/DynamicLoader.h>

#include <qs/Impl/shm/Connection.h>
#include <qs/Impl/shm/System.h>

#include <qs/Impl/sdf/file/System.h>
#include <qs/Impl/sdf/dir/System.h>
#include <qs/Impl/sdf/df/System.h>
#include <qs/Impl/sdf/timer/System.h>

#include <qs/Impl/net/sync/client/System.h>
#include <qs/Impl/net/sync/server/System.h>

#include <qs/Impl/net/sync/client/http/System.h>
#include <qs/Impl/net/sync/server/http/System.h>

#include <qs/Impl/net/async/System.h>
#include <qs/Impl/net/async/http/System.h>
#include <algorithm>
#include <unistd.h>

namespace IAS {
namespace QS {
namespace Impl {

//template<>
//InstanceFeature<IAS::QS::Impl::Environment>::TheInstanceType
//InstanceFeature<IAS::QS::Impl::Environment>::TheInstance(NULL);

/*************************************************************************/
Environment::Environment(){
	IAS_TRACER;
}
/*************************************************************************/
Environment::~Environment() throw(){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.bIsInfo,"Environment cleanup.")
}
/*************************************************************************/
API::Connection* Environment::connect(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(!dmConnection->isSetProtocol())
		IAS_THROW(BadUsageException("Protocol not set in a specification of QS."));

	String strProtocol(dmConnection->getProtocol());

	if(!hmSystems.count(strProtocol)){

		if(strProtocol.compare("shm") == 0){
			hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::SHM::System>::Create();
		}else if(strProtocol.compare("file") == 0){
			hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::SDF::File::System>::Create();
		}else if(strProtocol.compare("dir") == 0){
			hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::SDF::Dir::System>::Create();
		}else if(strProtocol.compare("df") == 0){
				hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::SDF::DF::System>::Create();
		}else if(strProtocol.compare("timer") == 0){
				hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::SDF::Timer::System>::Create();
		}else if(strProtocol.compare("netc") == 0){
				hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::Net::Sync::Client::System>::Create();
		}else if(strProtocol.compare("nets") == 0){
				hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::Net::Sync::Server::System>::Create();
		}else if(strProtocol.compare("netas") == 0){
				hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::Net::Async::System>::Create();
		}else if(strProtocol.compare("http") == 0){
				hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::Net::Sync::Client::HTTP::System>::Create();
		}else if(strProtocol.compare("srvhttp") == 0){
				hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::Net::Sync::Server::HTTP::System>::Create();
		}else if(strProtocol.compare("asrvhttp") == 0){
			hmSystems[strProtocol]=IAS_DFT_FACTORY<QS::Net::Async::HTTP::System>::Create();
		}else{
			try{
				hmSystems[strProtocol]=(*(getFactory(strProtocol)))();
			}catch(Exception& e){
				IAS_THROW(BadUsageException(String("Unknown protocol or dynamic library cannot be loaded: ")+strProtocol));
			}
		}
	}

	return hmSystems[strProtocol]->createConnection(dmConnection);
}
/*************************************************************************/
Environment::ExternalSystemFactoryPtr Environment::getFactory(const String& strProtocol){
	IAS_TRACER;

	if(hmLibraries.count(strProtocol) == 0){

		String strTmp=String("qsmod_")+strProtocol+".so";

		hmLibraries[strProtocol]=IAS_DFT_FACTORY<SYS::DynamicLibrary>::Create(strTmp);
	}

	void *p=hmLibraries.at(strProtocol)->getSymbol(String("_ias_qs_system_")+strProtocol);

	return (ExternalSystemFactoryPtr)p;
}
/*************************************************************************/
void Environment::shutdown(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.bIsInfo,"System instance will be destroyed: "<<getpid());

	hmSystems.clear();

	return;
}
/*************************************************************************/

}
}
}
