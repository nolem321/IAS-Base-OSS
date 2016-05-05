/*
 * File: IAS-CommonLib/src/commonlib/memory/buffer/StreamMemoryBuffer.cpp
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
#include "StreamMemoryBuffer.h"
#include "commonlib/exception/InternalException.h"

#include "../ma/Allocator.h"

#include <commonlib/commonlib.h>
#include <new>
#include <string.h>

namespace IAS {

/*************************************************************************/
const char StreamMemoryBuffer::Info::C_Tag[C_TagSize+1] = "SMBF";
size_t StreamMemoryBuffer::CMinInitialSegmentSize=sizeof(StreamMemoryBuffer::Segment) + 16;
/*************************************************************************/
StreamMemoryBuffer::Info::Info(size_t iInitalSegmentSize):
		iInitalSegmentSize(iInitalSegmentSize),
		iNumSegments(0),
	    pHead(0),
	    pTail(0),
		pAppendCursor(0){
	IAS_TRACER;
	::strncpy(sTag,C_Tag,C_TagSize);

}
/*************************************************************************/
StreamMemoryBuffer::Segment::Segment(size_t iSize):
		pNext(0),
		iDataSize(iSize){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"New segment: "<<(void*)this<<", size="<<iSize);

	if(iSize <= 1 )
		IAS_THROW(InternalException("iDataSize <= 0 in StreamMemoryBuffer::Segment::Segment"));

};
/*************************************************************************/
void* StreamMemoryBuffer::Create(Allocator* pAllocator,
								 size_t iInitalSegmentSize){
	IAS_TRACER;

	if(iInitalSegmentSize < CMinInitialSegmentSize)
		iInitalSegmentSize = CMinInitialSegmentSize;

	Info* pInfo=(Info*)pAllocator->allocate(sizeof(Info));
	new(pInfo)Info(iInitalSegmentSize);

	pInfo->allocateNextSegment(pAllocator);
	return pInfo;
}
/*************************************************************************/
StreamMemoryBuffer::StreamMemoryBuffer(void* pAddress,
									   Allocator* pAllocator):
		pAllocator(pAllocator){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pAddress);
	pInfo=(Info*)pAddress;

	if(strncmp(pInfo->sTag,Info::C_Tag,Info::C_TagSize) != 0)
			IAS_THROW(InternalException(String("No StreamMemoryBuffer::Info found.")));

	pReaderActive=pInfo->pHead;
	pWriterActive=pInfo->pTail;

	updateWritePointers(pInfo->pAppendCursor, pWriterActive->getDataStart() + pWriterActive->getDataSize() - pInfo->pAppendCursor );

	updateReadPointers(pReaderActive->getDataStart());

}
/*************************************************************************/
StreamMemoryBuffer::~StreamMemoryBuffer()throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StreamMemoryBuffer::Info::allocateNextSegment(Allocator* pAllocator){
	IAS_TRACER;

	size_t iNewSize= (iNumSegments < 8) ?
			iInitalSegmentSize<<(iNumSegments ? iNumSegments + 3 : 0) :
			iInitalSegmentSize << 11;

	Segment *pNewSegment=new(pAllocator->allocate(iNewSize))Segment(iNewSize-sizeof(Segment));

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"New segment: "<<(void*)this<<", size="<<iNewSize<<", at="<<(void*)pNewSegment);

	if(!pHead)
		pHead=pNewSegment;

	if(pTail)
		pTail->pNext=pNewSegment;

	iNumSegments++;

	pTail=pNewSegment;

	pAppendCursor=pTail->getDataStart();
}
/*************************************************************************/
bool StreamMemoryBuffer::Info::isTail(Segment* pSegment)const{
	IAS_TRACER;
	return pSegment == pTail;
	//return pSegment->pNext == NULL;
}
/*************************************************************************/
void StreamMemoryBuffer::updateWritePointers(TByte *pDataStart, size_t iBufferLen){
	IAS_TRACER;

	setp(pDataStart, pDataStart + iBufferLen);

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"setp("<<
			(void*)pDataStart<<", len="<<iBufferLen<<")");

}
/*************************************************************************/
void StreamMemoryBuffer::updateReadPointers(char *pReaderCursor){
	IAS_TRACER;

	setg(pReaderActive->getDataStart(),
		 pReaderCursor,
		 pInfo->isTail(pReaderActive) ?
		 pInfo->pAppendCursor : pReaderCursor+pReaderActive->getDataSize());

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"setg("<<
			(void*)(pReaderActive->getDataStart())<<", "<<(void*)pReaderCursor<<", "
			<<(void*)(pReaderActive == pInfo->pTail ?
					 pInfo->pAppendCursor : pReaderCursor+pReaderActive->getDataSize())<<")");

}
/*************************************************************************/
void StreamMemoryBuffer::allocateSegment(){
	IAS_TRACER;

	pInfo->allocateNextSegment(pAllocator);

	pWriterActive=pInfo->pTail;

}
/*************************************************************************/
 std::streamsize StreamMemoryBuffer::showmanyc(){
	IAS_TRACER;

	std::streamsize iRes;

	if(egptr() != gptr()){
		iRes=egptr() - gptr();
	}else if(pInfo->isTail(pReaderActive)){

		if(pInfo->pAppendCursor == egptr()){
			iRes=0;
		}else{
			updateReadPointers(gptr());
			return showmanyc();
		}

	}else if(!pInfo->isTail(pReaderActive->pNext)){
		iRes=pReaderActive->pNext->getDataSize();
	}else{
		iRes=pInfo->pAppendCursor - pReaderActive->pNext->getDataStart();
	}

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"showmanyc: "<<(void*)pInfo<<"res="<<iRes);

	return iRes;
}
 /*************************************************************************/
 void StreamMemoryBuffer::nextWriterSegment(){
	 IAS_TRACER;

	 if(pInfo->isTail(pWriterActive)){
		 allocateSegment();
	 }else{
		 pWriterActive=pWriterActive->pNext;
	 }

	 updateWritePointers(pWriterActive->getDataStart(),pWriterActive->getDataSize());
 }
 /*************************************************************************/
 std::streamsize StreamMemoryBuffer::xsputn (const char* s, std::streamsize n){
 	IAS_TRACER;

 	std::streamsize iWritten=0;

 	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),(void*)pptr()<<" "<<(void*)epptr()<<" "<<(void*)(pInfo->pAppendCursor));

 	while(n>0){

		sync();

 		std::streamsize iAvailable = epptr()- pptr();

 		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"write: "<<n<<", iAvailable="<<iAvailable);

 		if(iAvailable <= 0){
 			nextWriterSegment();
 			iAvailable = epptr()- pptr();
 		}

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

 	}/* WHILE: n > 0 */

	if(epptr() == pptr())
		nextWriterSegment();

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),(void*)pptr()<<" "<<(void*)epptr()<<" "<<(void*)(pInfo->pAppendCursor));

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"written: "<<iWritten);

 	return iWritten;
 }

 /*************************************************************************/
