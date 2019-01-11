/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/Sign.cpp
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
#include "Sign.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/Tools.h>
#include <commonlib/net/ssl/PrivateKey.h>
#include <commonlib/net/ssl/Environment.h>

#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace Security {

/*************************************************************************/
Sign::Sign(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;

	Net::SSL::Environment::GetInstance();

	if(lstParamaters.size() != 2)
		IAS_THROW(BadUsageException("TODO exception, wrong parameters in Sign() Statement."));

	StringList::const_iterator it=lstParamaters.begin();
	String strFileName = *it++;
	String strPassword = *it++;

	ptrPrivateKey = IAS_DFT_FACTORY<Net::SSL::PrivateKey>::Create(strFileName, strPassword);

}
/*************************************************************************/
Sign::~Sign() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Sign::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;
	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	String strContent = pParameters->getString("strContent");


	IAS_DFT_FACTORY<Buffer>::PtrHolder ptrBuffer(
				Net::SSL::Tools::ComputeSignature(ptrPrivateKey,strContent));

	String strOutput;

	MiscTools::BinaryToBase64(ptrBuffer->getBuffer<unsigned char>(),
			ptrBuffer->getSize(), strOutput);

	pParameters->setString(Model::Dec::ResultDeclarationNode::CStrResultVariable, strOutput);
}
/*************************************************************************/
Statement* Sign::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Sign>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
