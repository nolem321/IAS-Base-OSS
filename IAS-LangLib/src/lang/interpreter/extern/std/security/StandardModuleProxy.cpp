/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/StandardModuleProxy.cpp
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
#include "StandardModuleProxy.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "GetHash.h"
#include "BinaryToSHA1.h"
#include "BinaryToSHA256.h"
#include "BinaryToMD5.h"
#include "BinaryToHMAC256.h"
#include "ReadCertificate.h"
#include "Sign.h"
#include "Base64ToBinary.h"
#include "BinaryToBase64.h"
#include "HexToBinary.h"
#include "BinaryToHex.h"
#include "StrToSHA1.h"
#include "StrToSHA256.h"
#include "StrToMD5.h"
#include "StrToHMAC256.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace Security {

/*************************************************************************/
StandardModuleProxy::StandardModuleProxy(){
	IAS_TRACER;
}
/*************************************************************************/
StandardModuleProxy::~StandardModuleProxy() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StandardModuleProxy::setupImpl(){

	IAS_TRACER;

	registerSymbol("GetHash",&(GetHash::Create));
	registerSymbol("BinaryToSHA1",&(BinaryToSHA1::Create));
	registerSymbol("BinaryToSHA256",&(BinaryToSHA256::Create));
	registerSymbol("BinaryToMD5",&(BinaryToMD5::Create));
	registerSymbol("ReadCertificate",&(ReadCertificate::Create));
	registerSymbol("BinaryToHMAC256",&(BinaryToHMAC256::Create));
	registerSymbol("Sign",&(Sign::Create));
	registerSymbol("BinaryToHex",&(BinaryToHex::Create));
	registerSymbol("HexToBinary",&(HexToBinary::Create));
	registerSymbol("BinaryToBase64",&(BinaryToBase64::Create));
	registerSymbol("Base64ToBinary",&(Base64ToBinary::Create));

  registerSymbol("StrToSHA1",&(StrToSHA1::Create));
  registerSymbol("StrToSHA256",&(StrToSHA256::Create));
  registerSymbol("StrToMD5",&(StrToMD5::Create));
  registerSymbol("StrToHMAC256",&(StrToHMAC256::Create));

}
/*************************************************************************/
void StandardModuleProxy::cleanUpImpl(){
	IAS_TRACER;
}
/*************************************************************************/
StandardModuleProxy* StandardModuleProxy::Create(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<StandardModuleProxy>::Create();
}
/*************************************************************************/
}
}
}
}
}
}
/*************************************************************************/
void* ias_lang_std_security_proxy(){
	IAS_TRACER;
	return ::IAS::Lang::Interpreter::Extern::Std::Security::StandardModuleProxy::Create();
}
/*************************************************************************/

