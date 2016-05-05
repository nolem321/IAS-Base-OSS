/*
 * File: IAS-CommonLib/src/commonlib/net/async/InputDataPump.cpp
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
#include "InputDataPump.h"
#include <commonlib/logger/logger.h>
#include <commonlib/exception/EndOfDataException.h>
#include <commonlib/exception/BadUsageException.h>

#ifdef __linux__
#include <arpa/inet.h>
#else
#include <netinet/in.h>
#endif

#include <string.h>
namespace IAS {
namespace Net {
namespace Async {

/*************************************************************************/
InputDataPump::InputDataPump(IBlockIO* pBlockIO, std::ostream& os):
		pBlockIO(pBlockIO),
	Buffer(4096),
	iOffset(0),
	os(os){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pBlockIO);
}
/*************************************************************************/
InputDataPump::~InputDataPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IBlockIO::Result InputDataPump::pump(){
	IAS_TRACER;

	while(true){

		size_t iTmpDataLen;
		size_t iBufferDataLen;

		if(iOffset < CLenghtOffset){
			IBlockIO::Result rc=pBlockIO->read(getBuffer<char>()+iOffset, CLenghtOffset-iOffset,iTmpDataLen);
			if(rc != IBlockIO::RC_OK)
				return rc;

		}else{

			iBufferDataLen = ntohl(*getBuffer<DataSize>());

			if( iBufferDataLen == 0){
				os.flush();
				return IBlockIO::RC_OK;
			}

			if( iBufferDataLen > 100000)
				IAS_THROW(InternalException("Messed data length."));

			if(iBufferDataLen > this->iSize)
				resize(iBufferDataLen+CLenghtOffset);


			IBlockIO::Result rc=pBlockIO->read(getBuffer<char>()+iOffset, iBufferDataLen-(iOffset-CLenghtOffset),iTmpDataLen);
			if(rc != IBlockIO::RC_OK)
				return rc;

		}


		if(iTmpDataLen == 0)
			IAS_THROW(EndOfDataException("Data pump stream stopped."));


		iOffset+=iTmpDataLen;

		if(iOffset > CLenghtOffset && iOffset - CLenghtOffset == iBufferDataLen){

			IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"pumping="<<iBufferDataLen);

			os.write(getBuffer<char>()+CLenghtOffset,iBufferDataLen);

			if(!os.good())
				IAS_THROW(BadUsageException("Cannot write (pump) to the output stream."));

			iOffset=0;
		}

	}

}
/*************************************************************************/
}
}
}
