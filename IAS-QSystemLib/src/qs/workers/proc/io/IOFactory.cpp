/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/IOFactory.cpp
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
#include "IOFactory.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <commonlib/sys/ModuleFactoryStore.h>
#include "Input.h"
#include "ConsumerInput.h"
#include "SubscriberInput.h"
#include "BrowserInput.h"
#include "SharedBrowserInput.h"
#include "SharedBrowserWorker.h"
#include "PublisherOutput.h"
#include "ProducerOutput.h"
#include "ResponderOutput.h"
#include "RequesterOutput.h"
#include "ProxyController.h"
#include "IOManager.h"


#include <org/invenireaude/qsystem/workers/io/Input.h>
#include <org/invenireaude/qsystem/workers/io/Output.h>
#include <org/invenireaude/qsystem/workers/io/ConsumerInput.h>
#include <org/invenireaude/qsystem/workers/io/BrowserInput.h>
#include <org/invenireaude/qsystem/workers/io/SharedBrowserInput.h>
#include <org/invenireaude/qsystem/workers/io/SubscriberInput.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/SecureLayer.h>
#include <org/invenireaude/qsystem/workers/ClientIP.h>
#include <org/invenireaude/qsystem/workers/SSLCertificateFile.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {
/*************************************************************************/
static String _HackURI(const String& strSpecs) {

	/*
	 * Some convenient hacks:
	 *   "file:abc" => "file://${PWD}/abc"
	 *   "file:/abc" => "file:///abc"
	 *   "file:stdout" => "file:///stdout"
	 *   etc...
	 */


	String strNewSpec(strSpecs);

	if (strSpecs.find("://") == String::npos) {

		if (strSpecs.find(":/") == String::npos) {

			if (strSpecs.empty()){
				strNewSpec = "file://localhost/stdout";
			}else if(strSpecs.substr(0,11).compare("file:stdout") == 0) {
				strNewSpec = "file://localhost/stdout" + strSpecs.substr(11);
			} else if (strSpecs.substr(0,10).compare("file:stdin") == 0) {
				strNewSpec = "file://localhost/stdin"+ strSpecs.substr(10);
			}else if(strSpecs.substr(0,9).compare("df:stdout") == 0) {
				strNewSpec = "df://localhost/stdout" + strSpecs.substr(9);
			} else if (strSpecs.substr(0,8).compare("df:stdin") == 0) {
				strNewSpec = "df://localhost/stdin"+ strSpecs.substr(8);
			} else if (strSpecs.substr(0,11).compare("timer:clock") == 0) {
				strNewSpec = "timer://localhost/clock"+ strSpecs.substr(11);
			} else {

				String strNew("://localhost");
				strNew += EnvTools::GetEnv("PWD");
				strNew += "/";
				size_t iPos = strSpecs.find(':');
				strNewSpec.replace(iPos, 1, strNew);
			}

		} else {

			String strNew("://localhost/");
			size_t iPos = strSpecs.find(':');
			strNewSpec.replace(iPos, 1, strNew);

		}

	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(), "URI ["<<strNewSpec<<"]");

	return strNewSpec;

}
/*************************************************************************/
IOFactory::IOFactory(const ::io::InputSpecification*  dmInputSpecification,
					 const ::io::OutputSpecification* dmOutputSpecification,
					 IOManager* pIOManager,
					 WCM::WorkContextManager* pWorkContextManager):
                     pIOManager(pIOManager),
					 pWorkContextManager(pWorkContextManager){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(dmInputSpecification);
	IAS_CHECK_IF_NULL(dmOutputSpecification);
	IAS_CHECK_IF_NULL(pIOManager);
	IAS_CHECK_IF_NULL(pWorkContextManager);

	const io::Ext::InputList& lstInputs(dmInputSpecification->getInputsList());

	for(int iIdx=0;iIdx<lstInputs.size();iIdx++){

		String strName(lstInputs.at(iIdx)->getInputName());

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Input: "<<strName);

		if(hmInputs.count(strName))
			IAS_THROW(BadUsageException("Duplicate input name: ")<<strName)

			hmInputs[strName]=lstInputs.at(iIdx);

		if(lstInputs.at(iIdx)->isSetResponderName())
			hmOutputs[lstInputs.at(iIdx)->getResponderName()]=lstInputs.at(iIdx);

		if(lstInputs.at(iIdx)->isSetControllable() && lstInputs.at(iIdx)->getControllable())
			hmControllers[strName]=lstInputs.at(iIdx);
	}

	const io::Ext::OutputList& lstOutputs(dmOutputSpecification->getOutputsList());

	for(int iIdx=0;iIdx<lstOutputs.size();iIdx++){

		String strName(lstOutputs.at(iIdx)->getOutputName());

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Output: "<<strName);

		if(hmOutputs.count(strName))
			IAS_THROW(BadUsageException("Duplicate output name: ")<<strName)

		hmOutputs[strName]=lstOutputs.at(iIdx);

		if(io::DataFactory::GetInstance()->getRequesterOutputType()->equals(lstOutputs.at(iIdx)->getType()))
			hmInputs[strName]=lstOutputs.at(iIdx);

		if(lstOutputs.at(iIdx)->isSetControllable() && lstOutputs.at(iIdx)->getControllable()){

			if(hmControllers.count(strName))
				IAS_THROW(BadUsageException("Duplicate controller name: ")<<strName)

			hmControllers[strName]=lstOutputs.at(iIdx);
		}
	}

}
/*************************************************************************/
IOFactory::~IOFactory()throw(){}
/*************************************************************************/
void IOFactory::createInput(const String& strName){
	IAS_TRACER;

	if(!hmInputs.count(strName))
		IAS_THROW(ItemNotFoundException("Input not found: ")<<strName);

	create(hmInputs[strName]);
}
/*************************************************************************/
void IOFactory::createOutput(const String& strName){
	IAS_TRACER;

	if(!hmOutputs.count(strName))
		IAS_THROW(ItemNotFoundException("Output not found: ")<<strName);

	create(hmOutputs[strName]);

}
/*************************************************************************/
void IOFactory::createController(const String& strName){
	IAS_TRACER;

	if(!hmControllers.count(strName))
		IAS_THROW(ItemNotFoundException("Controller not found: ")<<strName);

	create(hmControllers[strName]);
}
/*************************************************************************/
void IOFactory::create(const DM::DataObject* dmParameters){

	IAS_TRACER;

	if(dmParameters->getType()->isAssignableTo(io::DataFactory::GetInstance()->getInputType())){

		create(io::DataFactory::GetInstance()->getInputType()->cast(dmParameters));

	}else if(dmParameters->getType()->isAssignableTo(io::DataFactory::GetInstance()->getOutputType())){
		create(io::DataFactory::GetInstance()->getOutputType()->cast(dmParameters));
	}else{
		IAS_THROW(InternalException("Unknown IO parameters type: ")<<dmParameters->getType()->getFullName());
	}
}

