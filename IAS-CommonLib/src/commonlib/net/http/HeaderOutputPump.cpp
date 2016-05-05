/*
 * File: IAS-CommonLib/src/commonlib/net/http/HeaderOutputPump.cpp
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
#include "HeaderOutputPump.h"

#include <commonlib/logger/logger.h>

#include "Header.h"

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
HeaderOutputPump::HeaderOutputPump(Header *pHeader, IBlockIO* pBlockIO):
	pBlockIO(pBlockIO),
	pHeader(pHeader),
	iOffset(0){

	IAS_TRACER;
	IAS_CHECK_IF_NULL(pHeader);

	StringStream ssContent;
	pHeader->serialize(ssContent);
	strContent=ssContent.str();
}
/*************************************************************************/
HeaderOutputPump::~HeaderOutputPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IBlockIO::Result HeaderOutputPump::pump(){
	IAS_TRACER;

	if(iOffset == strContent.length())
		return IBlockIO::RC_OK;

	size_t iWritten;

	IBlockIO::Result rc;

	do{
		 rc = pBlockIO->write(strContent.c_str()+iOffset,strContent.length()-iOffset,iWritten);

		if(rc == IBlockIO::RC_OK){
			iOffset+=iWritten;

			if(iOffset == strContent.length())
				return IBlockIO::RC_OK;
		}

	}while(rc == IBlockIO::RC_OK);

	return rc;
}
/*************************************************************************/
}
}
}
