/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/file/InputBase.cpp
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
namespace File {

/*************************************************************************/
InputBase::InputBase(const API::Destination& destination):
		strFileName(String("/")+destination.getName()),
		iCount(0){
	IAS_TRACER;

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
Message* InputBase::receiveImpl(int iTimeWait,bool bRemoveInputFile){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(iCount++)
		IAS_THROW(EndOfDataException(strFileName+" already processed."));

	if(strFileName.compare("/stdin")==0)
		return IAS_DFT_FACTORY<Message>::Create< std::istream& >(std::cin);

	InputFile inFile(EnvTools::Substitute(strFileName));
	inFile.open();

	if(!inFile.isOpenedAndGood())
		IAS_THROW(SystemException(inFile.getName()));

	IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage(
			IAS_DFT_FACTORY<Message>::Create< std::istream& >(inFile.getStreamRef())
		);

	ptrMessage->getAttributes()->setMID(strBaseName);
	ptrMessage->getAttributes()->setReplyTo("file://"+strFileName+".reply");
	updateFormat(ptrMessage,strFileName);

	if(bRemoveInputFile)
		InputFile::Remove(inFile.getName());

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
