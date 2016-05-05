/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/io/Manager.cpp
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
#include "../../wcm/io/Manager.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>


#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/Controller.h>

#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>

#include <org/invenireaude/qsystem/workers/spec/Specification.h>
#include <org/invenireaude/qsystem/workers/io/InputSpecification.h>
#include <org/invenireaude/qsystem/workers/io/OutputSpecification.h>

using namespace ::org::invenireaude::qsystem::workers;

#include "Context.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace IO {

/*************************************************************************/
Manager::Manager(WorkContextManager *pWorkContextManager):pWorkContextManager(pWorkContextManager){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pWorkContextManager);

	const spec::Specification* dmSpecification=pWorkContextManager->getGlobalContext()->getSpecification();

	if(dmSpecification->getInputSpec()->isSetDefault())
		setDefaultInput(dmSpecification->getInputSpec()->getDefault());

	if(dmSpecification->isSetOutputSpec() && dmSpecification->getOutputSpec()->isSetDefault())
		setDefaultOutput(dmSpecification->getOutputSpec()->getDefault());

	if(dmSpecification->isSetOutputSpec() && dmSpecification->getOutputSpec()->isSetDefaultError())
		setDefaultError(dmSpecification->getOutputSpec()->getDefaultError());

	ptrFactory=IAS_DFT_FACTORY<Proc::IO::IOFactory>::Create(dmSpecification->getInputSpec(),
														   dmSpecification->getOutputSpec(),
														   this,
														   pWorkContextManager);
}
/*************************************************************************/
Manager::~Manager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Proc::IO::Output* Manager::getOutput(const String& strName)const{
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"output["<<strName<<"]")

	if(!hmOutputs.hasKey(strName))
		ptrFactory->createOutput(strName);

	return const_cast<Proc::IO::Output*>(hmOutputs.at(strName));

}
/*************************************************************************/
void Manager::addOutput(const String& strName, Proc::IO::Output* pOutput){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pOutput);

	if(hmOutputs.hasKey(strName))
		IAS_THROW(InternalException(strName+" already exists on outputs lists."));

	hmOutputs[strName]=pOutput;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"hmOutputs["<<strName<<"]="<<(void*)pOutput);
}
/*************************************************************************/
Proc::IO::Input* Manager::getInput(const String& strName)const{
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"input["<<strName<<"]")

	if(!hmInputs.hasKey(strName))
		ptrFactory->createInput(strName);

	return const_cast<Proc::IO::Input*>(hmInputs.at(strName));

}
/*************************************************************************/
void Manager::addInput(const String& strName, Proc::IO::Input* pInput){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pInput);

	if(hmInputs.hasKey(strName))
		IAS_THROW(InternalException(strName+" already exists on inputs lists."));

	hmInputs[strName]=pInput;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"hmInputs["<<strName<<"]="<<(void*)pInput);
}
/*************************************************************************/
Proc::IO::Controller* Manager::getController(const String& strName)const{
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"input["<<strName<<"]")

	if(!hmControllers.hasKey(strName))
		ptrFactory->createController(strName);

	return const_cast<Proc::IO::Controller*>(hmControllers.at(strName));

}
/*************************************************************************/
void Manager::addController(const String& strName, Proc::IO::Controller* pController){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pController);

	if(hmControllers.hasKey(strName))
		IAS_THROW(InternalException(strName+" already exists on input lists."));

	hmControllers[strName]=pController;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"hmControllers["<<strName<<"]="<<(void*)pController);
}
/*************************************************************************/
}
}
}
}
}
}