StreamMemoryBuffer::int_type StreamMemoryBuffer::overflow( StreamMemoryBuffer::int_type c){
	IAS_TRACER;
	nextWriterSegment();
	*pptr()=c;
	pbump(1);
	return c;
}
/*************************************************************************/
StreamMemoryBuffer::int_type StreamMemoryBuffer::sync(){
	IAS_TRACER;

	if(pInfo->isTail(pWriterActive) && pInfo->pAppendCursor < pptr() )
		pInfo->pAppendCursor=pptr();

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),(void*)gptr()<<" "<<(void*)(pInfo->pAppendCursor));
	return 0;
}
/*************************************************************************/
std::streamsize StreamMemoryBuffer::xsgetn (char* s, std::streamsize n){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"read: "<<(void*)pInfo<<", size="<<n);

	int iCopied=0;
	int iLeft=n;

	if(pInfo->pAppendCursor == gptr()){
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo()," EOF !!! ");
		return 0;
	}

	while(iLeft){

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"before: "<<(void*)pInfo<<", gptr()="<<(void*)gptr()<<", egptr()="<<(void*)egptr()<<", size="<<iCopied);

		if(gptr() == egptr()) {
			if(underflow() == EOF)
				return iCopied ;
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

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"returned: "<<(void*)pInfo<<", gptr()="<<(void*)gptr()<<", egptr()="<<(void*)egptr()<<", size="<<iCopied);
	return iCopied;
}
/*************************************************************************/
StreamMemoryBuffer::int_type StreamMemoryBuffer::underflow() {
	IAS_TRACER;

	//Check if if something was added recently
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),(void*)gptr()<<" "<<(void*)(pInfo->pAppendCursor));

	if(pInfo->pAppendCursor == gptr())
		return EOF;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),(void*)gptr()<<" "<<(void*)(pReaderActive->getDataStart()+pReaderActive->getDataSize()));

	char *pReaderCursor(NULL);

	if(!pInfo->isTail(pReaderActive) && egptr() == pReaderActive->getDataStart() + pReaderActive->getDataSize()){

		pReaderActive=pReaderActive->pNext;
		pReaderCursor=pReaderActive->getDataStart();

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Next segement, c="<<(void*)pReaderCursor);

	}else{
		pReaderCursor=gptr();
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Update: c="<<(void*)pReaderCursor);
	}

	updateReadPointers(pReaderCursor);

	if(pInfo->pAppendCursor == pReaderCursor)
		return EOF;

	return *pReaderCursor;
}
/*************************************************************************
StreamMemoryBuffer::int_type StreamMemoryBuffer::pbackfail(int_type ch) {
	IAS_TRACER;
	if (current_ == begin_ || (ch != traits_type::eof() && ch != current_[-1]))
		return traits_type::eof();

	return *--current_;
}

*************************************************************************/
void StreamMemoryBuffer::Destroy(void *pAddress, Allocator* pAllocator){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pAddress);
	Info *pInfo=(Info*)pAddress;

	if(strncmp(pInfo->sTag,Info::C_Tag,Info::C_TagSize) != 0)
				IAS_THROW(InternalException(String("No StreamMemoryBuffer::Info found.")));


	Segment* pCurrent=pInfo->pHead;
	Segment* pNext;

	while(pCurrent){

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Deleted segment: "<<(void*)pInfo<<", at="<<(void*)pCurrent);

		pNext=pCurrent->pNext;
		pAllocator->free(pCurrent);
		pCurrent=pNext;
	}

	pAllocator->free(pAddress);
}
/*************************************************************************/
std::streampos StreamMemoryBuffer::seekpos (std::streampos pos,
											std::ios_base::openmode which){

	IAS_TRACER;
	//TODO (L) full implementation of seek.

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"seekpos: "<<pos<<", w="<<which);

	if (pos != (std::streampos)0L)
		IAS_THROW(BadUsageException("StreamMemoryBuffer::seekpos is only available for pos==0."))

	if (which & std::ios_base::out) {
		pWriterActive = pInfo->pHead;
		updateWritePointers(pWriterActive->getDataStart(),pWriterActive->getDataSize());
	}

	if (which & std::ios_base::in) {
		pReaderActive = pInfo->pHead;
		updateReadPointers(pReaderActive->getDataStart());
	}


	return pos;
}
/*************************************************************************/
std::streampos StreamMemoryBuffer::seekoff(std::streamoff off, std::ios_base::seekdir way,
										   std::ios_base::openmode which){


	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"seekoff: "<<off<<", which="<<which<<", way="<<way);

	if(off != 0)
		IAS_THROW(BadUsageException("StreamMemoryBuffer::seekoff is only available for pos==0."))

	switch(way){

		case std::ios_base::beg:
				return seekpos(0,which);
			break;

		case std::ios_base::cur:
			if(off != 0)
				IAS_THROW(BadUsageException("StreamMemoryBuffer::seekoff is only available for way = beg or end."))
			break;

		case std::ios_base::end:

			if (which & std::ios_base::out) {
				pWriterActive = pInfo->pTail;
				updateWritePointers(pInfo->pAppendCursor, pWriterActive->getDataStart() + pWriterActive->getDataSize() - pInfo->pAppendCursor );
			}

			if (which & std::ios_base::in) {
				pReaderActive = pInfo->pTail;
				updateReadPointers(pInfo->pAppendCursor);
			}

			break;

	}

	std::streampos pos=0;

	if (which & std::ios_base::out) {
		for(Segment *pCurrent = pInfo->pHead; pCurrent != pWriterActive; pCurrent=pCurrent->pNext)
			pos+=pCurrent->iDataSize;
		pos+=pInfo->pAppendCursor - pWriterActive->getDataStart();
	}

	if (which & std::ios_base::in) {
		for(Segment *pCurrent = pInfo->pHead; pCurrent != pReaderActive; pCurrent=pCurrent->pNext)
			pos+=pCurrent->iDataSize;

		pos+=gptr() - pReaderActive->getDataStart();
	}

	return pos;
}
/*************************************************************************/
void StreamMemoryBuffer::dump(std::ostream& os){

	os<<"StreamMemoryBuffer, entries                    = "<<pInfo->iNumSegments<<std::endl;

	for(Segment* current=pInfo->pHead; current!=0; current=current->pNext){
		os<<(void*)current<<std::endl;
	}
}
/*************************************************************************/
}
