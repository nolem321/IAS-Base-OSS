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
#include <commonlib/tools/MiscTools.h>

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
/*************************************************************************/


}
}
}