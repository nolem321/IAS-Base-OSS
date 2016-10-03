/*
 * File: IAS-QSystemLib/src/qs/lang/ec/Update.cpp
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
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <org/invenireaude/qsystem/workers/ec/Record.h>
#include <org/invenireaude/qsystem/workers/ec/DataFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/ec/EventCounterStore.h>
#include <qs/workers/proc/GlobalContext.h>
#include "Update.h"

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;
using namespace ::IAS::QS::Workers::Proc::EC;

namespace IAS {
namespace QS {
namespace Lang {
namespace EC {

/*************************************************************************/
Update::Update(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy):
	pEventCounter(0){
	IAS_TRACER;

	if(lstParamaters.size() < 1)
		IAS_THROW(ConfigException("Missing event counter name."));

	StringList::const_iterator it=lstParamaters.begin();

	strEventCounterName=*it;

	pEventCounter=pWorkContext->getGlobalContext()->getEventCounterStore()->lookup(strEventCounterName);

}
/*************************************************************************/
Update::~Update() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Update::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strKey       = pParameters->getString("key");
	unsigned int iValue       = pParameters->getInteger("value");
	unsigned int iTimeStamp   = pParameters->getInteger("ts");

	try{

		workers::ec::Ext::RecordPtr dmRecord;

		pEventCounter->update(strKey, iValue, iTimeStamp, dmRecord);

		pParameters->setDataObject(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable), dmRecord);

	}catch(Exception& e){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();
		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}
}
/*************************************************************************/
Extern::Statement* Update::Create(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Update>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

