/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/client/ssl/BlockIOWrapperFactory.cpp
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
#include "BlockIOWrapperFactory.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/SecureLayer.h>
#include <org/invenireaude/qsystem/workers/SSLCertificate.h>
#include <org/invenireaude/qsystem/workers/SSLCertificateFile.h>

#include <commonlib/net/http/http.h>

using namespace ::org::invenireaude::qsystem::workers;
namespace IAS {
namespace QS {
namespace Net {
namespace Sync{
namespace Client {
namespace SSL {
/*************************************************************************/
BlockIOWrapperFactory::BlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection):
		Sync::Client::BlockIOWrapperFactory(dmConnection){
	IAS_TRACER;

	//TODO (M) common toolkit for this SSL::Context creation based on DM.


	const SSLCertificateFile *dmSSLCertificateFile=DataFactory::GetInstance()->getSSLCertificateFileType()->cast(dmConnection->getSsl()->getCert());

	String strFile(dmSSLCertificateFile->getFileName());
	String strPassword(dmSSLCertificateFile->getPassword());

	ptrContext=IAS_DFT_FACTORY<IAS::Net::SSL::Context>::Create(strFile,strPassword);

	//ptrContext=IAS_DFT_FACTORY<IAS::Net::SSL::Context>::Create("","");
}
/*************************************************************************/
BlockIOWrapperFactory::~BlockIOWrapperFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
class BlockIOWrapper : public Sync::BlockIOWrapper{
public:
	BlockIOWrapper(IAS::Net::SSL::Context* pContext, IAS::Net::FileHandle* pFileHandle):
		Sync::BlockIOWrapper(pFileHandle),
		pFileHandle(pFileHandle){

		ptrBIO = IAS_DFT_FACTORY<IAS::Net::SSL::BlockIO>::Create(pFileHandle);
		ptrSecureLayer=IAS_DFT_FACTORY<IAS::Net::SSL::SecureLayerClient>::Create(pContext,ptrBIO.getPointer());

	}

	virtual IAS::Net::IBlockIO *getBlockIO()const{
		return ptrSecureLayer;
	};

	inline IAS::Net::SSL::SecureLayerClient *getSecureLayer()const{
		return ptrSecureLayer;
	};

	inline IAS::Net::FileHandle* getFileHandle()const{
		return pFileHandle;
	};

protected:
	IAS_DFT_FACTORY<IAS::Net::SSL::BlockIO>::PtrHolder            ptrBIO;
	IAS_DFT_FACTORY<IAS::Net::SSL::SecureLayerClient>::PtrHolder  ptrSecureLayer;
	IAS::Net::FileHandle* pFileHandle;
};
/*************************************************************************/
Sync::BlockIOWrapper* BlockIOWrapperFactory::createBlockIOWrapper()const{
	IAS_TRACER;

	IAS_DFT_FACTORY<BlockIOWrapper>::PtrHolder ptrWrapper(
			IAS_DFT_FACTORY<BlockIOWrapper>::Create(ptrContext.getPointer(),connect()));

	bool bVerifyPeer = dmConnection->getSsl()->isSetVerifyPeerCert() && dmConnection->getSsl()->getVerifyPeerCert();


	IAS::Net::IBlockIO* pBlockIO = ptrWrapper->getFileHandle();

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Using Proxy: "<<dmConnection->isSetProxy());

	if(dmConnection->isSetProxy()) {
		IAS_DFT_FACTORY<IAS::Net::HTTP::Request>::PtrHolder ptrRequest(IAS_DFT_FACTORY<IAS::Net::HTTP::Request>::Create());

		ptrRequest->setMethod(IAS::Net::HTTP::Request::HM_CONNECT);
		ptrRequest->setResource(dmConnection->getHost()+":443");
		ptrRequest->setHost(dmConnection->getHost());

		IAS_DFT_FACTORY<IAS::Net::HTTP::HeaderOutputPump>::PtrHolder ptrPumpOut(
				IAS_DFT_FACTORY<IAS::Net::HTTP::HeaderOutputPump>::Create(ptrRequest, pBlockIO));

		while(ptrPumpOut->pump() != IAS::Net::IBlockIO::RC_OK)
		/* repeat */;

		IAS_DFT_FACTORY<IAS::Net::HTTP::Response>::PtrHolder ptrResponse(IAS_DFT_FACTORY<IAS::Net::HTTP::Response>::Create());

		IAS_DFT_FACTORY<IAS::Net::HTTP::HeaderInputPump>::PtrHolder ptrPumpIn(
				IAS_DFT_FACTORY<IAS::Net::HTTP::HeaderInputPump>::Create(ptrResponse, pBlockIO));

		while(ptrPumpIn->pump() != IAS::Net::IBlockIO::RC_OK)
		/* repeat */;

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Proxy Status: "<<ptrResponse->getStatus());

		if(ptrResponse->getStatus() != IAS::Net::HTTP::Response::HS_OK)
			IAS_THROW(BadUsageException("Proxy returned non-200 status!"));
	}

	ptrWrapper->getSecureLayer()->connect();

	String strPeerCN(ptrWrapper->getSecureLayer()->getPeerCertifcate()->getSubjectCN());

	if(dmConnection->getSsl()->isSetVerifyPeerIP() && dmConnection->getSsl()->getVerifyPeerIP()){
		String strPeerCN(ptrWrapper->getSecureLayer()->getPeerCertifcate()->getSubjectCN());
		IAS_LOG(LogLevel::INSTANCE.isData(),strPeerCN<<" ? "<<getRemote());

		if(strPeerCN.compare(getRemote().getAddress()) != 0)
			IAS_THROW(BadUsageException("Certificate does not match the remote hostname, CN=")<<strPeerCN<<", connection: "<<getRemote())
	}



	return ptrWrapper.pass();
}
/*************************************************************************/
}
}
}
}
}
}
