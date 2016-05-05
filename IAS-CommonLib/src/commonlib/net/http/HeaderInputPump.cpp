/*
 * File: IAS-CommonLib/src/commonlib/net/http/HeaderInputPump.cpp
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
#include "HeaderInputPump.h"

#include <commonlib/logger/logger.h>

#include "Request.h"

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
HeaderInputPump::HeaderInputPump(Header *pHeader, IBlockIO* pBlockIO):
	Buffer(4000),
	pBlockIO(pBlockIO),
	pHeader(pHeader),
	iCounter(0){
	IAS_TRACER;

}
/*************************************************************************/
HeaderInputPump::~HeaderInputPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool HeaderInputPump::locateEndOfHeader(size_t& iNewBytes){

	char *s=getBuffer<char>();

	size_t iBytesLeft=iNewBytes;

	while(iBytesLeft-- > 0){
		if(iCounter & 0x01){
			if(*s == '\n' )
				iCounter++;
			else
				iCounter=0;
		}else{
			if(*s == '\r' )
				iCounter++;
			else
				iCounter=0;
		}

		s++;

		if(iCounter == 4){

			if(iBytesLeft)
				pBlockIO->undo(s,iBytesLeft);

			iNewBytes-=iBytesLeft;
			return true;
		}

	}

	return false;
}
/*************************************************************************/
IBlockIO::Result HeaderInputPump::pump(){
	IAS_TRACER;

	size_t iNewBytes;

	IBlockIO::Result rc;

	do{
		rc=pBlockIO->read(getBuffer<char>(),getSize(),iNewBytes);

		if(iNewBytes == 0){
			IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"read "<<ssContent.str().length()<<" bytes, counter: "<<(int)iCounter);
			IAS_THROW(EndOfDataException("Data pump stream stopped."));
		}

		bool bEndOfHeader = locateEndOfHeader(iNewBytes);

		ssContent.write(getBuffer<char>(),iNewBytes);

		if(bEndOfHeader){
			IAS_LOG(LogLevel::INSTANCE.isInfo(),ssContent.str());
			pHeader->parse(ssContent);
			return IBlockIO::RC_OK;
		}

	}while(rc == IBlockIO::RC_OK);

	return rc;
}
/*************************************************************************/
}
}
}
