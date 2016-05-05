/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/ProcessCacheEntry.cpp
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
#include "ProcessCacheEntry.h"

#include<qs/log/sps/LogLevel.h>

#include <org/invenireaude/qsystem/workers/sps/ProcessDocument.h>
#include <org/invenireaude/qsystem/workers/sps/DocumentsArray.h>
#include <org/invenireaude/qsystem/workers/sps/DataFactory.h>

using namespace org::invenireaude::qsystem::workers::sps;

#include "ProcessDataStore.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

/*************************************************************************/
ProcessCacheEntry::ProcessCacheEntry(Ext::ProcessInstancePtr dmProcessInstance):
	dmProcessInstance(dmProcessInstance),
	iNumRequests(0){
	IAS_TRACER;
}
/*************************************************************************/
ProcessCacheEntry::ProcessCacheEntry(const String& strID,const String& strProcessName, ProcessDataStore* pDataStore):
	iNumRequests(0){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataStore);

	Ext::ProcessInstancePtr dmProcessInstance(DataFactory::GetInstance()->createProcessInstance());
	dmProcessInstance->setId(strID);

	time_t iTime=time(NULL);

	dmProcessInstance->setName(strProcessName);
	dmProcessInstance->setActivity("start");
	dmProcessInstance->setPending(0);
	dmProcessInstance->setSeq(1);
	dmProcessInstance->setState("R");
	dmProcessInstance->setCreated(iTime);
	dmProcessInstance->setOldVersion(0);
	dmProcessInstance->setNewVersion(0);
	dmProcessInstance->setUpdated(iTime);

	this->dmProcessInstance=dmProcessInstance;

	pDataStore->createProcessInstance(dmProcessInstance);
}
/*************************************************************************/
ProcessCacheEntry::~ProcessCacheEntry() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ProcessCacheEntry::updateProcessInstance(org::invenireaude::qsystem::workers::sps::ProcessInstance* dmProcessInstance){
	IAS_TRACER;

	if(dmProcessInstance->getId().compare(this->dmProcessInstance->getId()) != 0)
		IAS_THROW(InternalException(String("PID mismatch:")+
				dmProcessInstance->getId()+" ? "+this->dmProcessInstance->getId()));

	this->dmProcessInstance=dmProcessInstance;

	hmDocuments.clear();
	setModifiedDocuments.clear();

}
/*************************************************************************/
org::invenireaude::qsystem::workers::sps::ProcessInstance* ProcessCacheEntry::getProcessInstance()const{
	IAS_TRACER;
	return dmProcessInstance;
}
/*************************************************************************/
void ProcessCacheEntry::decNumPending(){
	IAS_TRACER;
	int iPending=dmProcessInstance->getPending();

	if(iPending <= 0)
		return;

	dmProcessInstance->setPending(iPending-1);
};
/*************************************************************************/
int ProcessCacheEntry::getNumPending()const {
	IAS_TRACER;
	return dmProcessInstance->getPending();
}
/*************************************************************************/
void ProcessCacheEntry::registerRequest(){
	iNumRequests++;
};
/*************************************************************************/
int ProcessCacheEntry::getNumRequests()const {
	return iNumRequests;
};
/*************************************************************************/
void ProcessCacheEntry::step(){
	IAS_TRACER;

	if(isTerminated())
		return;

	if(strNextActivity.empty())
		//TODO exception
		IAS_THROW(BadUsageException("Target activity was not set"));

	int iSequence=dmProcessInstance->getSeq();
	dmProcessInstance->setSeq(iSequence+1);

	dmProcessInstance->setPending(iNumRequests);

	dmProcessInstance->setActivity(strNextActivity);

	strNextActivity.clear();
};
/*************************************************************************/
void ProcessCacheEntry::setSetNextActivity(const String& strNextActivity){
	IAS_TRACER;
	this->strNextActivity=strNextActivity;
}
/*************************************************************************/
 DM::DataObjectPtr ProcessCacheEntry::getDocument(const String& strName){

	 IAS_TRACER;

	if(hmDocuments.count(strName)==0)
		IAS_THROW(ItemNotFoundException(String("Process document:")+strName));

	return hmDocuments.at(strName);
}
/*************************************************************************/
void ProcessCacheEntry::setDocument(const String& strName, DM::DataObject* dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"PID="<<dmProcessInstance->getId()<<", name="<<strName<<", type="<<dm->getType()->getName());

	if( hmDocuments.count(strName) > 0){

		if(setNewDocuments.count(strName) == 0)
			setModifiedDocuments[strName]=true;

	}else{
		setNewDocuments[strName]=true;
	}

	hmDocuments[strName]=dm;
}
/*************************************************************************/
void ProcessCacheEntry::terminate(const String& strInfo){
	IAS_TRACER;

	//TODO enum/consts with states list.

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"PID="<<dmProcessInstance->getId());

	int iSequence=dmProcessInstance->getSeq();
	dmProcessInstance->setSeq(iSequence+1);

	dmProcessInstance->setState("T");
	dmProcessInstance->setInfo(strInfo);
}
/*************************************************************************/
void ProcessCacheEntry::schedule(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"PID="<<dmProcessInstance->getId());
	dmProcessInstance->setState("R");
}
/*************************************************************************/
void ProcessCacheEntry::enqueueForSchedule(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"PID="<<dmProcessInstance->getId());
	dmProcessInstance->setState("S");
}
/*************************************************************************/
void ProcessCacheEntry::enqueueForEvent(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"PID="<<dmProcessInstance->getId());
	dmProcessInstance->setState("E");
}
/*************************************************************************/
void ProcessCacheEntry::save(ProcessDataStore* pDataStore){
	IAS_TRACER;

	time_t iTime=time(NULL);
	dmProcessInstance->setUpdated(iTime);

	int iVersion=dmProcessInstance->getOldVersion()+1;
	dmProcessInstance->setNewVersion(iVersion);

	pDataStore->saveProcessInstance(dmProcessInstance);

	dmProcessInstance->setOldVersion(iVersion);

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"num modified="<<setModifiedDocuments.size());


	for(DocumentNameSet::const_iterator it=setModifiedDocuments.begin();
		it != setModifiedDocuments.end(); it++){
		pDataStore->saveDocument(dmProcessInstance->getId(),it->first,hmDocuments[it->first]);
	}

	setModifiedDocuments.clear();

	IAS_LOG(LogLevel::INSTANCE.isError(),"num new="<<setNewDocuments.size());

	for(DocumentNameSet::const_iterator it=setNewDocuments.begin();
		it != setNewDocuments.end(); it++){
		pDataStore->createDocument(dmProcessInstance->getId(),it->first,hmDocuments[it->first]);
	}

	setNewDocuments.clear();

}
/*************************************************************************/
void ProcessCacheEntry::loadDocuments(ProcessDataStore* pDataStore){
	IAS_TRACER;

	hmDocuments.clear();
	setModifiedDocuments.clear();
	setNewDocuments.clear();

	Ext::DocumentsArrayPtr dmArray(pDataStore->loadDocuments(dmProcessInstance->getId()));

	Ext::ProcessDocumentList& lstDocuments(dmArray->getDocumentsList());

	for(int iIdx=0; iIdx<lstDocuments.size();iIdx++){

		ProcessDocument* dmProcessDocument=lstDocuments.at(iIdx);

		hmDocuments[dmProcessDocument->getName()]=dmProcessDocument->getData();
	}

}
/*************************************************************************/
bool ProcessCacheEntry::isTerminated()const{
	IAS_TRACER;
	return dmProcessInstance->getState().compare("T") == 0;
}
/*************************************************************************/
}
}
}
}
}
}
