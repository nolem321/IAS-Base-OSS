/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/Context.h
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
#ifndef _IAS_Net_SSL_Context_H_
#define _IAS_Net_SSL_Context_H_

#include <commonlib/misc/InstanceFeature.h>
#include <openssl/ssl.h>
#include "BlockIO.h"

namespace IAS {
namespace Net {
namespace SSL {

/*************************************************************************/
/** The Context class.
 *
 */
class Context {
public:

	virtual ~Context() throw();

	SSL_CTX *getContext()const{
		return ctx;
	}


	void setCipherList(const StringList& lstCiphers);
	void setCipher(const String& strCiphers);

protected:

	Context(const String& strFile, const String& strPassword);

	SSL_CTX *ctx;

	String strFile;
	String strPassword;

	static int PasswordCallback(char *buf, int num, int rwflag, void *userdata);

	static const String CTrustedLocationsEnv;
	static const String CCertPathEnv;

	void loadCertFile();

	friend class Factory<Context>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_SSL_Context_H_ */
