/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/df/InputBase.cpp
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
#include <string>

namespace IAS {
namespace QS {
namespace SDF {
namespace DF {

/*************************************************************************/
InputBase::InputBase(const API::Destination& destination):
		strFileName(String("/")+destination.getName()),
		inFile(strFileName),
		isp(NULL),
		iCount(0){
	IAS_TRACER;

	if(strFileName.compare("/stdin") == 0){
		isp = &std::cin;
	}else{
		inFile.open();
		if(!inFile.isOpenedAndGood())
				IAS_THROW(SystemException(inFile.getName()));

		isp = &(inFile.getStreamRef());
	}

	size_t iIdx;
	if((iIdx=strFileName.find_last_of('/')) != String::npos)
		strBaseName=strFileName.substr(iIdx+1);
	else
		strBaseName=strFileName;


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"basename=["<<strBaseName<<"]");
}

/*************************************************************************/
InputBase::~InputBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
unsigned int InputBase::skip(unsigned int iOffset){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	return iCount++ == 0 ? 1 : 0;
}
/*************************************************************************/
Message* InputBase::receiveImpl(int iTimeWait){

	IAS_TRACER;

	String strLine;

	Mutex::Locker locker(mutex);


	if(isp->eof())
		IAS_THROW(EndOfDataException());

	IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage(IAS_DFT_FACTORY<Message>::Create());

	std::getline(*isp,strLine);
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"got: ["<<strLine<<"]");

	if(isp->eof())
		IAS_THROW(EndOfDataException());

	if(isp->fail())
		IAS_THROW(SystemException(inFile.getName()));

	iCount++;

	ptrMessage->getAttributes()->setMID(strBaseName+TypeTools::IntToString(iCount));
	ptrMessage->getAttributes()->setReplyTo(strFileName+".reply");

	(*ptrMessage->getContent())<<strLine;
	ptrMessage->getContent()->flush();
	updateFormat(ptrMessage,strFileName);


	return ptrMessage.pass();
}
/*************************************************************************/
unsigned int InputBase::getNumMessages(){
	IAS_TRACER;

	return access( strFileName.c_str(), F_OK ) != -1 ? 1 : 0;
}
/*************************************************************************/
}
}
}
}
