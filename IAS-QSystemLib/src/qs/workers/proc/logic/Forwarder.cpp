/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/Forwarder.cpp
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
#include "Forwarder.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
Forwarder::Forwarder(const ::org::invenireaude::qsystem::workers::logic::Forwarder* dmParameters,
					 WCM::WorkContextManager* pWorkContextManager):
		LogicBase(dmParameters,pWorkContextManager){
	IAS_TRACER;
}

/*************************************************************************/
Forwarder::~Forwarder() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Forwarder::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Forwarder starts.");
	getOutput()->send(dmContext,dmData);
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Forwarder ends.");
}
/*************************************************************************/
void Forwarder::computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
				           API::Message* pMessage){

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Forwarder starts.");
	getOutput()->send(dmContext,*pMessage->getContent());
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Forwarder ends.");
}
/*************************************************************************/
}
}
}
}
}
