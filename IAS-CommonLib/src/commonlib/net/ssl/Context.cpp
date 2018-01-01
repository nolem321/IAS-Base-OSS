/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/Context.cpp
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
#include "Context.h"
#include "SSLException.h"
#include <commonlib/tools/EnvTools.h>
#include <commonlib/exception/BadUsageException.h>
#include <string.h>

namespace IAS {
namespace Net {
namespace SSL {

const String Context::CTrustedLocationsEnv("IAS_SSL_TRUSTED");
const String Context::CCertPathEnv("IAS_SSL_CERT_PATH");

/*************************************************************************/
Context::Context(const String& strFile, const String& strPassword):
		ctx(0),
		strFile(strFile),
		strPassword(strPassword){

	IAS_TRACER;

	//TODO old ssl versions
	const SSL_METHOD *meth;

	/* Create our context*/
	meth = SSLv23_method();
	ctx = SSL_CTX_new(meth);

	if(!ctx){
		IAS_THROW(SSLException("SSL_CTX_new failed, giving up !, Did you call 'Net::SSL::Environment::GetInstance();'"));
	}

	/* Load our keys and certificates - BOOK has different method */

	if(!strFile.empty()){
	if (!(SSL_CTX_use_certificate_chain_file(ctx, strFile.c_str())))
		IAS_THROW(SSLException("Can't read certificate file"));

	SSL_CTX_set_default_passwd_cb(ctx, PasswordCallback);

	if (!(SSL_CTX_use_PrivateKey_file(ctx, strFile.c_str(), SSL_FILETYPE_PEM)))
		IAS_THROW(SSLException("Can't read key file"));

	/* Load the CAs we trust*/
	//TODO (L) Tokenize ?
	if (!(SSL_CTX_load_verify_locations(ctx, EnvTools::GetEnv(CTrustedLocationsEnv).c_str(), 0)))
		IAS_THROW(SSLException("Can't read CA list"));
	}
#if (OPENSSL_VERSION_NUMBER < 0x00905100L)
	SSL_CTX_set_verify_depth(ctx,1);
#endif

}
/*************************************************************************/
Context::~Context() throw(){
	IAS_TRACER;
	SSL_CTX_free(ctx);
}
/*************************************************************************/
void Context::setCipherList(const StringList& lstCiphers){
	IAS_TRACER;

	String strCiphers;

	for(StringList::const_iterator it=lstCiphers.begin(); it != lstCiphers.end(); it++){
		if(it != lstCiphers.begin())
			strCiphers+=',';
		strCiphers+=*it;
	}

	setCipher(strCiphers);
}
/*************************************************************************/
void Context::setCipher(const String& strCiphers){
	IAS_TRACER;

	if(SSL_CTX_set_cipher_list(ctx,strCiphers.c_str())==0)
		IAS_THROW(BadUsageException()<<"Cipher list:"<<strCiphers);

}
/*************************************************************************/
int Context::PasswordCallback(char *buf, int num, int rwflag, void *userdata) {

	Context* pContext=static_cast<Context*>(userdata);
	strncpy(buf, pContext->strPassword.c_str(), pContext->strPassword.length()+1);

	return(strlen(buf));
}
/*************************************************************************/


}
}
}
