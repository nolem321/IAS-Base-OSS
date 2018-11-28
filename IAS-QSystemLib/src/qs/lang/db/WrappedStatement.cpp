/*
 * File: IAS-QSystemLib/src/qs/lang/db/WrappedStatement.cpp
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
#include "WrappedStatement.h"
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

const String WrappedStatement::C_ENV_VERIFY_SQL("IAS_DS_VERIFY_SQL");

/*************************************************************************/
WrappedStatement::WrappedStatement(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

	if(lstParamaters.size() < 2)
		IAS_THROW(BadUsageException("TODO exception, wrong parameters in DataSource Statement."));

	StringList::const_iterator it=lstParamaters.begin();
	strDataSource=*it++;
	strSpecification=*it++;
  if(it != lstParamaters.end())
    strDataSourceIdx=*it++;

  if(EnvTools::GetBooleanEnv(C_ENV_VERIFY_SQL))
    verifySQL();

}
/*************************************************************************/
WrappedStatement::~WrappedStatement() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void WrappedStatement::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dmInput(pCtx->getBlockVariables(0));
  IAS_LOG(true,"type:"<<dmInput->getType()->getFullName());

	DM::DataObjectPtr dmResult;

	try{

    String strDataSourceName(strDataSource);

    if(!strDataSourceIdx.empty())
      strDataSourceName += "." +  dmInput->getString(strDataSourceIdx);

		DSDriver *pDriver     = pWorkContext->getDSManager()->getDSDriver(strDataSourceName);

		DSDriver::WrapperHolder ptrWrapper(pDriver->getStatement(strSpecification,dmInput.getPointer()),pDriver);
		ptrWrapper->execute(dmInput);

	}catch(DS::API::ConstraintViolationException& e){

		org::invenireaude::qsystem::workers::ds::Ext::ExceptionPtr dmException(
					org::invenireaude::qsystem::workers::ds::DataFactory::GetInstance()->createConstraintViolationException());

		dmException->setName("ConstraintViolationException");
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}catch(Exception& e){

		org::invenireaude::qsystem::workers::ds::Ext::ExceptionPtr dmException(
				org::invenireaude::qsystem::workers::ds::DataFactory::GetInstance()->createException());

		dmException->setName("WrappedStatementException");
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));
	}

}
/*************************************************************************/
void WrappedStatement::verifySQL(){
    IAS_TRACER;

    return ;
    // TODO type of program signature;
    String strSQL2Verify(TypeTools::Replace(strSpecification,"?",""));
 	  // DM::DataObjectPtr dmParameters;
    // dmParameters = pModuleProxy->getDataFactory()->getType("IAS/Script/T1","RootType")->createDataObject();
  	// DSDriver *pDriver     = pWorkContext->getDSManager()->getDSDriver(strDataSource);
  	// DSDriver::WrapperHolder ptrWrapper(pDriver->getStatement(strSpecification,dmParameters.getPointer()),pDriver);
}
/*************************************************************************/
Extern::Statement* WrappedStatement::Create(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<WrappedStatement>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

