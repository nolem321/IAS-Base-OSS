/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/SecureLayer.cpp
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
#include "SecureLayer.h"
#include <commonlib/commonlib.h>

#include "CertificateX509.h"

#include "Environment.h"
#include "SSLException.h"
#include "Context.h"

namespace IAS {
namespace Net {
namespace SSL {

/*************************************************************************/
SecureLayer::SecureLayer(Context* pContext,BlockIO* pBlockIO){
	IAS_TRACER;

	ssl = SSL_new(pContext->getContext());

	if(!ssl)
		IAS_THROW(SSLException("SSL_new"));

	SSL_set_bio(ssl,pBlockIO->getBIO(),pBlockIO->getBIO());
}
/*************************************************************************/
SecureLayer::~SecureLayer() throw(){
	IAS_TRACER;
	if(ssl)
		SSL_free(ssl);
}
/*************************************************************************/
IBlockIO::Result SecureLayer::write(const void *pData, size_t iDataSize, size_t& iWritten){
	IAS_TRACER;


	if(LogLevel::INSTANCE.isData()){
		String strData;
		for(int i=0;i<iDataSize;i++)
			strData += String("") + (*(((char*)pData)+i) >= ' ' ? *(((char*)pData)+i) : '.');
		IAS_LOG(LogLevel::INSTANCE.isData(),"WRITE:"<<iDataSize<<" ["<<strData<<"]");
	}

	return decodeError(SSL_write(ssl,pData,iDataSize),&iWritten);
}
/*************************************************************************/
IBlockIO::Result SecureLayer::read(void *pData, size_t iBufferLen, size_t& iDataSize){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"D:"<<pData);

	if(readUndone(pData,iBufferLen,iDataSize))
		return RC_OK;

	int iResult = SSL_read(ssl,pData,iBufferLen);

	if(LogLevel::INSTANCE.isData()){
		String strData;
		for(int i=0;i<iResult;i++)
			strData += String("") + (*(((char*)pData)+i) >= ' ' ? *(((char*)pData)+i) : '.');
		IAS_LOG(LogLevel::INSTANCE.isData(),"READ:"<<iResult<<" ["<<strData<<"]");
	}