/*************************************************************************/
void IOFactory::create(const io::Input* dmParameters){

	IAS_TRACER;

	Common *pNew=NULL;

	if(io::DataFactory::GetInstance()->getConsumerInputType()->equals(dmParameters->getType())){
		pIOManager->addInput(dmParameters->getInputName(),
				pNew=IAS_DFT_FACTORY<IO::ConsumerInput>::Create(
						io::DataFactory::GetInstance()->getConsumerInputType()->cast(dmParameters),
						pWorkContextManager));

	}else if(io::DataFactory::GetInstance()->getBrowserInputType()->equals(dmParameters->getType())){
		pIOManager->addInput(dmParameters->getInputName(),
				pNew=IAS_DFT_FACTORY<IO::BrowserInput>::Create(
						io::DataFactory::GetInstance()->getBrowserInputType()->cast(dmParameters),
						pWorkContextManager));

	}else if(io::DataFactory::GetInstance()->getSharedBrowserInputType()->equals(dmParameters->getType())){
			pIOManager->addInput(dmParameters->getInputName(),
				pNew=IAS_DFT_FACTORY<IO::SharedBrowserInput>::Create(
							io::DataFactory::GetInstance()->getSharedBrowserInputType()->cast(dmParameters),
							pWorkContextManager));

	}else if(io::DataFactory::GetInstance()->getSubscriberInputType()->equals(dmParameters->getType())){
		pIOManager->addInput(dmParameters->getInputName(),
				pNew=IAS_DFT_FACTORY<IO::SubscriberInput>::Create(
						io::DataFactory::GetInstance()->getSubscriberInputType()->cast(dmParameters),
						pWorkContextManager));

	}else{
		IAS_THROW(InternalException(dmParameters->getType()->getName()+"Unknown specification type."));
	}

	if(dmParameters->isSetResponderName() && pNew){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"ResponderOutput:  "<<dmParameters->getResponderName());
			pIOManager->addOutput(dmParameters->getResponderName(),	IAS_DFT_FACTORY<IO::ResponderOutput>::Create(pNew));
	}

	if(dmParameters->isSetControllable() && dmParameters->isSetControllable() && pNew){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Controller for Output:  "<<dmParameters->getInputName());
			pIOManager->addController(dmParameters->getInputName(),	IAS_DFT_FACTORY<IO::ProxyController>::Create(pNew));
	}


}
/*************************************************************************/
void IOFactory::create(const io::Output* dmParameters){

	IAS_TRACER;

	Common *pNew=NULL;

	if(io::DataFactory::GetInstance()->getPublisherOutputType()->equals(dmParameters->getType())){
		pIOManager->addOutput(dmParameters->getOutputName(),
				pNew=IAS_DFT_FACTORY<IO::PublisherOutput>::Create(
						io::DataFactory::GetInstance()->getPublisherOutputType()->cast(dmParameters),
						pWorkContextManager));
	}else if(io::DataFactory::GetInstance()->getProducerOutputType()->equals(dmParameters->getType())){
		pIOManager->addOutput(dmParameters->getOutputName(),
				pNew=IAS_DFT_FACTORY<IO::ProducerOutput>::Create(
						io::DataFactory::GetInstance()->getProducerOutputType()->cast(dmParameters),
						pWorkContextManager));

	}else if(io::DataFactory::GetInstance()->getRequesterOutputType()->equals(dmParameters->getType())){

		IAS_DFT_FACTORY<IO::RequesterOutput>::PtrHolder ptrRequesterOutput(
				 IAS_DFT_FACTORY<IO::RequesterOutput>::Create(
										io::DataFactory::GetInstance()->getRequesterOutputType()->cast(dmParameters),
										pWorkContextManager));

			pIOManager->addInput(dmParameters->getOutputName(),
					IAS_DFT_FACTORY<IO::RequesterInputProxy>::Create(ptrRequesterOutput.getPointer()));

			pIOManager->addOutput(dmParameters->getOutputName(), pNew=ptrRequesterOutput.pass());
	}else{
		IAS_THROW(InternalException(dmParameters->getType()->getName()+" Unknown specification type."));
	}

	if(dmParameters->isSetControllable() && dmParameters->isSetControllable() && pNew){
				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Controller for Output:  "<<dmParameters->getOutputName());
				pIOManager->addController(dmParameters->getOutputName(),	IAS_DFT_FACTORY<IO::ProxyController>::Create(pNew));
		}

}
/*************************************************************************/
io::Ext::InputSpecificationPtr IOFactory::InputSpecsToDM(const String& strSpecs){

	IAS_TRACER;

	io::Ext::InputSpecificationPtr ptrResult;

	if(strSpecs.find(':') == String::npos){

		String strDefault;
		String strFile;

		TypeTools::ChopArguments(strSpecs,strFile,strDefault,'@');

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Reading:"<<strFile);

		DM::DataObjectPtr dm(DM::Tools::Formatter::LoadFile(strFile,
														io::DataFactory::GetInstance()->getContaingDataFactory(),
														io::DataFactory::GetInstance()->getInputSpecificationType()));

		ptrResult = io::DataFactory::GetInstance()->getInputSpecificationType()->cast(dm);

		if(!strDefault.empty())
			ptrResult->setDefault(strDefault);

	}else{

		URI uri(_HackURI(strSpecs));

		io::Ext::InputPtr ptrInput;
		ptrInput=io::DataFactory::GetInstance()->getSharedBrowserInputType()->createSharedBrowserInput();
		ptrInput->setTxnMode("NONTXN");
		try{

			if(uri.getValue("mode").compare("browser")==0){
				ptrInput=io::DataFactory::GetInstance()->getBrowserInputType()->createBrowserInput();
			}else if(uri.getValue("mode").compare("subscriber")==0){
				ptrInput=io::DataFactory::GetInstance()->getSubscriberInputType()->createSubscriberInput();
			}else if(uri.getValue("mode").compare("consumer")==0 || uri.getValue("mode").compare("input")==0){
				ptrInput=io::DataFactory::GetInstance()->getConsumerInputType()->createConsumerInput();
			}

		}catch(...){};

		try{

			String strFormat=uri.getValue("format");

			Ext::AttributeUpdatePtr ptrAttributeUpdate(
					DataFactory::GetInstance()->getAttributeUpdateType()->createAttributeUpdate());

			ptrAttributeUpdate->setName("FMT");
			ptrAttributeUpdate->setValue(strFormat);
			ptrAttributeUpdate->setOverride(true);

			ptrInput->getAttrUpdatesList().add(ptrAttributeUpdate);

		}catch(...){};


		UpdateAttributes(uri,ptrInput->getAttrUpdatesList());
		UpdateConnection(uri,ptrInput->createConnection());

		ptrInput->setDestination(uri.getPath());

		try{
			ptrInput->setTimeout(TypeTools::StringToInt(uri.getValue("timeout")));
		}catch(...){};

		try{
			TypeTools::StringToInt(uri.getValue("ctrl"));
			ptrInput->setControllable(true);
		}catch(...){};

		try{
			ptrInput->setResponderName(uri.getValue("responderName"));
		}catch(...){};

		try{
			uri.getValue("txn").compare("y");
			ptrInput->setTxnMode("TXN");
		}catch(ItemNotFoundException& e){}

		ptrInput->setInputName("input");

		ptrResult=io::DataFactory::GetInstance()->getInputSpecificationType()->createInputSpecification();
		ptrResult->setInputs(ptrInput);
	}

	return ptrResult;
}
/*************************************************************************/
io::Ext::OutputSpecificationPtr IOFactory::OutputSpecsToDM(const String& strSpecs){

	IAS_TRACER;

	io::Ext::OutputSpecificationPtr ptrResult;

	if(!strSpecs.empty() && strSpecs.find(':') == String::npos){

		String strDefault;
		String strFile;

		TypeTools::ChopArguments(strSpecs,strFile,strDefault,'@');

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Reading:"<<strFile);

		DM::DataObjectPtr dm(DM::Tools::Formatter::LoadFile(strFile,
													io::DataFactory::GetInstance()->getContaingDataFactory(),
													io::DataFactory::GetInstance()->getOutputSpecificationType()));

		ptrResult = io::DataFactory::GetInstance()->getOutputSpecificationType()->cast(dm);

		if(!strDefault.empty())
			ptrResult->setDefault(strDefault);

	}else{

		ptrResult=io::DataFactory::GetInstance()->getOutputSpecificationType()->createOutputSpecification();

		if(strSpecs.compare("dummy:")==0)
			return ptrResult;

		URI uri(_HackURI(strSpecs));

		io::Ext::OutputPtr ptrOutput;
		ptrOutput=io::DataFactory::GetInstance()->getProducerOutputType()->createProducerOutput();

		try{
			if(uri.getValue("mode").compare("publisher")==0)
				ptrOutput=io::DataFactory::GetInstance()->getPublisherOutputType()->createPublisherOutput();
		}catch(...){};

		try{
			if(uri.getValue("mode").compare("requester")==0){
				io::Ext::RequesterOutputPtr dm(io::DataFactory::GetInstance()->getRequesterOutputType()->createRequesterOutput());
				ptrOutput=dm;
				dm->setInputDestination(uri.getValue("inputDestination"));
			}
		}catch(...){};

		try{

			String strFormat=uri.getValue("format");

			Ext::AttributeUpdatePtr ptrAttributeUpdate(
					DataFactory::GetInstance()->getAttributeUpdateType()->createAttributeUpdate());

			ptrAttributeUpdate->setName("FMT");
			ptrAttributeUpdate->setValue(strFormat);
			ptrAttributeUpdate->setOverride(true);

			ptrOutput->getAttrUpdatesList().add(ptrAttributeUpdate);

		}catch(...){};

		try{
			ptrOutput->setTimeout(TypeTools::StringToInt(uri.getValue("timeout")));
		}catch(...){};

		ptrOutput->setOutputName("output");

		UpdateAttributes(uri,ptrOutput->getAttrUpdatesList());
		UpdateConnection(uri, ptrOutput->createConnection());

		ptrOutput->setDestination(uri.getPath());

		try{
			uri.getValue("txn").compare("y");
			ptrOutput->setTxnMode("TXN");
		}catch(ItemNotFoundException& e){}

		ptrResult->setOutputs(ptrOutput);

		ptrOutput=io::DataFactory::GetInstance()->getProducerOutputType()->createProducerOutput();
		ptrOutput->setOutputName("error");
		ptrOutput->createConnection();
		ptrOutput->getConnection()->setProtocol("file");
		ptrOutput->getConnection()->setHost("localhost");
		ptrOutput->setDestination("stdout_fmt");

		ptrResult->setOutputs(ptrOutput);
	}

	return ptrResult;
}
/*************************************************************************/
void IOFactory::UpdateConnection(const URI& uri, Connection *pConnection) {

	IAS_TRACER;


	if(uri.getProtocol().compare("registry") == 0){
		pConnection->setAlias(uri.getHost());
		return;
	}

	pConnection->setProtocol(uri.getProtocol());
	pConnection->setHost(uri.getHost());

	if(uri.getPort() > 0)
		pConnection->setPort(uri.getPort());

	try {

		String strFileName(uri.getValue("sslCertFile"));
		String strPassword(uri.getValue("sslCertPassword"));

		Ext::SSLCertificateFilePtr dmCertificateFile(
				DataFactory::GetInstance()->createSSLCertificateFile());

		dmCertificateFile->setFileName(strFileName);
		dmCertificateFile->setPassword(strPassword);

		pConnection->createSsl()->setCert(dmCertificateFile);

		try{
			if(uri.getValue("sslVerifyPeerCert").compare("Y") == 0)
				pConnection->getSsl()->setVerifyPeerCert(true);
		}catch(ItemNotFoundException& e){}

		try{
			if(uri.getValue("sslVerifyPeerIP").compare("Y") == 0)
				pConnection->getSsl()->setVerifyPeerIP(true);
		}catch(ItemNotFoundException& e){}

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),
				"SSL ["<<strFileName<<","<<strPassword<<"]");

	} catch (ItemNotFoundException& e) {
	}
	try {
		String strInterface(uri.getValue("localIP"));
		pConnection->createClient()->setInterface(strInterface);
	} catch (ItemNotFoundException& e) {
	}
}
/*************************************************************************/
void IOFactory::UpdateAttributes(const URI& uri,
								 ::org::invenireaude::qsystem::workers::Ext::AttributeUpdateList& lstAttrUpdates){
	IAS_TRACER;


	for(URI::const_iterator it = uri.begin(); it != uri.end(); it++)
		if(it->first[0] == '*'){

		Ext::AttributeUpdatePtr ptrAttributeUpdate(
			DataFactory::GetInstance()->getAttributeUpdateType()->createAttributeUpdate());

		ptrAttributeUpdate->setName(it->first.substr(1));
		ptrAttributeUpdate->setValue(it->second);
		ptrAttributeUpdate->setOverride(true);

		lstAttrUpdates.add(ptrAttributeUpdate);

	}

}
/*************************************************************************/
}
}
}
}
}
