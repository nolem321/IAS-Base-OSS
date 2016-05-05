/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/RequesterOutput.cpp
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
#include "RequesterOutput.h"
#include<qs/log/LogLevel.h>
#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
RequesterOutput::RequesterOutput(const ::org::invenireaude::qsystem::workers::io::RequesterOutput* dmParameter,
								WCM::WorkContextManager* pWorkContextManager):
		Common(dmParameter,pWorkContextManager){
	IAS_TRACER;

	inputDestination=dmParameter->getInputDestination();
	ptrRequester=getSession()->createRequester(destination,inputDestination);

}
/*************************************************************************/
RequesterOutput::~RequesterOutput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void RequesterOutput::put(API::Message* pMessage){
	IAS_TRACER;
	ptrRequester->request(pMessage);
}
/*************************************************************************/
API::Message* RequesterOutput::get(API::Attributes* pAttributes, int iTimeout){
	IAS_TRACER;
	return ptrRequester->receive((iTimeout == Input::CDefaultTimeout ? this->iTimeout : iTimeout),pAttributes);
}
/*************************************************************************/
void RequesterInputProxy::receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 DM::DataObjectPtr& dmData,
						 int iTimeout){
	pRequester->receive(dmContext,dmData,iTimeout);
}
/*************************************************************************/
void RequesterInputProxy::receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
										   API::Message::PtrHolder& ptrMessage,
										   int iTimeout){
	pRequester->receive(dmContext, ptrMessage,iTimeout);
}
/*************************************************************************/
}
}
}
}
}
