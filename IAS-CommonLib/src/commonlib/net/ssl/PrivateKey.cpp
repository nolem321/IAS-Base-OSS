/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/PrivateKey.cpp
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
#include "PrivateKey.h"
#include "SSLException.h"
#include <commonlib/exception/ItemNotFoundException.h>
#include <commonlib/exception/BadUsageException.h>
#include <string.h>

namespace IAS {
namespace Net {
namespace SSL {

/***********************************************************************/
PrivateKey::PrivateKey(const String& strFileName, const String& strPassword):
		strPassword(strPassword),
		privkey(0){
	IAS_TRACER;

   FILE *fp = fopen (strFileName.c_str(), "r");

   if(fp == NULL)
		IAS_THROW(BadUsageException("Cannot find a private key file: "+strFileName));

   privkey = EVP_PKEY_new();

   privkey = PEM_read_PrivateKey( fp, &privkey, &PasswordCallback, this);

   fclose(fp);

   if(privkey == NULL)
	   IAS_THROW(BadUsageException("Cannot read a private key from a file: "+strFileName));
}
/*************************************************************************/
PrivateKey::~PrivateKey() throw(){
	IAS_TRACER;

	if(privkey)
		EVP_PKEY_free(privkey);
}
/*************************************************************************/
int PrivateKey::PasswordCallback(char *buf, int num, int rwflag, void *userdata) {

	PrivateKey* pPrivateKey=static_cast<PrivateKey*>(userdata);
	strncpy(buf, pPrivateKey->strPassword.c_str(), pPrivateKey->strPassword.length()+1);

	return(strlen(buf));
}
/*************************************************************************/


}
}
}
