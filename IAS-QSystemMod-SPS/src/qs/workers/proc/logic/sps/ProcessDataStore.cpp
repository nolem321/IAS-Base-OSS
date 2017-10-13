/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/ProcessDataStore.cpp
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
#include "ProcessDataStore.h"
#include "WrappedStatement.h"

#include<qs/log/sps/LogLevel.h>

#include <org/invenireaude/qsystem/workers/sps/ProcessInstance.h>
#include <org/invenireaude/qsystem/workers/sps/ProcessDocument.h>
#include <org/invenireaude/qsystem/workers/sps/ProcessKey.h>
#include <org/invenireaude/qsystem/workers/sps/DataFactory.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/ProgramProvider.h>
#include <qs/workers/proc/prog/DefaultResultHandler.h>

#include "ResultHandler.h"
using namespace org::invenireaude::qsystem::workers::sps;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {
/*************************************************************************/
ProcessDataStore::ProcessDataStore(const String& strDataSource):
		strDataSource(strDataSource){
	IAS_TRACER;

	ptrProgramSet=IAS_DFT_FACTORY<Prog::ProgramSet>::Create(
			pWorkContext->getGlobalContext()->getDataFactory());

	ptrProgramSet->setResultHandler(IAS_DFT_FACTORY<SPS::ResultHandler>::Create(pWorkContext->getGlobalContext()->getDataFactory()));

	//TODO error handling try{} catch null problems
	//TODO error handling when sql specification problem error
	//TODO error handling when exception in constructor IAS::StandardFactory<IAS::QS::Workers::Proc::Logic::SPS::ProcessCache>::Create () at ../IAS-CommonLib/src/commonlib/memory/Factory.h:78

	try{
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::createProcessInstance",ptrProgramSet);
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::saveProcessInstance",ptrProgramSet);
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::loadProcessInstance",ptrProgramSet);
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::selectProcessesToSchedule",ptrProgramSet);
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::selectProcessesToClean",ptrProgramSet);

		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::createDocument",ptrProgramSet);
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::saveDocument",ptrProgramSet);
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::loadDocuments",ptrProgramSet);
		pWorkContext->getGlobalContext()->getProgramProvider()->load("sps::createProcessKey",ptrProgramSet);

	}catch(Exception& e){
		IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
	}

}
/*************************************************************************/
ProcessDataStore::~ProcessDataStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ProcessDataStore::createProcessInstance(Ext::ProcessInstancePtr dmProcessInstance)const{
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::createProcessInstance",dmContext,dmProcessInstance);

}
/*************************************************************************/
void ProcessDataStore::saveProcessInstance(Ext::ProcessInstancePtr dmProcessInstance)const{
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::saveProcessInstance",dmContext,dmProcessInstance);

}
/*************************************************************************/

Ext::ProcessInstancePtr ProcessDataStore::loadAndLockProcessInstance(const String& strPID)const{
	IAS_TRACER;

	Ext::ProcessInstancePtr dmProcessInstance(DataFactory::GetInstance()->createProcessInstance());
	dmProcessInstance->setId(strPID);

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::loadProcessInstance",dmContext,dmProcessInstance);

	if(!dmProcessInstance->isSetState())
		IAS_THROW(ItemNotFoundException(String("Process instance not found for:")+strPID));

	return dmProcessInstance;
}
/*************************************************************************/
void ProcessDataStore::getProcessesToSchedule(org::invenireaude::qsystem::workers::sps::Ext::ProcessArrayPtr dmArray, int iMaxEntries ){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::selectProcessesToSchedule",dmContext,dmArray);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"To be scheduled:"<<dmArray->getInstancesList().size());

}
/*************************************************************************/
void ProcessDataStore::getProcessesToClean(org::invenireaude::qsystem::workers::sps::Ext::ProcessArrayPtr dmArray, int iMaxEntries ){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
		ptrProgramSet->execute("sps::selectProcessesToClean",dmContext,dmArray);

}
/*************************************************************************/
void ProcessDataStore::saveDocument(const String& strPID, const String& strProcess, const String& strVersion, const String& strName, DM::DataObject* dm)const{
	IAS_TRACER;

	Ext::ProcessDocumentPtr dmProcessDocument(DataFactory::GetInstance()->createProcessDocument());

	dmProcessDocument->setPid(strPID);
	dmProcessDocument->setProcess(strProcess);
	dmProcessDocument->setVersion(strVersion);
	dmProcessDocument->setName(strName);
	dmProcessDocument->setData(dm);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"saving="<<strName);

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::saveDocument",dmContext,dmProcessDocument);

}
/*************************************************************************/
void ProcessDataStore::createProcessKey(const String& strPID, const String& strProcess, const String& strVersion, const String& strName, const String& strValue)const{
	IAS_TRACER;


	Ext::ProcessKeyPtr dmProcessKey(DataFactory::GetInstance()->createProcessKey());
	dmProcessKey->setPid(strPID);
	dmProcessKey->setProcess(strProcess);
	dmProcessKey->setVersion(strVersion);
	dmProcessKey->setName(strName);
	dmProcessKey->setData(strValue);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"saving="<<strName);


	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::createProcessKey",dmContext,dmProcessKey);

}
/*************************************************************************/
void ProcessDataStore::createDocument(const String& strPID, const String& strProcess, const String& strVersion, const String& strName, DM::DataObject* dm)const{
	IAS_TRACER;

	Ext::ProcessDocumentPtr dmProcessDocument(DataFactory::GetInstance()->createProcessDocument());
	dmProcessDocument->setPid(strPID);
	dmProcessDocument->setProcess(strProcess);
	dmProcessDocument->setVersion(strVersion);
	dmProcessDocument->setName(strName);
	dmProcessDocument->setData(dm);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"saving="<<strName);


	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::createDocument",dmContext,dmProcessDocument);

}/*************************************************************************/
org::invenireaude::qsystem::workers::sps::Ext::DocumentsArrayPtr ProcessDataStore::loadDocuments(const String& strPID)const{
	IAS_TRACER;

	Ext::DocumentsArrayPtr dmArray=DataFactory::GetInstance()->createDocumentsArray();
	dmArray->setPid(strPID);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"loading="<<strPID);


	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute("sps::loadDocuments",dmContext,dmArray);

	return dmArray;
}
/*************************************************************************/

}
}
}
}
}
}
