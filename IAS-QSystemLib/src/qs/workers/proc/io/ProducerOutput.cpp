/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/ProducerOutput.cpp
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
#include "ProducerOutput.h"
#include<qs/log/LogLevel.h>
#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>

#include "../wcm/WorkContextManager.h"

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
ProducerOutput::ProducerOutput(const ::org::invenireaude::qsystem::workers::io::ProducerOutput* dmParameter,
								WCM::WorkContextManager* pWorkContextManager):
		Common(dmParameter,pWorkContextManager){
	IAS_TRACER;

	ptrProducer=getSession()->createProducer(destination);

}
/*************************************************************************/
ProducerOutput::~ProducerOutput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ProducerOutput::put(API::Message* pMessage){
	IAS_TRACER;
	ptrProducer->produce(pMessage);
}
/*************************************************************************/
}
}
}
}
}
