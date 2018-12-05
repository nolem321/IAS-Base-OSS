/*
 * File: IAS-QSystemLib/src/qs/lang/li/GetHTMLSource.cpp
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
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <org/invenireaude/qsystem/typeinfo/DataFactory.h>
#include <org/invenireaude/qsystem/typeinfo/Program.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/ProgramProvider.h>
#include <dm/Impl/DataFactory.h>

#include "GetHTMLSource.h"

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace LI {

/*************************************************************************/
GetHTMLSource::GetHTMLSource(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

	ptrLocalDataFactory = IAS_DFT_FACTORY<::IAS::DM::Impl::DataFactory>::Create(pWorkContext->getGlobalContext()->getDataFactory());

	ptrProgramProvider =
			IAS_DFT_FACTORY<Workers::Proc::ProgramProvider>::Create(ptrLocalDataFactory);

}
/*************************************************************************/
GetHTMLSource::~GetHTMLSource() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetHTMLSource::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strName       = pParameters->getString("name");

	try{

		ptrProgramProvider->getSources(strName,
				pParameters->getList(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable)
			);

	}catch(Exception& e){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();
		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}
}
/*************************************************************************/
Extern::Statement* GetHTMLSource::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetHTMLSource>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

