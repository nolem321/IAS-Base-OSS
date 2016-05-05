/*
 * File: IAS-CommonLib/src/commonlib/net/BlockIOBuffer.h
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
#ifndef _IAS_BlockIOBuffer_H_
#define _IAS_BlockIOBuffer_H_

#include <streambuf>
#include <cstddef>

#include <commonlib/memory/memory.h>
#include <commonlib/tools/Buffer.h>

namespace IAS {
namespace Net {
class MemoryAllocator;
class IBlockIO;
/*************************************************************************/
/** The BlockIOBuffer class.
 *
 */
class BlockIOBuffer : public std::streambuf {
public:

	virtual ~BlockIOBuffer()throw();

protected:

	static const int CUnused = -9999;
	BlockIOBuffer(IBlockIO* pBlockIO, size_t iBufferSize=4096);

	virtual int_type overflow(int_type c);
	virtual int sync();
	virtual int_type underflow();

	virtual std::streamsize xsgetn (char* s, std::streamsize n);
	virtual std::streamsize xsputn (const char* s, std::streamsize n);
	virtual std::streamsize showmanyc();

	IBlockIO* pBlockIO;

	void flush();
	void fetch();

	IAS_DFT_FACTORY<Buffer>::PtrHolder ptrWriterBuffer;
	IAS_DFT_FACTORY<Buffer>::PtrHolder ptrReaderBuffer;

	bool bEOF;

	static const size_t CNumGuards = 1;
	static const size_t CNumUnGet  = 1;

	friend class IAS::Factory<BlockIOBuffer>;
};
/*************************************************************************/
}
}

#endif /* _IAS_BlockIOBuffer_H_ */
