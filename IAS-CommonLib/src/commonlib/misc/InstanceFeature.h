/*
 * File: IAS-CommonLib/src/commonlib/misc/InstanceFeature.h
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
#ifndef _IAS_InstanceFeature_H_
#define _IAS_InstanceFeature_H_

/*
 *
 */
#include "../logger/logger.h"
#include "../memory/ma/Factory.h"
#include "../threads/Mutex.h"

namespace IAS {

template<class TT>
class InstanceFeature {
public:

	//TODO (L?) throw()
	virtual ~InstanceFeature(){};

	static TT* GetInstance() {
		IAS_TRACER;
		//TODO (L) Analyze Mutex::Locker locker(TheMutex) - is it up to the user to initialize safely.
		if(TheInstance.isNull())
			TheInstance = ::IAS::StandardFactory< TT >::Create();
		return TheInstance.getPointer();
	}

	/*
	 * For debug purposes only.
	 */

	static void Delete() { TheInstance = 0; }


protected:

	typedef typename ::IAS::StandardFactory< TT >::PtrHolder TheInstanceType;

	static TheInstanceType TheInstance;
	//static Mutex TheMutex;
};

template<class TT>
typename InstanceFeature<TT>::TheInstanceType InstanceFeature<TT>::TheInstance(0);

//template<class TT>
//Mutex InstanceFeature<TT>::TheMutex(false);


template<class F , class T>
class InstanceFeatureWithFactory {
public:

	virtual ~InstanceFeatureWithFactory(){};

	static T* GetInstance() {
		IAS_TRACER;
		if(TheInstance.isNull())
			TheInstance = F::Create();
		return TheInstance.getPointer();
	}

	/*
	 * For debug purposes only.
	 */

	static void Delete() { F::Free(TheInstance); }


protected:

	typedef typename F::PtrHolder TheInstanceType;

	static TheInstanceType TheInstance;
};

template<class F, class T>
typename InstanceFeatureWithFactory<F,T>::TheInstanceType InstanceFeatureWithFactory<F,T>::TheInstance(0);

}

#endif /* INSTANCEFEATURE_H_ */
