/*
 * File: IAS-CommonLib/src/commonlib/net/BlockIOUndo.cpp
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
#include "BlockIOUndo.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace Net {

/*************************************************************************/
BlockIOUndo::BlockIOUndo():
		Buffer(0),
		iUndoDataStart(0),
		iUndoDataLen(0){
	IAS_TRACER;
}

/*************************************************************************/
BlockIOUndo::~BlockIOUndo() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void BlockIOUndo::undo(void* pData, size_t iDataSize){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"undo "<<iDataSize<<" bytes.");
	size_t iRequestedBuffer = iUndoDataStart+iUndoDataLen+iDataSize;

	if(iRequestedBuffer > CMaxSize)
		IAS_THROW(BadUsageException("Too much data in the BlockIOUndo buffer."))


	if(iRequestedBuffer > getSize()){
		if(iUndoDataLen)
			resize(iRequestedBuffer);
		else
			reserve(iRequestedBuffer);
	}

	memcpy(getBuffer<char>()+iUndoDataStart+iUndoDataLen,pData,iDataSize);

	iUndoDataLen+=iDataSize;
}
/*************************************************************************/
bool BlockIOUndo::readUndone(void *pData, size_t iBufferLen, size_t& iDataSize){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),iUndoDataLen);

	if(!iUndoDataLen)
		return false;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"read undone, buf="<<iBufferLen<<", undone len="<<iUndoDataLen);

	if(iUndoDataLen > iBufferLen){
		memcpy(pData,getBuffer<char>()+iUndoDataStart,iBufferLen);
		iDataSize=iBufferLen;
		iUndoDataStart+=iBufferLen;
	}else{
		memcpy(pData,getBuffer<char>()+iUndoDataStart,iUndoDataLen);
		iDataSize=iUndoDataLen;
		iUndoDataStart=iUndoDataLen=0;
		resize(CKeepSize);
	}

	return true;
}
/*************************************************************************/
}
}
