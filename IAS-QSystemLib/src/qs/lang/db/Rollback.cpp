/*
 * File: IAS-QSystemLib/src/qs/lang/db/Rollback.cpp
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
#include "Rollback.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <dm/datamodel.h>
#include <ds/api.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/ds/DSManager.h>
#include <qs/workers/proc/ds/DSDriver.h>
#include <qs/workers/proc/ds/wrapper/Insert.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <org/invenireaude/qsystem/workers/ds/Exception.h>
#include <org/invenireaude/qsystem/workers/ds/ConstraintViolationException.h>
#include <org/invenireaude/qsystem/workers/ds/DataFactory.h>

#include <lang/model/dec/ResultDeclarationNode.h>

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem::workers;
using namespace ::IAS::QS::Workers::Proc::DS;

namespace IAS {
namespace QS {
namespace Lang {
namespace DB {

/*************************************************************************/
Rollback::Rollback(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

	if(lstParamaters.size() != 1)
		IAS_THROW(BadUsageException("TODO exception, wrong parameters in DataSource Rollback Statement."));

	StringList::const_iterator it=lstParamaters.begin();
	strDataSource=*it++;
}
/*************************************************************************/
Rollback::~Rollback() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Rollback::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dmInput(pCtx->getBlockVariables(0));
	DM::DataObjectPtr dmResult;

	try{

		DSDriver *pDriver     = pWorkContext->getDSManager()->getDSDriver(strDataSource);

		pDriver->getSession()->rollback();

	}catch(Exception& e){

		org::invenireaude::qsystem::workers::ds::Ext::ExceptionPtr dmException(
				org::invenireaude::qsystem::workers::ds::DataFactory::GetInstance()->createException());

		dmException->setName("DatabaseException");
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));
	}

}
/*************************************************************************/
Extern::Statement* Rollback::Create(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Rollback>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

