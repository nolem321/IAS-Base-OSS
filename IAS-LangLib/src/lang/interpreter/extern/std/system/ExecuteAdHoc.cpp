/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ExecuteAdHoc.cpp
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
#include "ExecuteAdHoc.h"
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
ExecuteAdHoc::ExecuteAdHoc(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy):
	pAdHocPrograms(Tools::Helper::AdHocPrograms::GetInstance()){
	IAS_TRACER;
}
/*************************************************************************/
ExecuteAdHoc::~ExecuteAdHoc() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExecuteAdHoc::executeExternal(Exe::Context *pCtx) const{

	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strProgram  = pParameters->getString("program");
	const String strPattern  = pParameters->getString("source");

	DM::DataObjectPtr dmArgument = pParameters->getDataObject("argument");
	DM::DataObjectPtr dmResult;

	StringStream ssErrors;
	pAdHocPrograms->execute(strProgram, strPattern, dmArgument, dmResult, ssErrors);

	if(!ssErrors.str().empty()){

		builtin::Ext::ExceptionPtr dmException=builtin::DataFactory::GetInstance()->createException();

		dmException->setName("ExecuteAdHocException");
		dmException->setInfo(ssErrors.str());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));
	}

	pParameters->setDataObject(Model::Dec::ResultDeclarationNode::CStrResultVariable,dmResult);

}
/*************************************************************************/
Statement* ExecuteAdHoc::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ExecuteAdHoc>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
