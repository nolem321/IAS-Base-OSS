/*
 * File: IAS-CommonLib/src/commonlib/memory/buffer/StreamMemoryBuffer.h
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
#ifndef _IAS_StreamMemoryBuffer_H_
#define _IAS_StreamMemoryBuffer_H_

#include <streambuf>
#include <cstddef>

#include "commonlib/memory/ma/Factory.h"

namespace IAS {
class Allocator;

/*************************************************************************/
/** The StreamMemoryBuffer class.
 *
 */
class StreamMemoryBuffer : public std::streambuf {
public:

	virtual ~StreamMemoryBuffer()throw();

	static void* Create(Allocator* pAllocator,
							   	   	   size_t iInitalSegmentSize=256);

	static void Destroy(void *pAddress, Allocator* pAllocator);

	static size_t CMinInitialSegmentSize;

protected:

	StreamMemoryBuffer(void *pAddress, Allocator* pAllocator);

	typedef  char     TByte;

	struct Segment{
			Segment* pNext;
			size_t   iDataSize;
			Segment(size_t iTotalSize);

			inline TByte* getDataStart(){
				return (TByte*)(this + 1);
			}

			inline size_t getDataSize()const{
				return iDataSize;
			}

		};


	struct Info{

		 static const size_t C_TagSize=4;

		 char sTag[C_TagSize];

		 size_t iInitalSegmentSize;
		 size_t iNumSegments;

		 Segment* pHead;
		 Segment* pTail;

		 TByte   *pAppendCursor;

		 Info(size_t iInitalSegmentSize);
		 void allocateNextSegment(Allocator* pAllocator);

		 bool isTail(Segment* pSegment)const;

		 static const char C_Tag[];
	};



	virtual int_type overflow(int_type c);
	virtual int sync();
	virtual int_type underflow();

	virtual std::streamsize xsgetn (char* s, std::streamsize n);
	virtual std::streamsize xsputn (const char* s, std::streamsize n);
	virtual std::streamsize showmanyc();

	virtual std::streampos seekpos (std::streampos pos,
									std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);

	virtual std::streampos seekoff (std::streamoff off, std::ios_base::seekdir way,
									std::ios_base::openmode which = std::ios_base::in | std::ios_base::out);

	void updateWritePointers(TByte *pDataStart, size_t iBufferLen);
	void updateReadPointers(TByte *pReaderCursor);
	void allocateSegment();

	void nextWriterSegment();

	Allocator* pAllocator;
	Info *pInfo;

	Segment* pReaderActive;
	Segment* pWriterActive;

	void dump(std::ostream& os);

	friend class IAS::Factory<StreamMemoryBuffer>;
};
/*************************************************************************/
}

#endif /* _IAS_StreamMemoryBuffer_H_ */
