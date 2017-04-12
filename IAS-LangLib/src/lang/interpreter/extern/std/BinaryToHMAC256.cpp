/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/BinaryToHMAC256.cpp
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
#include "BinaryToHMAC256.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/Tools.h>

#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
BinaryToHMAC256::BinaryToHMAC256(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
BinaryToHMAC256::~BinaryToHMAC256() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void BinaryToHMAC256::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;
	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	IAS_DFT_FACTORY<DM::RawContent>::PtrHolder ptrDataBuffer(
				IAS_DFT_FACTORY<DM::RawContent>::Create(1024));

	const String strKey      = pParameters->getString("strKey");

	pParameters->getRaw("bData", ptrDataBuffer);


	pParameters->setString(Model::Dec::ResultDeclarationNode::CStrResultVariable,
				Net::SSL::Tools::ComputeHmacSHA256(strKey, ptrDataBuffer->getBuffer<unsigned char>(), ptrDataBuffer->getSize())
	);
}
/*************************************************************************/
Statement* BinaryToHMAC256::Create(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<BinaryToHMAC256>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
