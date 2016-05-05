/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/timer/InputBase.cpp
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
#include "InputBase.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Message.h"
#include <unistd.h>

namespace IAS {
namespace QS {
namespace SDF {
namespace Timer {

/*************************************************************************/
InputBase::InputBase(const API::Destination& destination):
		File::InputBase(destination),
		tsLastAction(true),
		bFirst(true){
	IAS_TRACER;
}
/*************************************************************************/
InputBase::~InputBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
unsigned int InputBase::skip(unsigned int iOffset){
	IAS_TRACER;
	return 0;
}
/*************************************************************************/
Message* InputBase::receiveImpl(int iTimeWait,bool bRemoveInputTimer){

	IAS_TRACER;

	iTimeWait*=1000;

	long iSinceLastAction = tsLastAction.getSample();

	if(!bFirst && iTimeWait - iSinceLastAction > 0){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Sleeping: "<<(iTimeWait - iSinceLastAction)<<"micro sec!, timeout="<<iTimeWait<<", opetime="<<iSinceLastAction);
		Thread::Cancellation tc(true);
		usleep(iTimeWait - iSinceLastAction);
	}

	bFirst=false;

	IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage;

	if(strFileName.substr(0,6).compare("/clock")==0){
		StringStream ssTmp;
		Timestamp tsCurrent(true);
		ssTmp<<"{ \"_value\"   : \""<<tsCurrent.toString()<<"\",";
		ssTmp<<"  \"_dmType\" : \"IAS/DM/Default#DateTime\" }";
		ptrMessage=IAS_DFT_FACTORY<Message>::Create< std::istream& >(ssTmp);
		ptrMessage->getAttributes()->setFormat("JSON");
		ptrMessage->getAttributes()->setMID(tsCurrent.toString("T%Y%m%d%H%M%S%F"));
	}else{
		ptrMessage=File::InputBase::receiveImpl(0,bRemoveInputTimer);
	}

	tsLastAction.start();
	iCount=0;
	return ptrMessage.pass();
}
/*************************************************************************/
unsigned int InputBase::getNumMessages(){
	IAS_TRACER;
	return 1;
}
/*************************************************************************/
}
}
}
}
