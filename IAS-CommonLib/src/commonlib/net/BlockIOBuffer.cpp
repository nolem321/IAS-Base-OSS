/*
 * File: IAS-CommonLib/src/commonlib/net/BlockIOBuffer.cpp
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
#include "BlockIOBuffer.h"
#include "commonlib/exception/InternalException.h"

#include "BlockIO.h"

#include <commonlib/commonlib.h>
#include <new>
#include <string.h>

namespace IAS {
namespace Net {
/*************************************************************************/
BlockIOBuffer::BlockIOBuffer(IBlockIO* pBlockIO, size_t iBufferSize):
		pBlockIO(pBlockIO),
		bEOF(false),
		ptrWriterBuffer(IAS_DFT_FACTORY<Buffer>::Create(iBufferSize+CNumGuards)),
		ptrReaderBuffer(IAS_DFT_FACTORY<Buffer>::Create(iBufferSize+CNumGuards+CNumUnGet)){
	IAS_TRACER;

	setg(ptrReaderBuffer->getBuffer<char>(),
		 ptrReaderBuffer->getBuffer<char>()+ptrReaderBuffer->getSize()-CNumUnGet-CNumGuards,
		 ptrReaderBuffer->getBuffer<char>()+ptrReaderBuffer->getSize()-CNumUnGet-CNumGuards);

	setp(ptrWriterBuffer->getBuffer<char>(),
		 ptrWriterBuffer->getBuffer<char>()+ptrWriterBuffer->getSize()-CNumGuards);

}
/*************************************************************************/
BlockIOBuffer::~BlockIOBuffer()throw(){
	IAS_TRACER;

}
/*************************************************************************/
void BlockIOBuffer::flush(){
	IAS_TRACER;

	int iRes;

	size_t iWritten;

	if(pBlockIO->write(ptrWriterBuffer->getBuffer<void*>(),pptr()-pbase(),iWritten))
		IAS_THROW(BadUsageException("Asynchronous mode in BlockIOBuffer not supported."));

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"written, "<<"res="<<iWritten<<" size="<<(pptr()-pbase()));

	//TODO (M) full buffer not written at once - signals ?
	if(iWritten != pptr()-pbase())
		IAS_THROW(InternalException("TODO (M) full buffer not written at once - signals ?"));

	setp(ptrWriterBuffer->getBuffer<char>(),
		 ptrWriterBuffer->getBuffer<char>()+ptrWriterBuffer->getSize()-CNumGuards);
}
/*************************************************************************/
void BlockIOBuffer::fetch(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"fetching: "<<(void*)this);

	char *pStart=ptrReaderBuffer->getBuffer<char>()+CNumUnGet;

	size_t iDataSize;

	if(pBlockIO->read(pStart,ptrReaderBuffer->getSize()-CNumUnGet-CNumGuards,iDataSize))
			IAS_THROW(BadUsageException("Asynchronous mode in BlockIOBuffer not supported."));

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"read, "<<"len="<<iDataSize);

	bEOF = (iDataSize == 0);

	if(bEOF)
		return;

	setg(ptrReaderBuffer->getBuffer<char>(),pStart,pStart+iDataSize);
}
/*************************************************************************/
 std::streamsize BlockIOBuffer::showmanyc(){
	IAS_TRACER;

	std::streamsize iRes;

	if(egptr() != gptr()){
		iRes=egptr() - gptr();
	}else{
		fetch();

		if(bEOF)
			iRes=0;
		else
			iRes=egptr() - gptr();
	}

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"showmanyc: "<<iRes);

	return iRes;
}
 /*************************************************************************/
 std::streamsize BlockIOBuffer::xsputn (const char* s, std::streamsize n){
 	IAS_TRACER;

 	std::streamsize iWritten=0;

 	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),(void*)pptr()<<" "<<(void*)epptr());

 	while(n>0){

 		std::streamsize iAvailable=epptr()-pptr();

 		if(n<=iAvailable){
 			memcpy(pptr(),s,n);
 			pbump(n);
 			iWritten+=n;
 			n=0;
 		}else{
 			memcpy(pptr(),s,iAvailable);
 			s+=iAvailable;
 			n-=iAvailable;
 			iWritten+=iAvailable;
 			pbump(iAvailable);
 		}

 		if(epptr() == pptr())
 			flush();

 	}

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),(void*)pptr()<<" "<<(void*)epptr());

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"written: "<<iWritten);

 	return iWritten;
 }

 /*************************************************************************/
BlockIOBuffer::int_type BlockIOBuffer::overflow( BlockIOBuffer::int_type c){
	IAS_TRACER;
	flush();
	*pptr()=c;
	pbump(1);
	return c;
}
/*************************************************************************/
BlockIOBuffer::int_type BlockIOBuffer::sync(){
	IAS_TRACER;
	flush();
	return 0;
}
/*************************************************************************/
std::streamsize BlockIOBuffer::xsgetn (char* s, std::streamsize n){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"read: "<<", size="<<n);

	int iCopied=0;
	int iLeft=n;

	if(bEOF)
		return EOF;

	while(iLeft){

		if(gptr() == egptr()) {
			fetch();
			if(bEOF)
				return iCopied ? iCopied : EOF;
		}

		size_t iCopyLen = egptr() - gptr();

		if(iLeft<iCopyLen)
			iCopyLen=iLeft;

		memcpy(s,gptr(),iCopyLen);
		gbump(iCopyLen);
		iCopied+=iCopyLen;
		s+=iCopyLen;
		iLeft-=iCopyLen;
	}

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"returned: size="<<iCopied);
	return iCopied;
}
/*************************************************************************/
BlockIOBuffer::int_type BlockIOBuffer::underflow() {
	//IAS_TRACER;

	fetch();

	if(bEOF)
		return EOF;

	return traits_type::to_int_type(*gptr());;
}
/*************************************************************************/
}
}
