/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/Tools.h
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
#ifndef _IAS_Net_SSL_Tools_H_
#define _IAS_Net_SSL_Tools_H_

#include <commonlib/misc/InstanceFeature.h>

#include <openssl/ssl.h>
#include <commonlib/tools/Buffer.h>

#include "PrivateKey.h"

namespace IAS {
namespace Net {
namespace SSL {

/*************************************************************************/
/** The Tools class.
 *
 */
class Tools {
public:

	static String ComputeSHA256(const String& strValue);
	static String ComputeSHA256(const void *pData, size_t iDataLen);

	static String ComputeSHA1(const String& strValue);
	static String ComputeSHA1(const void *pData, size_t iDataLen);

	static String ComputeHmacSHA256(const String& strKey, const String& strValue);
	static String ComputeHmacSHA256(const String& strKey, const void *pData, size_t iDataLen);

	static String ComputeMD5(const String& strValue);
	static String ComputeMD5(const void *pData, size_t iDataLen);

	static Buffer* ComputeSignature(const PrivateKey* pKey, const String& strValue);
	static Buffer* ComputeSignature(const PrivateKey* pKey, const void *pData, size_t iDataLen);
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_SSL_Tools_H_ */
