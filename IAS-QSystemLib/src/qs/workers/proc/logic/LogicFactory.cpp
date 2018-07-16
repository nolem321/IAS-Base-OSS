/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/LogicFactory.cpp
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
#include "LogicFactory.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Forwarder.h"
#include "AsyncProxyInput.h"
#include "AsyncProxyOutput.h"
#include "Proxy.h"
#include "Grabber.h"
#include "MatchExecute.h"
#include "ExplicitExecute.h"
#include "RunExecute.h"
#include "DaemonExecute.h"
#include "AttrExecute.h"
#include "StatsProducer.h"
#include "MessagePreview.h"
#include "DistributionAgent.h"
#include "TaskPool.h"

#include <org/invenireaude/qsystem/workers/logic/Forwarder.h>
#include <org/invenireaude/qsystem/workers/logic/Proxy.h>
#include <org/invenireaude/qsystem/workers/logic/AsyncProxyInput.h>
#include <org/invenireaude/qsystem/workers/logic/AsyncProxyOutput.h>
#include <org/invenireaude/qsystem/workers/logic/Grabber.h>
#include <org/invenireaude/qsystem/workers/logic/MatchExecute.h>
#include <org/invenireaude/qsystem/workers/logic/ExplicitExecute.h>
#include <org/invenireaude/qsystem/workers/logic/RunExecute.h>
#include <org/invenireaude/qsystem/workers/logic/DaemonExecute.h>
#include <org/invenireaude/qsystem/workers/logic/AttrExecute.h>
#include <org/invenireaude/qsystem/workers/logic/StatsProducer.h>
#include <org/invenireaude/qsystem/workers/logic/MessagePreview.h>
#include <org/invenireaude/qsystem/workers/logic/DistributionAgent.h>
#include <org/invenireaude/qsystem/workers/logic/TaskPool.h>
#include <org/invenireaude/qsystem/workers/logic/External.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/LogicSpecification.h>


