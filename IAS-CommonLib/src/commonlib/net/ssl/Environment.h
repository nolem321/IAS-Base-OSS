/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/Environment.h
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
#ifndef _IAS_Net_SSL_Environment_H_
#define _IAS_Net_SSL_Environment_H_

#include <commonlib/misc/InstanceFeature.h>
#include <openssl/ssl.h>
#include "BlockIO.h"

namespace IAS {
namespace Net {
namespace SSL {

/*************************************************************************/
/** The Environment class.
 *
 */
class Environment : public ::IAS::InstanceFeature<Environment>{
public:

	virtual ~Environment() throw();

	void printErrors();

protected:
	Environment();

	BIO *bio_err;
	char *ciphers; //TODO release ?

	void initialize();

	friend class Factory<Environment>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_SSL_Environment_H_ */
