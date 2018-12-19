/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/Load.cpp
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
#include "Load.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>
#include <lang/interpreter/exe/exception/InterpreterException.h>

#include <org/invenireaude/lang/builtin/Exception.h>
#include <org/invenireaude/lang/builtin/DataFactory.h>

#include <dm/datamodel.h>

using namespace org::invenireaude::lang;

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace System {

/*************************************************************************/
Load::Load(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
Load::~Load() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Load::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;
	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strFileName = pParameters->getString("file");

	try{

		IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrXMLHelper(
					IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pCtx->getDataFactory()));

		IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readFile(strFileName));
		DM::DataObjectPtr dm = ptrDoc->getRootObject();

		pParameters->setDataObject(Model::Dec::ResultDeclarationNode::CStrResultVariable,dm);

	}catch(ItemNotFoundException& e){

		builtin::Ext::ExceptionPtr dmException=builtin::DataFactory::GetInstance()->createException();

		dmException->setName("ItemNotFoundException");
		dmException->setInfo(strFileName);

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));
	}


}
/*************************************************************************/
Statement* Load::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Load>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
