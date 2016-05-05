/*
 * File: IAS-QSystemLib/src/ds/Impl/Environment.cpp
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

#include <commonlib/commonlib.h>
#include <commonlib/sys/DynamicLoader.h>
#include <qs/log/LogLevel.h>

#include "System.h"

#include <algorithm>

#include <qs/fmt/FmtFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>
#include <unistd.h>
namespace IAS {
namespace DS {
namespace Impl {

/*************************************************************************/
Environment::Environment(){
	IAS_TRACER;
}
/*************************************************************************/
Environment::~Environment() throw(){
	IAS_TRACER;
	IAS_LOG(::IAS::QS::LogLevel::INSTANCE.bIsInfo,"Environment cleanup.")
}
/*************************************************************************/
API::Connection* Environment::connect(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;

	if(!dmParameter->isSetConnection()){
		IAS_THROW(BadUsageException(String("Connection details not set for:")+dmParameter->getName()));
	}

	String strProtocol(dmParameter->getConnection()->getProtocol());

	Mutex::Locker locker(mutex);

	if(!hmSystems.count(strProtocol)){

		try{
			hmSystems[strProtocol]=(*(getFactory(strProtocol)))();
		}catch(Exception& e){
			IAS_THROW(BadUsageException(String("Unknown protocol or dynamic load problem: ")+strProtocol+", connection="+dmParameter->getName()));
		}

	}

	return hmSystems[strProtocol]->createConnection(dmParameter);
}
/*************************************************************************/
Environment::ExternalSystemFactoryPtr Environment::getFactory(const String& strProtocol){
	IAS_TRACER;

	if(hmLibraries.count(strProtocol) == 0){

		String strTmp=String("dsmod_")+strProtocol+".so";

		hmLibraries[strProtocol]=IAS_DFT_FACTORY<SYS::DynamicLibrary>::Create(strTmp);
	}

	void *p=hmLibraries.at(strProtocol)->getSymbol(String("_ias_ds_system_")+strProtocol);

	return (ExternalSystemFactoryPtr)p;
}
/*************************************************************************/
void Environment::shutdown(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	IAS_LOG(::IAS::QS::LogLevel::INSTANCE.bIsInfo,"System instance will be destroyed: "<<getpid());

	hmSystems.clear();
	return;
}
/*************************************************************************/
void Environment::setFmtFactory(QS::Fmt::FmtFactory *pFmtFactory){
	IAS_TRACER;
	ptrFmtFactory=pFmtFactory;
}
/*************************************************************************/
QS::Fmt::FmtFactory *Environment::getFmtFactory()const{
	IAS_TRACER;

	if(!ptrFmtFactory)
		BadUsageException("Format Factory was not set for DM serialization.");

	return ptrFmtFactory;
}
/*************************************************************************/

}
}
}
