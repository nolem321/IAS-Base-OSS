/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ReadCertificate.cpp
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
#include "ReadCertificate.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/Tools.h>
#include <commonlib/net/ssl/CertificateX509.h>
#include <commonlib/net/ssl/Environment.h>

#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
ReadCertificate::ReadCertificate(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;

	Net::SSL::Environment::GetInstance();

}
/*************************************************************************/
ReadCertificate::~ReadCertificate() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ReadCertificate::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;
	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	String strFileName = pParameters->getString("strFileName");

	IAS_DFT_FACTORY<Net::SSL::CertificateX509>::PtrHolder ptrCertificate(
			IAS_DFT_FACTORY<Net::SSL::CertificateX509>::Create(strFileName));

	pParameters->setString(String(Model::Dec::ResultDeclarationNode::CStrResultVariable),
						   ptrCertificate->getBase64EncodedContent());
}
/*************************************************************************/
Statement* ReadCertificate::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ReadCertificate>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
