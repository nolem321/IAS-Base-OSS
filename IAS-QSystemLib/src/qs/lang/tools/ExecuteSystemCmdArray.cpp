/*
 * File: IAS-QSystemLib/src/qs/lang/tools/ExecuteSystemCmdArray.cpp
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
#include "ExecuteSystemCmdArray.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <lang/model/dec/ResultDeclarationNode.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {

/*************************************************************************/
ExecuteSystemCmdArray::ExecuteSystemCmdArray(const StringList& lstParamaters):
	ExecuteSystemCmd(lstParamaters){
	IAS_TRACER;

}
/*************************************************************************/
ExecuteSystemCmdArray::~ExecuteSystemCmdArray() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void ExecuteSystemCmdArray::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* dmParameters = pCtx->getBlockVariables(0);

	String strCommand(dmParameters->getString("command"));
	const DM::DataObjectList& dmArgs(dmParameters->getList("arguments"));

	StringList lstArgs;

	try{

		for(int iIdx = 0; iIdx < dmArgs.size(); iIdx++){
			lstArgs.push_back(dmArgs.at(iIdx)->toString());
		}

		dmParameters->setInteger(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
									execute(strCommand,lstArgs));

	}catch(Exception& e){

		//TODO (H) use exceptions from the tools namespace.

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}


}
/*************************************************************************/
Extern::Statement* ExecuteSystemCmdArray::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ExecuteSystemCmdArray>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}

