/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/server/ssl/BlockIOWrapperFactory.cpp
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

using namespace ::org::invenireaude::qsystem::workers;
namespace IAS {
namespace QS {
namespace Net {
namespace Sync {
namespace Server {
namespace SSL {
/*************************************************************************/
BlockIOWrapperFactory::BlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection):
			Sync::Server::BlockIOWrapperFactory(dmConnection){
	IAS_TRACER;

	//TODO (M) common toolkit for this SSL::Context creation based on DM.

	const SSLCertificateFile *dmSSLCertificateFile=DataFactory::GetInstance()->getSSLCertificateFileType()->cast(dmConnection->getSsl()->getCert());

	String strFile(dmSSLCertificateFile->getFileName());
	String strPassword(dmSSLCertificateFile->getPassword());

	ptrContext=IAS_DFT_FACTORY<IAS::Net::SSL::Context>::Create(strFile,strPassword);
}
/*************************************************************************/
BlockIOWrapperFactory::~BlockIOWrapperFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
class BlockIOWrapper : public Sync::BlockIOWrapper{
public:
	BlockIOWrapper(IAS::Net::SSL::Context* pContext, IAS::Net::FileHandle* pFileHandle):
		Sync::BlockIOWrapper(pFileHandle){

		ptrBIO = IAS_DFT_FACTORY<IAS::Net::SSL::BlockIO>::Create(pFileHandle);
		ptrSecureLayer=IAS_DFT_FACTORY<IAS::Net::SSL::SecureLayerServer>::Create(pContext,ptrBIO.getPointer());

	}

	virtual IAS::Net::IBlockIO *getBlockIO()const{
		return ptrSecureLayer;
	};

	inline IAS::Net::SSL::SecureLayerServer *getSecureLayer()const{
		return ptrSecureLayer;
	};

protected:
	IAS_DFT_FACTORY<IAS::Net::SSL::BlockIO>::PtrHolder            ptrBIO;
	IAS_DFT_FACTORY<IAS::Net::SSL::SecureLayerServer>::PtrHolder  ptrSecureLayer;
};
/*************************************************************************/
Sync::BlockIOWrapper* BlockIOWrapperFactory::createBlockIOWrapper()const{
	IAS_TRACER;

	IAS_DFT_FACTORY<BlockIOWrapper>::PtrHolder ptrWrapper(
			IAS_DFT_FACTORY<BlockIOWrapper>::Create(ptrContext.getPointer(),accept()));

	bool bVerifyPeer = dmConnection->getSsl()->isSetVerifyPeerCert() && dmConnection->getSsl()->getVerifyPeerCert();

	if(bVerifyPeer)
		ptrWrapper->getSecureLayer()->setVerification(true,true);

	ptrWrapper->getSecureLayer()->accept();


	if(bVerifyPeer){
		String strPeerCN(ptrWrapper->getSecureLayer()->getPeerCertifcate()->getSubjectCN());
		IAS_LOG(LogLevel::INSTANCE.isData()||true,strPeerCN);
	}

	//TODO if(dmBlockIOWrapperFactory->getSsl()->isSetVerifyPeerIP() && dmBlockIOWrapperFactory->getSsl()->getVerifyPeerIP())

	return ptrWrapper.pass();
}
/*************************************************************************/
}
}
}
}
}
}
