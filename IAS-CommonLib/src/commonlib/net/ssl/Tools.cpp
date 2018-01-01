/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/Tools.cpp
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
#include <commonlib/logger/logger.h>
#include <commonlib/memory/memory.h>
#include "Tools.h"
#include "SSLException.h"

#include <commonlib/exception/ItemNotFoundException.h>
#include <commonlib/exception/BadUsageException.h>

#include <commonlib/tools/MiscTools.h>

#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>

namespace IAS {
namespace Net {
namespace SSL {

/***********************************************************************/
String Tools::ComputeSHA256(const String& strValue){

	 IAS_TRACER;
	 unsigned char hash[SHA256_DIGEST_LENGTH];

	 SHA256_CTX sha256;

	 SHA256_Init(&sha256);
	 SHA256_Update(&sha256, strValue.c_str(), strValue.length());
	 SHA256_Final(hash, &sha256);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA256_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeSHA256(const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[SHA256_DIGEST_LENGTH];

	 SHA256_CTX sha256;

	 SHA256_Init(&sha256);
	 SHA256_Update(&sha256, pData, iDataLen);
	 SHA256_Final(hash, &sha256);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA256_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeMD5(const String& strValue){
	 IAS_TRACER;

	 return ComputeMD5(strValue.c_str(), strValue.length());
}
/***********************************************************************/
String Tools::ComputeMD5(const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[MD5_DIGEST_LENGTH];

	 MD5_CTX md5;

	 MD5_Init(&md5);
	 MD5_Update(&md5, pData, iDataLen);
	 MD5_Final(hash, &md5);

	 String strResult;
	 MiscTools::BinarytoHex(hash,MD5_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeSHA1(const String& strValue){

	 IAS_TRACER;
	 unsigned char hash[SHA_DIGEST_LENGTH];

	 SHA_CTX sha;

	 SHA1_Init(&sha);
	 SHA1_Update(&sha, strValue.c_str(), strValue.length());
	 SHA1_Final(hash, &sha);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeSHA1(const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[SHA_DIGEST_LENGTH];

	 SHA_CTX sha;

	 SHA1_Init(&sha);
	 SHA1_Update(&sha, pData, iDataLen);
	 SHA1_Final(hash, &sha);

	 String strResult;
	 MiscTools::BinarytoHex(hash,SHA_DIGEST_LENGTH,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeHmacSHA256(const String& strKey, const void *pData, size_t iDataLen){

	 IAS_TRACER;
	 unsigned char hash[EVP_MAX_MD_SIZE];
	 unsigned int  iOutputLen;

	 if(HMAC(EVP_sha256(), strKey.c_str(), strKey.length(), (const unsigned char*)pData, iDataLen, hash, &iOutputLen) == NULL)
		 IAS_THROW(BadUsageException("ComputeHmacSHA256 has failed."));

	 String strResult;
	 MiscTools::BinarytoHex(hash,iOutputLen,strResult);
	 return strResult;
}
/***********************************************************************/
String Tools::ComputeHmacSHA256(const String& strKey, const String& strValue){

	 IAS_TRACER;
	 unsigned char hash[EVP_MAX_MD_SIZE];
	 unsigned int  iOutputLen;

	 if(HMAC(EVP_sha256(), strKey.c_str(), strKey.length(), (const unsigned char*)strValue.c_str(), strValue.length(), hash, &iOutputLen) == NULL)
		 IAS_THROW(BadUsageException("ComputeHmacSHA256 has failed."));

	 String strResult;
	 MiscTools::BinarytoHex(hash,iOutputLen,strResult);
	 return strResult;
}
/*************************************************************************/

/***********************************************************************/
Buffer* Tools::ComputeSignature(const PrivateKey* pKey, const String& strValue){

	 IAS_TRACER;

	 return ComputeSignature(pKey, strValue.c_str(), strValue.length());
}
/***********************************************************************/
Buffer* Tools::ComputeSignature(const PrivateKey* pKey, const void *pData, size_t iDataLen){


	size_t iSignatureLen = 0;


	EVP_MD_CTX md_ctx;
	EVP_MD_CTX_init(&md_ctx);

	//SSL API revenge ...
    EVP_PKEY *pkey = const_cast<EVP_PKEY *>(pKey->getPrivateKey());

    IAS_CHECK_IF_NULL(pkey);

	if(!EVP_DigestSignInit(&md_ctx, NULL, EVP_sha1(), NULL, pkey) ||
	   !EVP_DigestSignUpdate(&md_ctx, pData, iDataLen))
		IAS_THROW(InternalException("Openssl error in EVP_DigestSignUpdate or EVP_DigestSignInit"));

	 if (!EVP_DigestSignFinal(&md_ctx, NULL, &iSignatureLen))
		 IAS_THROW(InternalException("Openssl error in EVP_DigestSignFinal"));

	 if (iSignatureLen != EVP_PKEY_size(pkey))
		 IAS_THROW(InternalException("Openssl signature length error"));

	 IAS_DFT_FACTORY<Buffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<Buffer>::Create(iSignatureLen));

	  if(!EVP_DigestSignFinal(&md_ctx, ptrBuffer->getBuffer<unsigned char>(), &iSignatureLen))
		  IAS_THROW(InternalException("Openssl error in EVP_DigestSignFinal (2)"));

	  return ptrBuffer.pass();
}
/*************************************************************************/
//String strResult;
//
//MiscTools::BinaryToBase64(ptrBuffer->getBuffer<unsigned char>(), iSignatureLen, strResult);
//
//return strResult;
}
}
}
