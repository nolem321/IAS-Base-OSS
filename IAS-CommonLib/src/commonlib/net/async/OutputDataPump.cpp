/*
 * File: IAS-CommonLib/src/commonlib/net/async/OutputDataPump.cpp
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
#include "OutputDataPump.h"
#include <commonlib/logger/logger.h>
#include <string.h>

#ifdef __linux__
#include <arpa/inet.h>
#else
#include <netinet/in.h>
#endif

namespace IAS {
namespace Net {
namespace Async {

/*************************************************************************/
OutputDataPump::OutputDataPump(IBlockIO* pBlockIO, std::istream& is):
		pBlockIO(pBlockIO),
		bEndOfData(false),
	iWrittenBytes(0),
	iDataSize(0),
	Buffer(4096),
	is(is){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pBlockIO);
}
/*************************************************************************/
OutputDataPump::~OutputDataPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IBlockIO::Result OutputDataPump::pump() {
	IAS_TRACER;

	while(true) {

		if(iWrittenBytes == iDataSize) {

			if(bEndOfData)
				return IBlockIO::RC_OK;

			iWrittenBytes = 0;

			is.read(getBuffer<char>()+CLenghtOffset,iSize-CLenghtOffset);

			if((iDataSize=is.gcount()) == 0)
				bEndOfData=true;

			*getBuffer<DataSize>()=htonl(iDataSize);
			iDataSize+=CLenghtOffset;
		}

		do {

			size_t iNowWritten;

			IBlockIO::Result rc=pBlockIO->write(getBuffer<char>()+iWrittenBytes, iDataSize-iWrittenBytes,iNowWritten);
			if(rc != IBlockIO::RC_OK)
				return rc;

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"write("<<(void*)pData<<" + "<<iNowWritten<<", "<<(iDataSize-iWrittenBytes));

			iWrittenBytes+=iNowWritten;

		}while(iWrittenBytes < iDataSize);

	}

}
/*************************************************************************/
}
}
}
