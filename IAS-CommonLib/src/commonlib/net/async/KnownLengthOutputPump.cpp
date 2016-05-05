/*
 * File: IAS-CommonLib/src/commonlib/net/async/KnownLengthOutputPump.cpp
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
#include "KnownLengthOutputPump.h"
#include <commonlib/logger/logger.h>
#include <commonlib/exception/EndOfDataException.h>

#include <string.h>

namespace IAS {
namespace Net {
namespace Async {

/*************************************************************************/
KnownLengthOutputPump::KnownLengthOutputPump(IBlockIO* pBlockIO, std::istream& is, size_t iDataSize):
		pBlockIO(pBlockIO),
		iDataLeft(iDataSize),
		iWriterLeft(0),
		iWrittenBytes(0),
		Buffer(4096),
		is(is){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pBlockIO);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"DataSize: "<<iDataSize);
}
/*************************************************************************/
KnownLengthOutputPump::~KnownLengthOutputPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IBlockIO::Result KnownLengthOutputPump::pump() {
	IAS_TRACER;

	if(!iDataLeft)
		return IBlockIO::RC_OK;

	while(iDataLeft && !iWriterLeft) {

		if(!iWriterLeft){

			size_t iNowRead;
			size_t iBytesToRead = iDataLeft > getSize() ? getSize() : iDataLeft;

			is.read(getBuffer<char>(),iBytesToRead);

			if((iNowRead=is.gcount()) == 0)
				IAS_THROW(EndOfDataException("Unexpected end of data in KnownLengthOutputPump."));

			iWrittenBytes=0;
			iWriterLeft=iNowRead;

			iDataLeft-=iNowRead;
		}

		do {

			size_t iNowWritten;

			IBlockIO::Result rc=pBlockIO->write(getBuffer<char>()+iWrittenBytes, iWriterLeft, iNowWritten);

			if(rc != IBlockIO::RC_OK)
				return rc;

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"write("<<(void*)pData<<" + "<<iNowWritten<<", "<<iWriterLeft);

			iWrittenBytes+=iNowWritten;
			iWriterLeft-=iNowWritten;

		}while(iWriterLeft);

	}

	return IBlockIO::RC_OK; //Avoid warnings
}
/*************************************************************************/
}
}
}
