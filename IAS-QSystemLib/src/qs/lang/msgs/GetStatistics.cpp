/*
 * File: IAS-QSystemLib/src/qs/lang/msgs/GetStatistics.cpp
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
#include "GetStatistics.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <lang/model/dec/ResultDeclarationNode.h>
#include <qs/workers/proc/exception/RollbackMeException.h>


using namespace ::IAS::Lang::Interpreter;
using namespace ::IAS::QS::Workers::Proc;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Msgs {

/*************************************************************************/
GetStatistics::GetStatistics(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

  if(lstParamaters.size() != 1)
		IAS_THROW(BadUsageException("TODO exception, wrong parameters in GetStatistics Statement."));

	StringList::const_iterator it=lstParamaters.begin();
	strConnectionAlias=*it++;

}
/*************************************************************************/
GetStatistics::~GetStatistics() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void GetStatistics::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	try{

   workers::Ext::ConnectionPtr ptrConnection(workers::DataFactory::GetInstance()->createConnection());
   ptrConnection->setAlias(strConnectionAlias);

	 URI uri;
	 API::Administrator *pAdministrator=pWorkContext->qs.lookupAdministrator(uri, ptrConnection);

	stats::Ext::SystemStatsPtr dmStats(pAdministrator->getStats(true));

	pParameters->setDataObject(String(::IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
			dmStats);

	}catch(Exception& e){

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}


}
/*************************************************************************/
Extern::Statement* GetStatistics::Create(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetStatistics>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

