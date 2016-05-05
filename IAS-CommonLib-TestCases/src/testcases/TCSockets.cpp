/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSockets.cpp
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
#include "commonlib/commonlib.h"
#include "commonlib/net/BlockIOBuffer.h"
#include "commonlib/net/BlockIOStream.h"

#include "commonlib/net/ssl/Environment.h"
#include "commonlib/net/ssl/SecureLayer.h"
#include "commonlib/net/ssl/BlockIO.h"
#include "commonlib/net/ssl/Context.h"
#include "commonlib/net/ssl/CertificateX509.h"

#include "TCSockets.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

namespace IAS{
using namespace Net;
namespace TCT{

/*************************************************************************/
TCSockets::TCSockets(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCSockets::~TCSockets() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCSockets::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("c01",&::IAS::TCT::TCSockets::case01);
	theTestRunner.addCase("c02",&::IAS::TCT::TCSockets::case02);
	theTestRunner.addCase("c03",&::IAS::TCT::TCSockets::case03);
	theTestRunner.addCase("c04",&::IAS::TCT::TCSockets::case04);
	TestUnit::init("TCSockets",&theTestRunner,pTestSuite);
}

static const String _test_message("12345678901234567890123456789012345678901234567890");
static const String C_ServerName("localhost");
static const String C_ClientIP("localhost");
static const int    C_TestClientPort(50002);
static const int    C_TestPort(50000);
static const int    C_TestPortAsync(50001);

/*************************************************************************/
/* case 01 - simple client/server.
/*************************************************************************/
TCSockets::SyncServer::SyncServer():
		server(Peer(C_TestPort)),
		Thread(this){
	IAS_TRACER;
}
/*************************************************************************/
void TCSockets::SyncServer::run(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Net::FileHandle>::PtrHolder ptrFileHandle(server.accept());
	serve(ptrFileHandle);
}
/*************************************************************************/
void TCSockets::SyncServer::serve(Net::IBlockIO *pBlockIO){
	IAS_TRACER;

	Net::BlockIOStream fhs(pBlockIO);

	StringStream ssData(_test_message);
	fhs.exceptions(std::ios_base::badbit);
	MiscTools::CopyStreams(ssData,fhs);
}
/*************************************************************************/
TCSockets::SyncClient::SyncClient():
		client(Peer(C_ServerName,C_TestPort),Peer(C_ClientIP,C_TestClientPort)){}
/*************************************************************************/
void TCSockets::SyncClient::run(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Net::FileHandle>::PtrHolder ptrFileHandle(client.connect());
	serve(ptrFileHandle);
}
/*************************************************************************/
void TCSockets::SyncClient::serve(Net::IBlockIO *pBlockIO){
	IAS_TRACER;

	Net::BlockIOStream fhs(pBlockIO);
	fhs.exceptions(std::ios_base::badbit);

	MiscTools::CopyStreams(fhs,ssInput);

	std::cerr<<"Got:"<<ssInput.str()<<std::endl;

	if(ssInput.str().compare(_test_message) != 0)
		IAS_THROW(InternalException("Do not match"));
}
/*************************************************************************/
void TCSockets::case01(){
	IAS_TRACER;

	SyncServer server;
	server.start();

	SyncClient client;
	client.run();

	server.join();
}
/*************************************************************************/
class ServerEventHandler: public ::IAS::Net::EventHandler {
public:

	virtual ~ServerEventHandler()throw(){};

protected:
	ServerEventHandler(Net::FileHandle* pFileHandle, bool bInitialize=true) :
			EventHandler(pFileHandle),
			ptrFileHandle(pFileHandle),
			iCount(0), bDone(false) {

		if(bInitialize)
			initialize(ptrFileHandle);
	}

	void initialize(Net::IBlockIO* pBlockIO){
		this->pBlockIO = pBlockIO;

		ptrInputDataPump = IAS_DFT_FACTORY<Net::Async::InputDataPump>::Create<Net::IBlockIO*,std::ostream&>(pBlockIO,ssInput);

		subscribe(ET_InputReady);

		IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"Service started."<<(void*)this);
	};

	virtual void onInputReady() {

		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"call:"<<++iCount);

