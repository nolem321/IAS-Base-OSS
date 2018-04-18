/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/dir/InputBase.cpp
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
namespace Dir {

/*************************************************************************/
InputBase::InputBase(const API::Destination& destination):
		strDirName(EnvTools::Substitute(String("/")+destination.getName())),
		dirReader(strDirName),
		iCount(0){
	IAS_TRACER;

	dirReader.read();

	itEntries=dirReader.begin();
}
/*************************************************************************/
InputBase::~InputBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
unsigned int InputBase::skip(unsigned int iOffset){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	unsigned int iResult = 0;

	while(itEntries != dirReader.end() && iOffset-- > 0){

		while(itEntries != dirReader.end() &&
			  (*itEntries)->iType != SYS::FS::DirectoryReader::FT_FILE)
		itEntries++;

		iResult++;
	}

	return iResult;
}
/*************************************************************************/
Message* InputBase::receiveImpl(int iTimeWait, bool bRemoveInputFile, API::Attributes* pSelector){

	IAS_TRACER;

	String strFileName;

	{
		Mutex::Locker locker(mutex);
		String        strMatchName;

		if(pSelector && pSelector->isSetMID()){
			strMatchName = pSelector->getMID();
			IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Matching: "<<strMatchName);

		}

		while(itEntries != dirReader.end() &&
				((*itEntries)->iType != SYS::FS::DirectoryReader::FT_FILE ||
				(!strMatchName.empty() && strMatchName.compare((*itEntries)->strFile) != 0))){

			IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Skipping: "<<(*itEntries)->strFile<<", "<<(*itEntries)->iType<<", "<<SYS::FS::DirectoryReader::FT_FILE);

			itEntries++;
		}

		while(itEntries == dirReader.end()){

			if(iTimeWait == 0)
				IAS_THROW(EndOfDataException(strDirName+" processed all files."));

			int iPoolInterval = 1000;
			if(iTimeWait <  1000)
				iPoolInterval = iTimeWait;

			iTimeWait-=iPoolInterval;

			IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Sleeping: "<<iPoolInterval<<"ms. , waiting for: "<<strDirName);

			{
				Thread::Cancellation tc(true);
				usleep(iPoolInterval*1000);
			}

			IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Recycle: "<<strDirName);
			dirReader.read();
			IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Recycle completed");

			itEntries = dirReader.begin();

			while(itEntries != dirReader.end() &&
						(*itEntries)->iType != SYS::FS::DirectoryReader::FT_FILE)
					itEntries++;
		}

		strFileName=(*itEntries)->strFile;
		itEntries++;
	}

	InputFile inFile(strDirName+"/"+strFileName);
	inFile.open();

	if(!inFile.isOpenedAndGood())
		IAS_THROW(SystemException(inFile.getName()));

	IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage(
			IAS_DFT_FACTORY<Message>::Create< std::istream& >(inFile.getStreamRef())
		);

	ptrMessage->getAttributes()->setMID(strFileName);
	updateFormat(ptrMessage,strFileName);

	if(bRemoveInputFile)
		InputFile::Remove(inFile.getName());

	return ptrMessage.pass();
}
/*************************************************************************/
unsigned int InputBase::getNumMessages(){
	IAS_TRACER;

	dirReader.read();
	itEntries=dirReader.begin();
	return dirReader.size()-iCount;
}
/*************************************************************************/
}
}
}
}
