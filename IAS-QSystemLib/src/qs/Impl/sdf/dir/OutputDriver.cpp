/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/dir/OutputDriver.cpp
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
#include <unistd.h>
namespace IAS {
namespace QS {
namespace SDF {
namespace Dir {

/*************************************************************************/
OutputDriver::OutputDriver(const API::Destination& destination):
		iCount(0){
	IAS_TRACER;

	ptrTemplate=IAS_DFT_FACTORY<Template>::Create(String("/")+destination.getName());
}

/*************************************************************************/
OutputDriver::~OutputDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool OutputDriver::send(Message* pMessage){

	IAS_TRACER;

	{
		Mutex::Locker locker(mutex);
		++iCount;
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Send["<<pMessage->getAttributes()->getMID()<<"]");

	StringStream ssFileName;

	Template::Arguments args;

	Timestamp ts;
	args.add("COUNT",TypeTools::IntToString(iCount));
	args.add("PID",TypeTools::IntToString((unsigned int)getpid()));
	args.add("TID",TypeTools::IntToString((unsigned int)pthread_self()));
	args.add("TS",ts.toString());
	args.add("ID",pMessage->getAttributes()->getMID());

	ptrTemplate->evaluate(args,ssFileName);

	OutputFile outFile(ssFileName.str());
	outFile.open();

	if(!outFile.isOpenedAndGood())
		IAS_THROW(SystemException(outFile.getName()));

	pMessage->write(outFile.getStreamRef());

	return true;
}
/*************************************************************************/
}
}
}
}