		try {

			if(ptrInputDataPump->pump()) {
				IAS_LOG(LogLevel::INSTANCE.isInfo(),"read some data, total="<<ssInput.str().length());
				return;
			}

			if(!bDone) {
				if(ssInput.str().compare(_test_message) == 0) {

					IAS_LOG(LogLevel::INSTANCE.isInfo(),"input length="<<ssInput.str().length()<<"val="<<ssInput.str());

					for(int i=0;i<10000;i++)
						ssOutput<<ssInput.str();

					ssOutput<<"!"<<ssInput.str();

					IAS_LOG(LogLevel::INSTANCE.isInfo(),"output length="<<ssOutput.str().length());

					ptrOutputDataPump = IAS_DFT_FACTORY<Net::Async::OutputDataPump>::Create<Net::IBlockIO*,std::istream&>(pBlockIO,ssOutput);
					ptrInputDataPump = IAS_DFT_FACTORY<Net::Async::InputDataPump>::Create<Net::IBlockIO*,std::ostream&>(pBlockIO,ssInput);

					subscribe(ET_OutputReady);

				} else {
					IAS_LOG(LogLevel::INSTANCE.isInfo(),"bad data, total="<<ssInput.str().length());
				}
			}

			bDone=true;

		} catch(EndOfDataException& e) {
			IAS_LOG(LogLevel::INSTANCE.isInfo(),"setDeletePending");
			setDeletePending();
		}
	}

	virtual void onOutputReady() {

		if(! !ptrOutputDataPump) {

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"pumping !");

			if(!ptrOutputDataPump->pump()) {
				ptrOutputDataPump=0;
				IAS_LOG(LogLevel::INSTANCE.isInfo(),"End of server pumping !");
				unsubscribe(ET_OutputReady);
			}
		}else{
			IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"empty call!");
		}

		//TODO (L) remove ? client closes ?
	}

	StringStream ssOutput;
	StringStream ssInput;

	int iCount;
	bool bDone;

	IAS_DFT_FACTORY<Net::Async::OutputDataPump>::PtrHolder ptrOutputDataPump;
	IAS_DFT_FACTORY<Net::Async::InputDataPump>::PtrHolder ptrInputDataPump;

	Net::IBlockIO*                              pBlockIO;
	IAS_DFT_FACTORY<Net::FileHandle>::PtrHolder ptrFileHandle;

	friend class IAS::Factory<ServerEventHandler>;
};
/*************************************************************************/
class TestServiceFactory : public Net::Socket::ServiceHandleFactory{
public:

	virtual ~TestServiceFactory() throw(){};

	virtual void createService(Net::FileHandle* pConnection){
		IAS_TRACER;
		pMonitor->addHandler(IAS_DFT_FACTORY<ServerEventHandler>::Create(pConnection));
	}

	TestServiceFactory(Net::EventMonitor* pMonitor):
		pMonitor(pMonitor){};

	Net::EventMonitor* pMonitor;
};
/*************************************************************************/
TCSockets::AsyncClient::AsyncClient():
		Thread(this),
		client(Peer(C_ServerName,C_TestPortAsync),Peer(C_ClientIP)){}
/*************************************************************************/
void TCSockets::AsyncClient::run(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Net::FileHandle>::PtrHolder ptrFileHandle(client.connect());

	try{
		serve(ptrFileHandle);
	}catch(Exception& e){
		e.printToStream(ssException);
	}
}
/*************************************************************************/
void TCSockets::AsyncClient::serve(Net::IBlockIO *pBlockIO){
		IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"Client started.");
	StringStream ssData(_test_message);

	IAS_DFT_FACTORY<Net::Async::OutputDataPump>::PtrHolder ptrClientPump(
					IAS_DFT_FACTORY<Net::Async::OutputDataPump>::Create<Net::IBlockIO*,std::istream&>(pBlockIO,ssData));

	usleep(rand()%250000);

	ptrClientPump->pump();

	int c;
	long iCount=0;
	usleep(rand()%250000);

	StringStream ssInput;
	IAS_DFT_FACTORY<Net::Async::InputDataPump>::PtrHolder ptrClientInputPump(
					IAS_DFT_FACTORY<Net::Async::InputDataPump>::Create<Net::IBlockIO*,std::ostream&>(pBlockIO,ssInput));

	ptrClientInputPump->pump();

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"ssInput:"<<ssInput.str().substr(0,100));

	StringStream ssResult;
	while( (c=(ssInput).get()) != EOF){
		iCount++;
			ssResult<<(char)c;
			if(c=='!'){
				ssResult.str("");
				ssResult.clear();
			}
		}

		IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"Count="<<iCount<<", found="<<ssResult.str().length());


	if(ssResult.str().compare(_test_message) != 0)
		IAS_THROW(InternalException("Do not match"));

	if(iCount != ssResult.str().length()*10001 + 1)
		IAS_THROW(InternalException("Do not match 2"));

	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"Client ended.");
}

