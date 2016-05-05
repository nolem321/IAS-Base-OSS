/*
 * File: IAS-QSystemLib/src/qs/lang/msgs/Receive.cpp
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
#include "Receive.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>

#include <qs/workers/proc/io/IOManager.h>
#include <qs/workers/proc/io/Input.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <lang/model/dec/ResultDeclarationNode.h>

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Msgs {

/*************************************************************************/
Receive::Receive(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
Receive::~Receive() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Receive::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strInputName = pParameters->getString("name");
	workers::Ext::ContextPtr  dmCtx  = workers::DataFactory::GetInstance()->getContextType()->cast(pParameters->getDataObject("ctx"));

	DM::DataObjectPtr dmResult;

	try{

		pWorkContext->getIOManager()->getInput(strInputName)->receive(dmCtx,dmResult);

		pParameters->setDataObject(String(::IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
									 	 dmResult);

	}catch(Exception& e){

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}


}
/*************************************************************************/
Extern::Statement* Receive::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Receive>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}

