/*
 * File: IAS-CommonLib/src/commonlib/net/http/ChunkedInputPump.cpp
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
#include "ChunkedInputPump.h"
#include <commonlib/logger/logger.h>
#include <commonlib/exception/EndOfDataException.h>
#include <commonlib/tools/MiscTools.h>
#include <commonlib/exception/BadUsageException.h>

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
ChunkedInputPump::ChunkedInputPump(IBlockIO* pBlockIO, std::ostream& os):
		pBlockIO(pBlockIO),
	Buffer(4096),
	iState(S_Length),
	iChunkSize(0),
	bEndOfData(false),
	os(os){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pBlockIO);
}
/*************************************************************************/
ChunkedInputPump::~ChunkedInputPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IBlockIO::Result ChunkedInputPump::pump(){
	IAS_TRACER;

	while(! (bEndOfData && iState == S_Length)){

		size_t      iBytesLeft;

		char *sBuffer=getBuffer<char>();

		IBlockIO::Result rc=pBlockIO->read(sBuffer, getSize(), iBytesLeft);

		if(rc != IBlockIO::RC_OK)
			return rc;

		if(!iBytesLeft)
			IAS_THROW(BadUsageException("Unexpected end of input in ChunkedInputPump."));

		while(iBytesLeft){

			IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"s: "<<iState<<", cs: "<<iChunkSize);

			switch(iState){

				case S_Length:

					if(*sBuffer == '\r')
						iState=S_CR;
					else
						iChunkSize = (iChunkSize<<4) + MiscTools::HexValue(*sBuffer);

					sBuffer++;
					iBytesLeft--;
					break;

				case S_CR:
					if(*sBuffer == '\n'){

						if(iChunkSize > 0){
							iState=S_Data;
						}else{
							iState=S_DataCR;
							bEndOfData=true;
						}

						sBuffer++;
						iBytesLeft--;
					}else
						IAS_THROW(BadUsageException("Missing LR after CR in ChunkedInputPump data length."))

					break;
				case S_Data:

						if(iChunkSize <= iBytesLeft){
							os.write(sBuffer,iChunkSize);
							iBytesLeft-=iChunkSize;
							sBuffer+=iChunkSize;
							iState=S_DataCR;
						}else{
							os.write(sBuffer,iBytesLeft);
							iChunkSize-=iBytesLeft;
							iBytesLeft=0;
						}
					break;

				case S_DataCR:
						if(*sBuffer == '\r'){
							iState=S_DataLF;
							sBuffer++;
							iBytesLeft--;
						}else{
							IAS_THROW(BadUsageException("Missing CR after data in ChunkedInputPump."))
						}
					break;

				case S_DataLF:
					if(*sBuffer == '\n'){
						iState=S_Length;
						iChunkSize=0;
						sBuffer++;
						iBytesLeft--;
					}else{
						IAS_THROW(BadUsageException("Missing LR after CR in ChunkedInputPump data."))
					}
					break;

			default:
				IAS_THROW(InternalException());
			}
		}
	}

	os.flush();
	return IBlockIO::RC_OK;

}

/*************************************************************************/
}
}
}