/*************************************************************************/
void TCSockets::case02(){
	IAS_TRACER;

	std::cerr<<"Wait up to 60s."<<std::endl;

	Net::EventMonitor::PtrHolder ptrMonitor( Net::EventMonitor::Create() );

	IAS_DFT_FACTORY<TestServiceFactory>::PtrHolder ptrFactory(
		IAS_DFT_FACTORY<TestServiceFactory>::Create(ptrMonitor));

	Net::Server server(C_TestPortAsync);

	ptrMonitor->addHandler(IAS_DFT_FACTORY<Net::Socket::EventHandler>::Create(ptrFactory.pass(),&server));

	EventMonitor::ThreadedWorker worker(ptrMonitor);
	worker.start();

	AsyncClient client[10];

	for(int i=0;i<10;i++)
		client[i].start();

	for(int i=0;i<10;i++)
		client[i].join();

	worker.stop();
	worker.join();

	for(int i=0;i<10;i++)
		if(!client[i].ssException.str().empty())
			IAS_THROW(BadUsageException(client[i].ssException.str()));

}

/*************************************************************************/
/* case 03 - simple client/server SSL
/*************************************************************************/

/*************************************************************************/
void TCSockets::SyncServerSSL::run(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Net::SSL::Context>::PtrHolder      ptrContext(IAS_DFT_FACTORY<Net::SSL::Context>::Create("/home/albert/openssl/s_server/server.pem","password"));

	ptrContext->setCipher("NULL-MD5");

	IAS_DFT_FACTORY<Net::FileHandle>::PtrHolder       ptrFileHandle(server.accept());
	IAS_DFT_FACTORY<Net::SSL::BlockIO>::PtrHolder     ptrBIO(IAS_DFT_FACTORY<Net::SSL::BlockIO>::Create<FileHandle*>(ptrFileHandle));
	IAS_DFT_FACTORY<Net::SSL::SecureLayerServer>::PtrHolder ptrSecureLayer(IAS_DFT_FACTORY<Net::SSL::SecureLayerServer>::Create(ptrContext.getPointer(),ptrBIO.getPointer()));

	ptrSecureLayer->setVerification(true);

	ptrSecureLayer->accept();

	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"vr="<<ptrSecureLayer->getVerificationResult());

	IAS_DFT_FACTORY<Net::SSL::CertificateX509>::PtrHolder ptrX509(ptrSecureLayer->getPeerCertifcate());

	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"issuer:  "<<ptrX509->getIssuerName());
	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"subject: "<<ptrX509->getSubjectName());

	Net::SSL::CertificateX509::NamesMap hmNames;
	ptrX509->getSubject(hmNames);

	for(Net::SSL::CertificateX509::NamesMap::const_iterator it=hmNames.begin(); it != hmNames.end(); it++)
		IAS_LOG(LogLevel::INSTANCE.isInfo()||true,it->first<<"="<<it->second);

	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"O="<<ptrX509->getSubjectField("O"));
	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"CN="<<ptrX509->getSubjectCN());
	try{
		serve(ptrSecureLayer);
	}catch(Exception& e){
		e.printToStream(std::cerr);
	}
}
/*************************************************************************/
void TCSockets::SyncClientSSL::run(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Net::SSL::Context>::PtrHolder ptrContext(IAS_DFT_FACTORY<Net::SSL::Context>::Create("/home/albert/openssl/s_server/client.pem","password"));

	ptrContext->setCipher("NULL-MD5");

	IAS_DFT_FACTORY<Net::FileHandle>::PtrHolder ptrFileClient(client.connect());
	IAS_DFT_FACTORY<Net::SSL::BlockIO>::PtrHolder ptrBIO(IAS_DFT_FACTORY<Net::SSL::BlockIO>::Create<FileHandle*>(ptrFileClient));
	IAS_DFT_FACTORY<Net::SSL::SecureLayerClient>::PtrHolder ptrSecureLayer(IAS_DFT_FACTORY<Net::SSL::SecureLayerClient>::Create(ptrContext.getPointer(),ptrBIO.getPointer()));

	ptrSecureLayer->setVerification(true);


	ptrSecureLayer->connect();

	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"cipher="<<ptrSecureLayer->getCurrentCipher());
	IAS_DFT_FACTORY<Net::SSL::CertificateX509>::PtrHolder ptrX509(ptrSecureLayer->getPeerCertifcate());

	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"issuer:  "<<ptrX509->getIssuerName());
	IAS_LOG(LogLevel::INSTANCE.isInfo()||true,"subject: "<<ptrX509->getSubjectName());

	serve(ptrSecureLayer);
}
/*************************************************************************/
void TCSockets::case03(){
	IAS_TRACER;

	Net::SSL::Environment::GetInstance();

	SyncServerSSL server;
	server.start();

	SyncClientSSL client;
	client.run();

	server.join();

}

