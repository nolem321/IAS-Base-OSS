/*
 * File: IAS-CommonLib/src/commonlib/net/async/KnownLengthInputPump.cpp
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
#include "KnownLengthInputPump.h"
#include <commonlib/logger/logger.h>
#include <commonlib/exception/EndOfDataException.h>

#include <string.h>
namespace IAS {
namespace Net {
namespace Async {

/*************************************************************************/
KnownLengthInputPump::KnownLengthInputPump(IBlockIO* pBlockIO, std::ostream& os, size_t iDataSize):
		pBlockIO(pBlockIO),
	Buffer(0x10000),
	iDataLeft(iDataSize),
	os(os){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pBlockIO);
}
/*************************************************************************/
KnownLengthInputPump::~KnownLengthInputPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IBlockIO::Result KnownLengthInputPump::pump(){
	IAS_TRACER;

	if(!iDataLeft)
		return IBlockIO::RC_OK;

	while(true){

		size_t iDataLen;
		size_t iBytesToRead = iDataLeft > getSize() ? getSize() : iDataLeft;

		IBlockIO::Result rc=pBlockIO->read(getBuffer<char>(), iBytesToRead,iDataLen);

		if(rc != IBlockIO::RC_OK)
			return rc;

		if(!iDataLen)
			IAS_THROW(EndOfDataException("Unexpected end of data in KnownLengthInputPump."));

		os.write(getBuffer<char>(),iDataLen);

		iDataLeft-=iDataLen;

		if(!iDataLeft){
			os.flush();
			return IBlockIO::RC_OK;
		}

	}

}
/*************************************************************************/
}
}
}
