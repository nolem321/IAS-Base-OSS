/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Administrator.cpp
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
#include "Administrator.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Attachment.h"
#include "Distributor.h"
#include "Cleaner.h"
#include "System.h"
#include "admin/ActionDispatcher.h"
#include "lang/model/Model.h"

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Administrator::Administrator(SHM::Attachment* pAttachment):
	pAttachment(pAttachment){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pAttachment);
}
/*************************************************************************/
Administrator::~Administrator() throw(){
	IAS_TRACER;
}
/*************************************************************************/
stats::Ext::SystemStatsPtr Administrator::getStats(bool bReset){
	IAS_TRACER;

	return pAttachment->getStats(bReset);
}
/*************************************************************************/
void Administrator::CreateSystem(Ext::SystemPtr dmSystem){
	IAS_TRACER;

	IAS_DFT_FACTORY<System>::PtrHolder ptrSystem(
			IAS_DFT_FACTORY<System>::Create() );

	ptrSystem->create(dmSystem);
}
/*************************************************************************/
void Administrator::DeleteSystem(const String& strName){
	IAS_TRACER;
}
/*************************************************************************/
void Administrator::StartDistributor(const String& strName){
	IAS_TRACER;

	Lang::Model::Model::RegisterBuildInTypes();

	::org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection(
				API::Environment::BuildConnection("shm",strName));

	IAS_DFT_FACTORY<System>::PtrHolder ptrSystem(
					IAS_DFT_FACTORY<System>::Create() );

	ptrSystem->createConnection(dmConnection);

	IAS_DFT_FACTORY<Distributor>::PtrHolder ptrDistributor(
			IAS_DFT_FACTORY<Distributor>::Create(ptrSystem->getAttachment()));

	ptrDistributor->start();

}
/*************************************************************************/
void Administrator::StartCleaner(const String& strName){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection(
				API::Environment::BuildConnection("shm",strName));

	IAS_DFT_FACTORY<System>::PtrHolder ptrSystem(
						IAS_DFT_FACTORY<System>::Create() );

	ptrSystem->createConnection(dmConnection);

	IAS_DFT_FACTORY<Cleaner>::PtrHolder ptrCleaner(
			IAS_DFT_FACTORY<Cleaner>::Create(ptrSystem->getAttachment()));

	ptrCleaner->start();

}
/*************************************************************************/
void Administrator::DisplaySystem(const String& strName, std::ostream& os){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection(
				API::Environment::BuildConnection("shm",strName));

	IAS_DFT_FACTORY<QS::SHM::System>::PtrHolder ptrSystem(
						IAS_DFT_FACTORY<QS::SHM::System>::Create() );

	ptrSystem->createConnection(dmConnection);

	ptrSystem->getAttachment()->dumpInfo(os);

	//stats::Ext::SystemStatsPtr dmStats;
	//dmStats=ptrSystem->getStats(false);
	//os<<DM::XML::XMLHelper::Stringify(stats::DataFactory::GetInstance()->getContaingDataFactory(), dmStats);
}
/*************************************************************************/
void Administrator::ChangeSystem(const String& strName,
					::org::invenireaude::qsystem::Ext::ActionList& lstActions){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection(
				API::Environment::BuildConnection("shm",strName));

	IAS_DFT_FACTORY<System>::PtrHolder ptrSystem(
						IAS_DFT_FACTORY<System>::Create() );

	ptrSystem->createConnection(dmConnection);

	ptrSystem->getAttachment()->getActionDispatcher()->dispatchWork(lstActions);

}
/*************************************************************************/
}
}
}