/*************************************************************************/
/* case 04 - asynchronous client/server SSL
/*************************************************************************/
class ServerEventHandlerSSL : public ServerEventHandler{
public:

	virtual ~ServerEventHandlerSSL()throw(){};

	ServerEventHandlerSSL(FileHandle* pConnection,Net::SSL::Context*pContext):
		ServerEventHandler(pConnection,false),
		bAccepted(false){

		ptrBIO=IAS_DFT_FACTORY<Net::SSL::BlockIO>::Create<FileHandle*>(pConnection);
		ptrSecureLayer=IAS_DFT_FACTORY<Net::SSL::SecureLayerServer>::Create(pContext,ptrBIO.getPointer());

		subscribe(ET_OutputReady);
		subscribe(ET_InputReady);

		accept();
	}


	void accept(){
		IAS_TRACER;

		if(!ptrSecureLayer->accept()){
			bAccepted=true;
			unsubscribe(ET_OutputReady);
			unsubscribe(ET_InputReady);
			initialize(ptrSecureLayer);
		}
	}

	virtual void onInputReady(){
		if(!bAccepted)
			accept();
		else
			ServerEventHandler::onInputReady();
	}

	virtual void onOutputReady(){
		if(!bAccepted)
			accept();
		else
			ServerEventHandler::onOutputReady();
	}

protected:

	IAS_DFT_FACTORY<Net::SSL::BlockIO>::PtrHolder           ptrBIO;
	IAS_DFT_FACTORY<Net::SSL::SecureLayerServer>::PtrHolder ptrSecureLayer;

	bool bAccepted;
	friend class IAS::Factory<ServerEventHandlerSSL>;
};
/*************************************************************************/
class TestServiceFactorySSL : public TestServiceFactory{
public:

	virtual ~TestServiceFactorySSL() throw(){};

	virtual void createService(Net::FileHandle* pConnection){
		IAS_TRACER;
		pMonitor->addHandler(IAS_DFT_FACTORY<ServerEventHandlerSSL>::Create(pConnection,ptrContext.getPointer()));
	}

	TestServiceFactorySSL(Net::EventMonitor* pMonitor):
		TestServiceFactory(pMonitor){
		ptrContext = IAS_DFT_FACTORY<Net::SSL::Context>::Create("/home/albert/openssl/s_server/server.pem","password");
	};

	IAS_DFT_FACTORY<Net::SSL::Context>::PtrHolder     ptrContext;
};
/*************************************************************************/
void TCSockets::AsyncClientSSL::run(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Net::SSL::Context>::PtrHolder ptrContext(IAS_DFT_FACTORY<Net::SSL::Context>::Create("/home/albert/openssl/s_server/client.pem","password"));

	IAS_DFT_FACTORY<Net::FileHandle>::PtrHolder ptrFileClient(client.connect());
	IAS_DFT_FACTORY<Net::SSL::BlockIO>::PtrHolder ptrBIO(IAS_DFT_FACTORY<Net::SSL::BlockIO>::Create<FileHandle*>(ptrFileClient));
	IAS_DFT_FACTORY<Net::SSL::SecureLayerClient>::PtrHolder ptrSecureLayer(IAS_DFT_FACTORY<Net::SSL::SecureLayerClient>::Create(ptrContext.getPointer(),ptrBIO.getPointer()));

	ptrSecureLayer->connect();
	serve(ptrSecureLayer);
}
/*************************************************************************/
void TCSockets::case04(){
	IAS_TRACER;

	Net::SSL::Environment::GetInstance();

	std::cerr<<"Wait up to 60s."<<std::endl;

	Net::EventMonitor::PtrHolder ptrMonitor( Net::EventMonitor::Create() );

	IAS_DFT_FACTORY<TestServiceFactorySSL>::PtrHolder ptrFactory(
		IAS_DFT_FACTORY<TestServiceFactorySSL>::Create(ptrMonitor));

	Net::Server server(C_TestPortAsync);

	ptrMonitor->addHandler(IAS_DFT_FACTORY<Net::Socket::EventHandler>::Create(ptrFactory.pass(),&server));

	AsyncClientSSL client[10];

	EventMonitor::ThreadedWorker worker(ptrMonitor);
	worker.start();

	for(int i=0;i<10;i++)
		client[i].start();

	for(int i=0;i<10;i++)
		client[i].join();

	worker.stop();
	worker.join();

	for(int i=0;i<10;i++)
		if(!client[i].ssException.str().empty())
			IAS_THROW(BadUsageException(client[i].ssException.str()));

}

/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */

