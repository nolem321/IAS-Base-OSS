/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/file/OutputDriver.cpp
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
namespace File {

static String getDestinationFile(const API::Destination& destination){

	IAS_TRACER;

	String strName(EnvTools::Substitute(destination.getName()));

	if(strName[0] == '/')
		return strName;

	if(strName.compare("stdout") == 0 ||
	   strName.compare("stdout_fmt") == 0)
		return "/" + strName;

	URI uri(strName);
	return "/"+uri.getPath();
}
/*************************************************************************/
OutputDriver::OutputDriver(const API::Destination& destination):
		strFileName(getDestinationFile(destination)),
		iCount(0){
	IAS_TRACER;
}

/*************************************************************************/
OutputDriver::~OutputDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool OutputDriver::send(Message* pMessage){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(strFileName.compare("/stdout")==0){

		pMessage->write(std::cout);
		std::cout.flush();

	}else if(strFileName.compare("/stdout_fmt")==0){

		API::Attributes* pAttributes=pMessage->getAttributes();
		std::cout<<"\n =================================="<<std::endl;
		std::cout<<" =========== Attributes ==========="<<std::endl;
		std::cout<<" =================================="<<std::endl;
		for(API::Attributes::const_iterator it=pAttributes->begin();
			it != pAttributes->end(); it++){
			std::cout<<"["<<it->first<<"]="<<it->second<<std::endl;
		}
		std::cout<<" ============== DATA =============="<<std::endl;
		pMessage->write(std::cout);
		std::cout<<" ============== END  ==============\n"<<std::endl;

		std::cout.flush();

	}else{

		if(iCount)
			return false;

		OutputFile outFile(strFileName);
		outFile.open();

		if(!outFile.isOpenedAndGood())
			IAS_THROW(SystemException(outFile.getName()));

		pMessage->write(outFile.getStreamRef());
	}

	iCount++;

	return true;
}
/*************************************************************************/
}
}
}
}
