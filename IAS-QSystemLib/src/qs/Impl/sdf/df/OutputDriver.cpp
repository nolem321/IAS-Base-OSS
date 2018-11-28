/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/df/OutputDriver.cpp
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
#include "OutputDriver.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Message.h"

namespace IAS {
namespace QS {
namespace SDF {
namespace DF {

/*************************************************************************/
OutputDriver::OutputDriver(const API::Destination& destination):
		strFileName(String("/")+EnvTools::Substitute(destination.getName())),
		outFile(strFileName),
		osp(0),
		iCount(0){
	IAS_TRACER;


	//IAS_LOG(true,strFileName);

	if(strFileName.compare("/stdout") == 0){
		osp = &std::cout;
	}else{
		 outFile.open();
		 osp = &(outFile.getStreamRef());
	}
}

/*************************************************************************/
OutputDriver::~OutputDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool OutputDriver::send(Message* pMessage){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	iCount++;

	//std::ostream& os(outFile.getStreamRef());

	pMessage->write(*osp);
	(*osp)<<std::endl;

	return true;
}
/*************************************************************************/
}
}
}
}
