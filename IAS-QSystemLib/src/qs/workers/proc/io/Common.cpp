/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/Common.cpp
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
#include "Common.h"
#include<qs/log/LogLevel.h>
#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/io/Input.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>


#include "../GlobalContext.h"

#include <qs/fmt/FmtFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include "../exception/RollbackMeException.h"

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
Common::Common(const ::org::invenireaude::qsystem::workers::io::Parameters* dmParameters,
			   WCM::WorkContextManager* pWorkContextManager):
				pSession(0),
				pConnection(0),
				lstAttrUpdates(dmParameters->getAttrUpdatesList()),
				iTimeout(0){

	IAS_TRACER;

	//TODO reconsider duplicate (it is necessary for IAS_REGION) to work.

	this->dmParameters=dmParameters;

	pFmtFactory=pWorkContextManager->getGlobalContext()->getFmtFactory();

	pConnection=pWorkContextManager->qs.lookupConnection(uriConnectionKey,this->dmParameters->getConnection());
	pSession=pWorkContextManager->qs.lookupSession(uriConnectionKey,this->dmParameters);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Key: "<<uriConnectionKey.getURIString());

	destination=dmParameters->getDestination();

	if(dmParameters->isSetTimeout()){
		iTimeout=dmParameters->getTimeout();
	}

	uriOrigin=uriConnectionKey;
	uriOrigin.setPath(destination.getName());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Created: "<<(void*)this<<" "<<destination.getName()<<", timeout="<<iTimeout);

	if(dmParameters->getType()->isAssignableTo(workers::io::DataFactory::GetInstance()->getInputType())){

		const workers::io::Input* pInput=workers::io::DataFactory::GetInstance()->getInputType()->cast(dmParameters);
		IAS_CHECK_IF_NULL(pInput);

		if(pInput->isSetResponderName()){
			ptrResponder=getSession()->createResponder();
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Responder created.");
		}
	}

	ptrOnReceive=IAS_DFT_FACTORY<Prog::CallbackSet>::Create(pWorkContextManager->getGlobalContext()->getDataFactory());
	ptrOnSend=IAS_DFT_FACTORY<Prog::CallbackSet>::Create(pWorkContextManager->getGlobalContext()->getDataFactory());
	ptrOnNoData=IAS_DFT_FACTORY<Prog::CallbackSet>::Create(pWorkContextManager->getGlobalContext()->getDataFactory());

	ProgramProvider *pProgramProvider=pWorkContextManager->getGlobalContext()->getProgramProvider();

	Prog::CallbackSet::Build(ptrOnReceive, pProgramProvider, dmParameters->getOnRecievieList());
	Prog::CallbackSet::Build(ptrOnSend,    pProgramProvider, dmParameters->getOnSendList());
	Prog::CallbackSet::Build(ptrOnNoData,  pProgramProvider, dmParameters->getOnNoDataList());

}
/*************************************************************************/
Common::~Common() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Session*  Common::getSession(){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSession);
	return pSession;
}
/*************************************************************************/
API::Connection* Common::getConnection(){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);
	return pConnection;
}
/*************************************************************************/
void Common::updateAttributes(API::Message* pMessage)const{
	IAS_TRACER;

	API::Attributes* pAttributes=pMessage->getAttributes();

	for(int iIdx=0;iIdx<lstAttrUpdates.size();iIdx++){
		const workers::AttributeUpdate *pAttrUpdate=lstAttrUpdates.at(iIdx);
		if(pAttrUpdate->getOverride() || !pAttributes->isSet(pAttrUpdate->getName())){
			String strValue(pAttrUpdate->getValue());
			if(strValue.compare("@timestamp@")==0){
				Timestamp ts(true);
				strValue=ts.toString();
			}
			pAttributes->setValue(pAttrUpdate->getName(), strValue);
		}
	}

}
/*************************************************************************/
void Common::applyContext(const ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
		  	  	  	  	  API::Message* pMessage)const{
	IAS_TRACER;

	API::Attributes* pAttributes=pMessage->getAttributes();
	const workers::Ext::AttributeList& lstAttributes(dmContext->getAttributesList());

	if(dmContext->isSetMID())
		pAttributes->setMID(dmContext->getMID());

	if(dmContext->isSetMID())
		pAttributes->setMID(dmContext->getMID());

	if(dmContext->isSetCID())
		pAttributes->setCID(dmContext->getCID());

	if(dmContext->isSetFMT())
		pAttributes->setFormat(dmContext->getFMT());

	if(dmContext->isSetREPLY_TO())
		pAttributes->setReplyTo(dmContext->getREPLY_TO());

	if(dmContext->isSetPERSISTANCE())
		pAttributes->setPersistance(dmContext->getPERSISTANCE());

	if(dmContext->isSetEXPIRATION())
		pAttributes->setExpiration(dmContext->getEXPIRATION());

	if(dmContext->isSetPRIORITY())
			pAttributes->setPriority(dmContext->getPRIORITY());

	for(int iIdx=lstAttributes.size()-1; iIdx>=0; iIdx--){

		const workers::Attribute *pAttribute=lstAttributes.at(iIdx);
		const String& strName(pAttribute->getName());

		//TODO if(strName[0] != '.')
		pAttributes->setValue(pAttribute->getName(), pAttribute->getValue());
	}

	if(QS::LogLevel::INSTANCE.isInfo()){
		for(API::Attributes::ValuesMap::const_iterator it=pAttributes->begin();
			it != pAttributes->end(); it++)
			IAS_LOG(true,"["<<it->first<<"]="<<it->second);
	}

	for(int iIdx=lstAttrUpdates.size()-1; iIdx>=0; iIdx--){
		const workers::AttributeUpdate *pAttributeUpdate=lstAttrUpdates.at(iIdx);
		if(pAttributeUpdate->getOverride() || !pAttributes->isSet(pAttributeUpdate->getName()))
		pAttributes->setValue(pAttributeUpdate->getName(), pAttributeUpdate->getValue());
	}

	if(dmContext->isSetException()){

		try{
			pAttributes->setValue("IAS_EXCEPTION_NAME",dmContext->getException()->getString("name"));
		}catch(...){

			try{
				pAttributes->setValue("IAS_EXCEPTION_NAME",dmContext->getException()->getType()->getName());
			}catch(...){}
		}

		try{
			pAttributes->setValue("IAS_EXCEPTION_INFO",dmContext->getException()->getString("info").substr(0,128));
		}catch(...){

			try{
				pAttributes->setValue("IAS_EXCEPTION_INFO",dmContext->getException()->toString());
			}catch(...){}

		}

	}
}
/*************************************************************************/
void Common::buildContext(const API::Message* pMessage,
			  ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext)const{
	IAS_TRACER;

	dmContext->setStartDateTime(::IAS::DateTime(true));
	//TODO PR2 dmContext->getAttributesList().clear();

	dmContext->setOrigin(uriOrigin.getURIString());

	IAS_CHECK_IF_NULL(pMessage);

	const ::org::invenireaude::qsystem::workers::Ext::AttributeType*
	pAttributeType = ::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->getAttributeType();

	for(API::Attributes::const_iterator it=pMessage->getAttributes()->begin();
		it != pMessage->getAttributes()->end(); it++){
		if(it->first.compare(API::Attributes::CA_MID) == 0){
			dmContext->setMID(it->second);
		}else if(it->first.compare(API::Attributes::CA_CID) == 0){
			dmContext->setCID(it->second);
		}else if(it->first.compare(API::Attributes::CA_Format) == 0){
			dmContext->setFMT(it->second);
		}else if(it->first.compare(API::Attributes::CA_ReplyTo) == 0){
			dmContext->setREPLY_TO(it->second);
		}else if(it->first.compare(API::Attributes::CA_Persistance) == 0){
			dmContext->setPERSISTANCE(TypeTools::StringToInt(it->second));
		}else if(it->first.compare(API::Attributes::CA_Expiration) == 0){
			dmContext->setEXPIRATION(TypeTools::StringToInt(it->second));
		}else if(it->first.compare(API::Attributes::CA_Priority) == 0){
			dmContext->setPRIORITY(TypeTools::StringToInt(it->second));
		}else{
			workers::Attribute* dmAttribute = dmContext->createAttributes();

			dmAttribute->setString(pAttributeType->getNameProperty(),it->first);
			dmAttribute->setString(pAttributeType->getValueProperty(),it->second);

		}
	}

}
/*************************************************************************/
void Common::parse(API::Message* pMessage, DM::DataObjectPtr& dmData){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pMessage);
	pFmtFactory->getFormatter(pMessage->getAttributes()->getFormat())->
			read(dmData,*(pMessage->getContent()), pMessage->getAttributes());

	if(QS::LogLevel::INSTANCE.isData()){
		StringStream ssTmp;
		pFmtFactory->getFormatter(pMessage->getAttributes()->getFormat())->write(dmData,ssTmp);
		IAS_LOG(true,ssTmp.str());
	}
}
/*************************************************************************/
void Common::serialize(const DM::DataObject* dmData, API::Message* pMessage){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pMessage);
	IAS_CHECK_IF_NULL(dmData);


	API::Attributes* pAttributes=pMessage->getAttributes();
	const DM::Type* pType=dmData->getType();

	pAttributes->setValue("TYPE",pType->getName());
	pAttributes->setValue("SET",pType->getURI());

	//TODO default FMT ?
	if(!pAttributes->isSet(API::Attributes::CA_Format))
		pAttributes->setFormat("JSON");

	pFmtFactory->getFormatter(pAttributes->getFormat())->
			write(dmData,*(pMessage->getContent()),pAttributes);

	if(QS::LogLevel::INSTANCE.isData()){
		StringStream ssTmp;
		pFmtFactory->getFormatter(pAttributes->getFormat())->write(dmData,ssTmp,pAttributes);
		IAS_LOG(true,ssTmp.str());
	}
}
//TODO exits do not work on non-parsed send/receive.
/*************************************************************************/
void Common::receiveImpl(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
		 	 	 	  API::Message::PtrHolder& ptrMessage,
					  int iTimeout){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(dmContext.getPointer());

	API::Attributes attr;

	API::Attributes *pAttr = NULL;

	if(dmContext->isSetMID()){
		attr.setMID(dmContext->getMID());
		pAttr=&attr;
	}

	if(dmContext->isSetCID()){
		attr.setCID(dmContext->getCID());
		pAttr=&attr;
	}

	ptrMessage=get(pAttr, iTimeout);

}
/*************************************************************************/
void Common::receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 DM::DataObjectPtr& dmData,
					 int iTimeout) {
	IAS_TRACER;

	API::Message::PtrHolder ptrMessage;

	receiveImpl(dmContext,ptrMessage, iTimeout);

	try{
		updateAttributes(ptrMessage);
		parse(ptrMessage,dmData);
		buildContext(ptrMessage,dmContext);
		ptrOnReceive->execute(dmContext,dmData);
	}catch(Exception&e ){
		IAS_THROW(RollbackMeException(String("Post Processing Error: ")+e.getName()+":"+e.getInfo()));
	}
}
/*************************************************************************/
void Common::receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
		 	 	 	  API::Message::PtrHolder& ptrMessage,
					  int iTimeout){
	IAS_TRACER;

	receiveImpl(dmContext,ptrMessage,iTimeout);

	try{
		updateAttributes(ptrMessage);

		for(int i=0;i<5;i++){
			dmContext->unsetAttributes();
			buildContext(ptrMessage,dmContext);
		}
	}catch(Exception&e ){
		IAS_THROW(RollbackMeException(String("Post Processing Error: ")+e.getName()+":"+e.getInfo()));
	}
}
/*************************************************************************/
void Common::send(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
				  DM::DataObject* dmData){
	IAS_TRACER;

	ptrOnSend->execute(dmContext,dmData);

	API::Message::PtrHolder ptrMessage(getConnection()->createMessage());

	applyContext(dmContext,ptrMessage);
	updateAttributes(ptrMessage);

	serialize(dmData,ptrMessage);

	ptrMessage->getAttributes()->setValue("DST",destination.getName());

	put(ptrMessage);

	if(ptrMessage->getAttributes()->isSet(API::Attributes::CA_MID))
		dmContext->setMID(ptrMessage->getAttributes()->getMID());
}

