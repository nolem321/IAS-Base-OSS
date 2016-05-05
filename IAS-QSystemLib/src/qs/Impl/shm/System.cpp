/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/System.cpp
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
#include "System.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Attachment.h"

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
System::System(){}
/*************************************************************************/
System::~System() throw () {}
/*************************************************************************/
void  System::create(::org::invenireaude::qsystem::Ext::SystemPtr dmSystem){
	IAS_TRACER;

	if(!ptrAttachment.isNull())
		IAS_THROW(InternalException("TODO better exception - only one connection possible"));

	ptrAttachment=IAS_DFT_FACTORY<Attachment>::Create(dmSystem);
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	if(!ptrAttachment){
		ptrAttachment=IAS_DFT_FACTORY<Attachment>::Create(dmConnection);
	}else{
		if(ptrAttachment->getName().compare(dmConnection->getHost()))
			IAS_THROW(InternalException("TODO better exception - only one connection possible"));
	}

	return ptrAttachment->createConnection(dmConnection);
}

/*************************************************************************/
}
}
}

