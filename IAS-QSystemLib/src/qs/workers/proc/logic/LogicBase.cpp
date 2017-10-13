/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/LogicBase.cpp
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
#include "LogicBase.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <qs/workers/proc/io/Output.h>

#include "../io/IOManager.h"
#include "../GlobalContext.h"

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include "../exception/RollbackMeException.h"

#include <qs/workers/proc/wcm/WorkContextManager.h>


using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
LogicBase::LogicBase(const ::org::invenireaude::qsystem::workers::logic::Logic* dmLogic,
		             WCM::WorkContextManager*       pWorkContextManager):
		pWorkContextManager(pWorkContextManager),
		bDM(! dmLogic->isSetParseDM() || dmLogic->getParseDM()),
		pInput(NULL),
		pOutput(NULL),
		pError(NULL){
	IAS_TRACER;

	if(dmLogic->isSetInput())
		strInputName=dmLogic->getInput();

	if(dmLogic->isSetOutput())
		strOutputName=dmLogic->getOutput();

	if(dmLogic->isSetError())
		strErrorName=dmLogic->getError();

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"input:"<<strInputName);
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"output:"<<strOutputName);
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"error:"<<strErrorName);

	if(bDM)
		ptrContext = IAS_DFT_FACTORY<DataModelContext>::Create(this);
	else
		ptrContext = IAS_DFT_FACTORY<RawContext>::Create(this);
}
/*************************************************************************/
LogicBase::~LogicBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void LogicBase::receive(bool bNoWait){
	IAS_TRACER;
	ptrContext->receive(bNoWait);
}
/*************************************************************************/
void LogicBase::compute(){
	IAS_TRACER;
	ptrContext->compute();
}
/*************************************************************************/
void LogicBase::DataModelContext::receive(bool bNoWait){
	IAS_TRACER;
	dmContext = workers::DataFactory::GetInstance()->getContextType()->createContext();
	pLogicBase->getInput()->receive(dmContext,dmData, !bNoWait ? IO::Input::CDefaultTimeout : 0);
}
/*************************************************************************/
void LogicBase::DataModelContext::compute(){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Computing ...");
	pLogicBase->computeDM(dmContext,dmData);
}
/*************************************************************************/
void LogicBase::RawContext::receive(bool bNoWait){
	IAS_TRACER;
	dmContext = workers::DataFactory::GetInstance()->getContextType()->createContext();
	pLogicBase->getInput()->receive(dmContext,ptrMessage, !bNoWait ? IO::Input::CDefaultTimeout : 0);
}
/*************************************************************************/
void LogicBase::RawContext::compute(){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Computing ...");
	pLogicBase->computeRaw(dmContext,ptrMessage);
}
/*************************************************************************/
void LogicBase::computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							 API::Message* pMessage){

	workers::Ext::RoutingPtr dmRouting;
	dmRouting = workers::DataFactory::GetInstance()->getRoutingType()->createRouting();

	DM::DataObjectPtr dm(dmRouting);
	computeDM(dmContext,dm);

	if(dmRouting->isSetValid() && dmRouting->getValid()){

		if(dmRouting->isSetTarget()){
			pWorkContextManager->getIOManager()->getOutput(dmRouting->getTarget())->
				send(dmContext,*pMessage->getContent());

			(*pMessage->getContent()).clear();
			(*pMessage->getContent()).seekg(0);;
		}

		const DM::Default::Ext::StringList& lstTargets(dmRouting->getTargetsList());

		for(int iIdx=0; iIdx<lstTargets.size();iIdx++){
			pWorkContextManager->getIOManager()->getOutput(lstTargets.at(iIdx))->
							send(dmContext,*pMessage->getContent());

			(*pMessage->getContent()).clear();
			(*pMessage->getContent()).seekg(0);
		}

	}

}
/*************************************************************************/
IO::Input *LogicBase::getInput(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Input Name: "<<strInputName);

	if(!pInput){

		if(strInputName.empty())
			pInput=pWorkContextManager->getIOManager()->getDefaultInput();
		else
			pInput=pWorkContextManager->getIOManager()->getInput(strInputName);

	}

	return pInput;
}
/*************************************************************************/
IO::Output  *LogicBase::getOutput(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Output Name: "<<strOutputName);

	if(!pOutput){

		if(strOutputName.empty())
			pOutput=pWorkContextManager->getIOManager()->getDefaultOutput();
		else
			pOutput=pWorkContextManager->getIOManager()->getOutput(strOutputName);

	}

	return pOutput;
}
/*************************************************************************/
IO::Output  *LogicBase::getError(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Error Output: "<<strErrorName);

	if(!pError){

		if(strErrorName.empty())
			pError=pWorkContextManager->getIOManager()->getDefaultError();
		else
			pError=pWorkContextManager->getIOManager()->getOutput(strErrorName);
	}

	return pError;
}
/*************************************************************************/
void LogicBase::tryError(workers::Ext::ContextPtr& dmContext,
			  	  	     DM::DataObjectPtr& dmData,
						 Exception& e){
	IAS_TRACER;

	StringStream ssInfo;
	ssInfo<<e.getName()<<":"<<e.getInfo();

	workers::Attribute* pAttribute=dmContext->createAttributes();
	pAttribute->setName("IAS_PROXY_ERROR");
	pAttribute->setValue(ssInfo.str());

	try{
		getError()->send(dmContext,dmData);
	}catch(Exception& e2){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Send to error failed, execute method"
			" does not know what to do with this exception:"+e2.toString() + e.toString());
		IAS_THROW(RollbackMeException(ssInfo.str()));
	}

}
/*************************************************************************/
void LogicBase::tryError(workers::Ext::ContextPtr& dmContext,
			  	  	     API::Message* pMessage,
						 Exception& e){
	IAS_TRACER;

	StringStream ssInfo;
	ssInfo<<e.getName()<<":"<<e.getInfo();

	workers::Attribute* pAttribute=dmContext->createAttributes();
	pAttribute->setName("IAS_LOGIC_ERROR");
	pAttribute->setValue(ssInfo.str());

	try{
		pMessage->getContent()->clear();
		pMessage->getContent()->seekg(0);

		getError()->send(dmContext,*pMessage->getContent());
	}catch(Exception& e2){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Send to error failed, execute method"
			" does not know what to do with this exception:"+e2.toString() + e.toString());
		IAS_THROW(RollbackMeException(ssInfo.str()));
	}

}
/*************************************************************************/
String LogicBase::getAttribute(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							   const String& strName)const{
	IAS_TRACER;
	workers::Ext::AttributeList& lstAttributes(dmContext->getAttributesList());

	for(int iIdx=0; iIdx < lstAttributes.size(); iIdx++){
		workers::Attribute* pAttribute=lstAttributes.at(iIdx);
		if(pAttribute->getName().compare(strName) == 0)
			return pAttribute->getValue();
	}

	IAS_THROW(ItemNotFoundException(String("Attribute: ")+strName));
}
/*************************************************************************/
void LogicBase::setAttribute(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							 const String& strName,
							 const String& strValue)const{
	IAS_TRACER;

	workers::Ext::AttributeList& lstAttributes(dmContext->getAttributesList());

	for(int iIdx=0; iIdx < lstAttributes.size(); iIdx++){
		workers::Attribute* pAttribute=lstAttributes.at(iIdx);
		if(pAttribute->getName().compare(strName) == 0){
			pAttribute->setValue(strValue);
			return;
		}

	}

	workers::Attribute* pAttribute=dmContext->createAttributes();
	pAttribute->setName(strName);
	pAttribute->setValue(strValue);


}
/*************************************************************************/
}
}
}
}
}