#include "../io/IOFactory.h"

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic{

/*************************************************************************/
LogicFactory::LogicFactory(){
	IAS_TRACER;
	registerExternalLibraires();
}
/*************************************************************************/
LogicFactory::~LogicFactory(){}
/*************************************************************************/
Logic* LogicFactory::createLogic(const ::org::invenireaude::qsystem::workers::logic::Logic* dmLogic,
							WCM::WorkContextManager* pWorkContextManager){
	IAS_TRACER;

	IAS_DFT_FACTORY<Logic>::PtrHolder ptrLogic;

	FactoriesMap::const_iterator it=hmFactories.find(dmLogic->getType());

		if(it != hmFactories.end())
			return (it->second)(dmLogic,pWorkContextManager);

	if(workers::logic::DataFactory::GetInstance()->getForwarderType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<Forwarder>::Create(
				workers::logic::DataFactory::GetInstance()->getForwarderType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getProxyType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<Proxy>::Create(
					workers::logic::DataFactory::GetInstance()->getProxyType()->cast(dmLogic),
					pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getAsyncProxyInputType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<AsyncProxyInput>::Create(
					workers::logic::DataFactory::GetInstance()->getAsyncProxyInputType()->cast(dmLogic),
					pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getAsyncProxyOutputType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<AsyncProxyOutput>::Create(
					workers::logic::DataFactory::GetInstance()->getAsyncProxyOutputType()->cast(dmLogic),
					pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getGrabberType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<Grabber>::Create(
					workers::logic::DataFactory::GetInstance()->getGrabberType()->cast(dmLogic),
					pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getMatchExecuteType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<MatchExecute>::Create(
				workers::logic::DataFactory::GetInstance()->getMatchExecuteType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getExplicitExecuteType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<ExplicitExecute>::Create(
				workers::logic::DataFactory::GetInstance()->getExplicitExecuteType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getRunExecuteType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<RunExecute>::Create(
				workers::logic::DataFactory::GetInstance()->getRunExecuteType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getAttrExecuteType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<AttrExecute>::Create(
				workers::logic::DataFactory::GetInstance()->getAttrExecuteType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getDaemonExecuteType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<DaemonExecute>::Create(
				workers::logic::DataFactory::GetInstance()->getDaemonExecuteType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getTaskPoolType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<TaskPool>::Create(
				workers::logic::DataFactory::GetInstance()->getTaskPoolType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getStatsProducerType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<StatsProducer>::Create(
				workers::logic::DataFactory::GetInstance()->getStatsProducerType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getMessagePreviewType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<MessagePreview>::Create(
				workers::logic::DataFactory::GetInstance()->getMessagePreviewType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getDistributionAgentType()->equals(dmLogic->getType())){
		ptrLogic=IAS_DFT_FACTORY<DistributionAgent>::Create(
				workers::logic::DataFactory::GetInstance()->getDistributionAgentType()->cast(dmLogic),
				pWorkContextManager);

	}else if(workers::logic::DataFactory::GetInstance()->getExternalType()->equals(dmLogic->getType())){

		const workers::logic::External *pExternal = workers::logic::DataFactory::GetInstance()->getExternalType()->cast(dmLogic);

		String strLibrary = "qsmod_"+pExternal->getModule()+".so";

		String strSymbol;

		if(pExternal->isSetFactory())
			strSymbol=pExternal->getFactory();
		else
			strSymbol="_ias_qs_logic_"+pExternal->getModule();

		LogicFactoryFunPtr funLogicFactory = (LogicFactoryFunPtr)
				SYS::GlobalDynamicLibraryStore::GetInstance()->getLibrary(strLibrary)
						->getSymbol(strSymbol);

		ptrLogic=(*funLogicFactory)(pExternal, pWorkContextManager);

	}else{
		IAS_THROW(InternalException(dmLogic->getType()->getName()+"Unknown specification type."));
	}

	return ptrLogic.pass();
}
/*************************************************************************/
void LogicFactory::registerExternalFactory(const DM::Type* pType,
		LogicFactoryFunPtr pFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pType);

	if(hmFactories.count(pType) > 0)
		IAS_THROW(ConfigException(String("This type already has a factory:")+pType->getName()));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Registering factory for:"<<pType->getURI()<<"#"<<pType->getName());

	hmFactories[pType]=pFactory;
}
/*************************************************************************/
void LogicFactory::registerExternalLibraires(){
	IAS_TRACER;

	StringList lstLibNames;

	try{
		EnvTools::GetEnvTokenized("IAS_QS_BUILDIN_LOGIC",lstLibNames);
	}catch(ItemNotFoundException& e){}

	for(StringList::const_iterator it=lstLibNames.begin(); it!=lstLibNames.end(); it++){
		String strLibName="qsmod_"+*it+".so";

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Loading:"<<strLibName);

		try{
			hmLibraries[*it]=IAS_DFT_FACTORY<SYS::DynamicLibrary>::Create(strLibName);

			LogicFactoryFeedPtr pFun=(LogicFactoryFeedPtr)(hmLibraries.at(*it)->getSymbol(String("_ias_qs_lf_")+*it));
			(*pFun)(this);

		}catch(Exception& e){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Failed to load:"<<strLibName<<", "<<e.toString());
		}
	}
}
/*************************************************************************/
workers::logic::Ext::LogicSpecificationPtr LogicFactory::SpecsToDM(const String& strSpecs,
												const StringList& lstParameters){

	IAS_TRACER;


	if(strSpecs.find(".xml") != String::npos){


		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Reading:"<<strSpecs);

		IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder
		ptrXMLHelper (IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(
				workers::logic::DataFactory::GetInstance()->getContaingDataFactory()));

		IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readFile(strSpecs));

		DM::DataObjectPtr dmSpecification=ptrDoc->getRootObject();

		if(workers::logic::DataFactory::GetInstance()->getLogicSpecificationType()->equals(dmSpecification->getType())){
			workers::logic::Ext::LogicSpecificationPtr ptrResult=workers::logic::DataFactory::GetInstance()->getLogicSpecificationType()->cast(dmSpecification);
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Got:"<<DM::XML::XMLHelper::Stringify(workers::logic::DataFactory::GetInstance()->getContaingDataFactory(),ptrResult));
			return ptrResult;
		}

		if(dmSpecification->getType()->isAssignableTo(workers::logic::DataFactory::GetInstance()->getLogicType())){

			workers::logic::Ext::LogicSpecificationPtr ptrResult(
				workers::logic::DataFactory::GetInstance()->getLogicSpecificationType()->createLogicSpecification());

			ptrResult->setLogics(workers::logic::DataFactory::GetInstance()->getLogicType()->cast(dmSpecification));
			return ptrResult;
		}

		IAS_THROW(ConfigException(String("Unexpected type in a logic specification:")+=dmSpecification->getType()->getName()));

	}else{

		String strAction=strSpecs;

		workers::logic::Ext::LogicSpecificationPtr ptrResult(
			workers::logic::DataFactory::GetInstance()->getLogicSpecificationType()->createLogicSpecification());


		bool bDM=true;
		if(strAction[strAction.length()-1] == '!'){
			bDM=false;
			strAction=strAction.substr(0,strAction.length()-1);
		}

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"DM:"<<bDM);

		if(strAction.compare("fwd") == 0){

			workers::logic::Ext::ForwarderPtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getForwarderType()->createForwarder();
			dmLogic->setParseDM(bDM);
			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("extern") == 0 || strAction.compare("js") == 0){

			if(lstParameters.size() == 0)
				IAS_THROW(BadUsageException("Missing parameters: [module id] [parameter 1] [parameter 2] ... "));

			workers::logic::Ext::ExternalPtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getExternalType()->createExternal();
			dmLogic->setParseDM(bDM);

			StringList::const_iterator it=lstParameters.begin();

			if(strAction.compare("js") == 0)
				dmLogic->setModule("js");
			else
				dmLogic->setModule(*it++);

			while(it != lstParameters.end()){
				dmLogic->setArgs(*it++);
			}

			ptrResult->setLogics(dmLogic);


		}else if(strAction.compare("sp") == 0 || strAction.compare("stats_producer") == 0){

			workers::logic::Ext::StatsProducerPtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getStatsProducerType()->createStatsProducer();
			dmLogic->setParseDM(bDM);

			if(lstParameters.size() == 0)
				IAS_THROW(BadUsageException("Missing parameters: connection_uri [exe_list]"));

			StringList::const_iterator it=lstParameters.begin();
			URI uri(*it);

			IO::IOFactory::UpdateConnection(uri,dmLogic->createConnection());

			for(it++; it != lstParameters.end(); it++){
					dmLogic->setLoad(*it);
					dmLogic->setRun(*it);
				}

			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("mp") == 0 || strAction.compare("message_preview") == 0){

			workers::logic::Ext::MessagePreviewPtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getMessagePreviewType()->createMessagePreview();
			dmLogic->setParseDM(bDM);

			if(lstParameters.size() != 1)
				IAS_THROW(BadUsageException("Missing parameter: connection_uri "));

			StringList::const_iterator it=lstParameters.begin();
			URI uri(*it);

			IO::IOFactory::UpdateConnection(uri,dmLogic->createConnection());

			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("da") == 0 || strAction.compare("distribution_agent") == 0){

				workers::logic::Ext::DistributionAgentPtr dmLogic;
				dmLogic=workers::logic::DataFactory::GetInstance()->getDistributionAgentType()->createDistributionAgent();
				dmLogic->setParseDM(bDM);

				StringList::const_iterator it=lstParameters.begin();

				if(it == lstParameters.end())
					IAS_THROW(BadUsageException("Missing connection URI for the Distrubutor Agent parameter."));

				URI uri(*it++);
				IO::IOFactory::UpdateConnection(uri,dmLogic->createConnection());

				if(it != lstParameters.end())
					dmLogic->setAttribute(*it++);

				ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("grab") == 0 || strAction.compare("grabber") == 0){

			workers::logic::Ext::GrabberPtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getGrabberType()->createGrabber();
			dmLogic->setParseDM(bDM);
			StringList::const_iterator it=lstParameters.begin();
			if(it != lstParameters.end())
				dmLogic->setGrabberInput(*it++);
			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("proxy") == 0){

			workers::logic::Ext::ProxyPtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getProxyType()->createProxy();
			dmLogic->setParseDM(bDM);
			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("aproxy") == 0){

			workers::logic::Ext::ProxyPtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getAsyncProxyInputType()->createAsyncProxyInput();
			dmLogic->setParseDM(bDM);
			ptrResult->setLogics(dmLogic);
			dmLogic=workers::logic::DataFactory::GetInstance()->getAsyncProxyOutputType()->createAsyncProxyOutput();
			dmLogic->setParseDM(bDM);
			dmLogic->setInput("output"); //TOOD standarize input/output for proxy
			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("exe") == 0){

			workers::logic::Ext::ExplicitExecutePtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getExplicitExecuteType()->createExplicitExecute();

			for(StringList::const_iterator it=lstParameters.begin();it!=lstParameters.end();it++){
				dmLogic->setLoad(*it);
				dmLogic->setRun(*it);
			}
			dmLogic->setParseDM(bDM);
			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("run") == 0){

				workers::logic::Ext::RunExecutePtr dmLogic;
				dmLogic = workers::logic::DataFactory::GetInstance()->getRunExecuteType()->createRunExecute();

				for(StringList::const_iterator it=lstParameters.begin();it!=lstParameters.end();it++)
					if(it == lstParameters.begin()){
						dmLogic->setLoad(*it);
						dmLogic->setRun(*it);
					}else{
						dmLogic->setParameters(*it);
				}

				dmLogic->setParseDM(bDM);
				ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("match") == 0){

			workers::logic::Ext::MatchExecutePtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getMatchExecuteType()->createMatchExecute();

			for(StringList::const_iterator it=lstParameters.begin();it!=lstParameters.end();it++){
				dmLogic->setLoad(*it);
			}
			dmLogic->setParseDM(bDM);
			ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("attr") == 0){

				workers::logic::Ext::AttrExecutePtr dmLogic;
				dmLogic=workers::logic::DataFactory::GetInstance()->getAttrExecuteType()->createAttrExecute();

				for(StringList::const_iterator it=lstParameters.begin();it!=lstParameters.end();it++){
					dmLogic->setLoad(*it);
				}
				dmLogic->setParseDM(bDM);
				ptrResult->setLogics(dmLogic);

		}else if(strAction.compare("daemon") == 0){

			workers::logic::Ext::DaemonExecutePtr dmLogic;
			dmLogic=workers::logic::DataFactory::GetInstance()->getDaemonExecuteType()->createDaemonExecute();

			for(StringList::const_iterator it=lstParameters.begin();it!=lstParameters.end();it++){
				dmLogic->setLoad(*it);
				dmLogic->setRun(*it);
			}

			dmLogic->setParseDM(bDM);
			ptrResult->setLogics(dmLogic);

		}else{
			IAS_THROW(InternalException(strSpecs+" ? "+strAction+" <= No logic found. TODO better message."));
		}

		return ptrResult;
	}

}
/*************************************************************************/
}
}
}
}
}