	return decodeError(iResult,&iDataSize);
}
/*************************************************************************/
CertificateX509* SecureLayer::getPeerCertifcate()const{
	IAS_TRACER;

	X509* x509 = SSL_get_peer_certificate(ssl);

	if(!x509)
		IAS_THROW(ItemNotFoundException("CertificateX509"));

	return IAS_DFT_FACTORY<CertificateX509>::Create(x509);
}
/*************************************************************************/
bool SecureLayer::getVerificationResult()const{
	IAS_TRACER;

	long iResult = SSL_get_verify_result(ssl);

	if(iResult == X509_V_OK)
		return true;

	IAS_LOG(LogLevel::INSTANCE.isError(),"SSL Verification failed with code: "<<iResult<<".")

	return false;
}
/*************************************************************************/
String SecureLayer::getCurrentCipher()const{
	IAS_TRACER;

	char sBuffer[128];

	const SSL_CIPHER* c=SSL_get_current_cipher(ssl);
	if(!c)
		IAS_THROW(ItemNotFoundException("SSL_get_current_cipher"));

	SSL_CIPHER_description(c,sBuffer,128);
	sBuffer[127]=0;
	return String(sBuffer);
}
/*************************************************************************/
IBlockIO::Result SecureLayer::decodeError(int iRes,size_t* pDataSize){

	IAS_TRACER;

	switch(SSL_get_error(ssl,iRes)){

			case SSL_ERROR_NONE:
				if(pDataSize)
					*pDataSize=iRes;
				return RC_OK;
				break;

			case SSL_ERROR_WANT_READ:
				return RC_WantRead;
			case SSL_ERROR_WANT_WRITE:
				return RC_WantWrite;
			case SSL_ERROR_WANT_CONNECT:
			case SSL_ERROR_WANT_ACCEPT:
				return RC_WantAny;
				break;

			case SSL_ERROR_ZERO_RETURN:
				if(pDataSize)
					*pDataSize=iRes;
				return RC_OK;
				break;

			case SSL_ERROR_WANT_X509_LOOKUP:
				IAS_THROW(SystemException("SSL SSL_ERROR_WANT_X509_LOOKUP "));
			break;

			case SSL_ERROR_SSL:
				IAS_THROW(SystemException("SSL SSL_ERROR_SSL "));
			break;

			case SSL_ERROR_SYSCALL:

				if(pDataSize)
					*pDataSize=0;

				if(errno==0)
					return RC_OK;
				IAS_THROW(SystemException("SSL Read ")<<strerror(errno));
				break;

			default:
				IAS_THROW(InternalException("SSL Read: unknown case"));
		}
}
/*************************************************************************/
void SecureLayer::setVerify(int iMode){
	IAS_TRACER;
	SSL_set_verify(ssl,iMode,NULL);
}
/*************************************************************************/
SecureLayerServer::SecureLayerServer(Context* pContext,BlockIO* pBlockIO):
		SecureLayer(pContext,pBlockIO){};
/*************************************************************************/
bool SecureLayerServer::accept(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Accepting");
	int iRes = SSL_accept(ssl);

	if(!decodeError(iRes)){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Accept completed.");
		//TODO check certs
		return false;
	}else
		return true;

}
/*************************************************************************/
void SecureLayerServer::setVerification(bool bVerifyPeer, bool bFailIfNoPeerCert, bool bVerifyClientOnce){
	IAS_TRACER;

	int iMode = bVerifyPeer ?  SSL_VERIFY_PEER : SSL_VERIFY_NONE;

	if(bFailIfNoPeerCert)
		iMode |= SSL_VERIFY_FAIL_IF_NO_PEER_CERT;

	if(bVerifyClientOnce)
			iMode |= SSL_VERIFY_CLIENT_ONCE;

	setVerify(iMode);

}
/*************************************************************************/
SecureLayerClient::SecureLayerClient(Context* pContext,BlockIO* pBlockIO):
		SecureLayer(pContext,pBlockIO){};
/*************************************************************************/
void SecureLayerClient::connect(){
	IAS_TRACER;

	int iRes = SSL_connect(ssl);

	if(iRes<=0)
		IAS_THROW(SSLException("SSL_connect")<<"Code:"<<SSL_get_error(ssl,iRes)<<strerror(errno));

	//TODO check cert.
}
/*************************************************************************/
void SecureLayerClient::shutdown(){
	IAS_TRACER;

	int iRes = SSL_shutdown(ssl);

	if(iRes < 0)
		IAS_THROW(SSLException("SSL_shutdown")<<"Code: "<<iRes<<" "<<SSL_get_error(ssl,iRes)<<strerror(errno));

	//TODO check cert.
}
/*************************************************************************/
void SecureLayerClient::setVerification(bool bVerifyPeer){
	IAS_TRACER;

	int iMode = bVerifyPeer ?  SSL_VERIFY_PEER : SSL_VERIFY_NONE;

	setVerify(iMode);
}
/*************************************************************************/
SecureLayerServerSocket::SecureLayerServerSocket(int fd, Context* pContext, bool bVerifyPeer):
	FileHandle(fd),
	BlockIO(static_cast<FileHandle*>(this)),
	SecureLayerServer(pContext,static_cast<BlockIO*>(this)){}
/*************************************************************************/
SecureLayerServerSocket::~SecureLayerServerSocket()throw(){}
/*************************************************************************/
SecureLayerClientSocket::SecureLayerClientSocket(int fd, Context* pContext):
	FileHandle(fd),
	BlockIO(static_cast<FileHandle*>(this)),
	SecureLayerClient(pContext,static_cast<BlockIO*>(this)){}
/*************************************************************************/
SecureLayerClientSocket::~SecureLayerClientSocket()throw(){}
/*************************************************************************/

}
}
}

