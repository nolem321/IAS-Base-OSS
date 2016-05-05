/*
 * File: IAS-CommonLib/src/commonlib/tools/Buffer.cpp
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
#include "Buffer.h"

#include <commonlib/logger/logger.h>
#include <commonlib/memory/memory.h>
#include <commonlib/exception/InternalException.h>

#include <string.h>

namespace IAS {

/*************************************************************************/
Buffer::Buffer(size_t iSize, Allocator *ma):pData(0),iSize(0),ma(ma){
	IAS_TRACER;
	reserve(iSize);
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Buffer, size: "<<(pData ? (void*)getBuffer<char>(): 0));
};
/*************************************************************************/
Buffer::~Buffer(){
	IAS_TRACER;
	reserve(0);
}
/*************************************************************************/
void Buffer::reserve(size_t iSize){

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Reserve from:"<<this->iSize<<" to "<<iSize<<", data is "<<pData);

	if(iSize == this->iSize)
		return;

	if(pData)
		ma->free(pData);

	if(iSize)
		pData=ma->allocate(iSize);

	this->iSize=iSize;
}
/*************************************************************************/
struct MemHolder {

	MemHolder(void* p, Allocator *ma) :
			p(p),ma(ma) {
	}

	~MemHolder() {
		if(p)
			ma->free(p);
	}

	operator void*(){
		return p;
	}

	void* pass() {
		void* tmp = p;
		p = 0;
		return tmp;
	}

	void* p;
	Allocator *ma;
};
/*************************************************************************/
void Buffer::resize(size_t iSize){

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Resizing from:"<<this->iSize<<" to "<<iSize);

	if(this->iSize == iSize)
		return;

	if(iSize){

		MemHolder ptrNewData(ma->allocate(iSize),ma);

		if(pData){
			memcpy(ptrNewData,pData,(this->iSize < iSize) ? this->iSize : iSize);
			ma->free(pData);
		}

		this->iSize=iSize;
		pData=ptrNewData.pass();

	}else{
		reserve(0);
	}

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"pData="<<pData);

}
/*************************************************************************/
size_t Buffer::getSize()const{
	return iSize;
}
/*************************************************************************/
template<>
void *Buffer::getBuffer<void>(){
	IAS_TRACER;
	if(iSize)
		return pData;
	IAS_THROW(InternalException("Buffer is empty."))
}
/*************************************************************************/

}