/*************************************************************************/
void Common::send(const ::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
				  std::istream& is){
	IAS_TRACER;

	API::Message::PtrHolder ptrMessage(getConnection()->createMessage());

	MiscTools::CopyStreams(is,*ptrMessage->getContent());


	applyContext(dmContext,ptrMessage);
	updateAttributes(ptrMessage);


	ptrMessage->getAttributes()->setValue("DST",destination.getName());

	put(ptrMessage);

	if(ptrMessage->getAttributes()->isSet(API::Attributes::CA_MID))
			dmContext->setMID(ptrMessage->getAttributes()->getMID());
}
/*************************************************************************/
API::Message* Common::get(API::Attributes* pAttributes, int iTimeout){
	IAS_TRACER;
	IAS_THROW(InternalException("Method not allowed!!"))
}
/*************************************************************************/
void Common::put(API::Message* pMessage){
	IAS_TRACER;

	if(!ptrResponder){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"No responeder !!!");
	}else{
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Responding: "<<(void*)this);

		API::Attributes* pAttributes=pMessage->getAttributes();
		pAttributes->setCID(pAttributes->getMID());
		API::Destination outDestination(pAttributes->getReplyTo());

		ptrResponder->respond(pMessage,outDestination);
	}
}
/*************************************************************************/
const API::Destination&  Common::getDestination()const{
	IAS_TRACER;
	return destination;
}
/*************************************************************************/
}
}
}
}
}
