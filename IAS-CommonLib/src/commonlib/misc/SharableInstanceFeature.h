/*
 * File: IAS-CommonLib/src/commonlib/misc/SharableInstanceFeature.h
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
#ifndef _IAS_SharableInstanceFeature_H_
#define _IAS_SharableInstanceFeature_H_

/*
 *
 */
#include "../logger/logger.h"
#include "../memory/MemoryAllocator.h"
#include <typeinfo>

namespace IAS {


class SharableInstanceManager {
public:

	virtual ~SharableInstanceManager(){};
	virtual bool lookup(const char* id, void **p)=0;
	virtual void addPointer(const char* id, void *p)=0;
};

typedef ::IAS::SharableInstanceManager* (*PtrFunSharableInstanceManager)();


template<class TT, PtrFunSharableInstanceManager FunSIM, PtrFunAllocator FunAllocator>
class SharableInstance {
public:

	static TT* GetInstance() {

		if(TheInstance == NULL){

			void *tmp;

			if((*FunSIM)()->lookup(typeid(TT).name(),&tmp)){
				TheInstance=(TT*)tmp;
			}else{
				tmp=(*FunAllocator)()->allocate(sizeof(TT));
				TheInstance=new(tmp)TT;
				(*FunSIM)()->addPointer(typeid(TT).name(),tmp);
			}
		}

		return TheInstance;
	}

protected:
	typedef TT* TheInstanceType;
private:

	static TheInstanceType TheInstance;
};

}

#endif /* INSTANCEFEATURE_H_ */
