/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/SecureLayer.h
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
#ifndef _IAS_Net_SSL_SecureLayer_H_
#define _IAS_Net_SSL_SecureLayer_H_

#include <commonlib/memory/ma/Factory.h>
#include <openssl/ssl.h>

#include "../BlockIOUndo.h"
#include "BlockIO.h"

namespace IAS {
namespace Net {
namespace SSL {


/*************************************************************************/
/** The SecureLayer class.
 *
 */
class Context;
class CertificateX509;

class SecureLayer : public Net::BlockIOUndo {
public:

	virtual ~SecureLayer() throw();

	virtual Result  read(void *pData, size_t iBufferLen, size_t& iDataSize);
	virtual Result  write(const void *pData, size_t iDataSize, size_t& iWritten);


	CertificateX509 *getPeerCertifcate()const;
	bool getVerificationResult()const;

	String getCurrentCipher()const;

protected:
	SecureLayer(Context* pContext,BlockIO* pBlockIO);

	::SSL *ssl;

	IBlockIO::Result decodeError(int iRes,size_t* pDataSize=NULL);

	void setVerify(int iMode);

	friend class SSLException;

};
/*************************************************************************/
class SecureLayerServer : public SecureLayer {
	public:

	void setVerification(bool bVerifyPeer, bool bFailIfNoPeerCert=false, bool bVerifyClientOnce=false);

	bool accept();

	protected:
	SecureLayerServer(Context* pContext,BlockIO* pBlockIO);

	friend class Factory<SecureLayerServer>;
};
/*************************************************************************/
class SecureLayerServerSocket :
		public IAS::Net::FileHandle,
		public IAS::Net::SSL::BlockIO,
		public IAS::Net::SSL::SecureLayerServer{

	public:
		virtual ~SecureLayerServerSocket()throw();

	protected:
		SecureLayerServerSocket(int fd, Context* pContext, bool bVerifyPeer = false);

		friend class Factory<SecureLayerServerSocket>;
};
/*************************************************************************/
class SecureLayerClient : public SecureLayer {
	public:

	void setVerification(bool bVerifyPeer);

	void connect();
	void shutdown();

	protected:
	SecureLayerClient(Context* pContext,BlockIO* pBlockIO);

	friend class Factory<SecureLayerClient>;
};
/*************************************************************************/
class SecureLayerClientSocket :
		public IAS::Net::FileHandle,
		public IAS::Net::SSL::BlockIO,
		public IAS::Net::SSL::SecureLayerClient{

	public:
		virtual ~SecureLayerClientSocket()throw();

	protected:
		SecureLayerClientSocket(int fd, Context* pContext);

		friend class Factory<SecureLayerClientSocket>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_Net_SSL_SecureLayer_H_ */
