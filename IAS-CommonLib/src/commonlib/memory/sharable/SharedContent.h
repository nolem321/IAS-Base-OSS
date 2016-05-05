/*
 * File: IAS-CommonLib/src/commonlib/memory/sharable/SharedContent.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 * 
 */

#ifndef _IAS_SharedContent_H_
#define _IAS_SharedContent_H_

#include "../memory.h"
#include "SharedMemoryFile.h"

namespace IAS{

//============================================================================

template<class T>
class SharedContent  : public Factory<T>{

public:

	typedef SharedMemoryFile::Descriptor Descriptor;

	T* get(){ return pContent; };

	virtual ~SharedContent(){

		if(ptrSHMFile->getDescriptor().getCloseMode() ==
			SharedMemoryFile::Descriptor::CM_DESTROY)

		Factory<T>::Free(pContent);
	}

	SharedContent(const Descriptor& refDescriptor) {
		init(refDescriptor);
		if(!ptrSHMFile->alreadyExisted())
			Factory<T>::Initialize(pContent);
	}

	template<typename P1>
	SharedContent(const Descriptor& refDescriptor, P1 a){
		init(refDescriptor);
		if(!ptrSHMFile->alreadyExisted())
			Factory<T>::Initialize(pContent,a);
	}

	template<typename P1, typename P2>
	SharedContent(const Descriptor& refDescriptor, P1 a, P2 b){
		init(refDescriptor);
		if(!ptrSHMFile->alreadyExisted())
			Factory<T>::Initialize(pContent,a,b);
	}

	template<typename P1, typename P2, typename P3>
	SharedContent(const Descriptor& refDescriptor, P1 a, P2 b, P3 c){
		init(refDescriptor);
		if(!ptrSHMFile->alreadyExisted())
			Factory<T>::Initialize(pContent,a,b,c);
	}

protected:

	IAS_DFT_FACTORY<SharedMemoryFile>::PtrHolder ptrSHMFile;
	T *pContent;

	void init(const Descriptor& refDescriptor){

		IAS_TRACER;

		Descriptor aDescriptor(refDescriptor);
		aDescriptor.setSize(sizeof(T));
		ptrSHMFile = IAS_DFT_FACTORY<SharedMemoryFile>::Create(aDescriptor);
		pContent = (T*)(ptrSHMFile->getAddress());


	}
};

//============================================================================

};

#endif /*_IAS_Factory_H_*/
