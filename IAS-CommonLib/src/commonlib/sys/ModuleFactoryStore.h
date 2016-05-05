/*
 * File: IAS-CommonLib/src/commonlib/sys/ModuleFactoryStore.h
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
#ifndef _IAS_SYS_ModuleFactoryStore_H_
#define _IAS_SYS_ModuleFactoryStore_H_

#include "commonlib/memory/memory.h"
#include "commonlib/logger/logger.h"
#include "commonlib/containers/HashMapStringPairToPointer.h"

#include "DynamicLibrary.h"
namespace IAS {
namespace SYS {

/*************************************************************************/
/** The ModuleStore class.
 *
 */

/*************************************************************************/
template <class T>
class Factory : public DynamicLibrary{

	public:

		virtual ~Factory()throw(){
			IAS_TRACER;
			IAS_LOG(LogLevel::INSTANCE.isInfo(),"deleted at: "<<(void*)this<<" for: "<<pVoidFactory);
		};

		Factory(const String& strLibrary,
				const String& strFactoryName):
		  			DynamicLibrary(strLibrary){

			pVoidFactory = getSymbol(strFactoryName);

			 IAS_LOG(LogLevel::INSTANCE.isInfo(),"factory at: "<<(void*)pVoidFactory);
		}

		T * create(){

			typedef T* (*FactoryPtr)();
			FactoryPtr pFactory=(FactoryPtr)pVoidFactory;

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"calling factory0 at: "<<(void*)pFactory);
			return (*pFactory)();
		}

		template<class P1>
		T * create(P1 p1){

			typedef T* (*FactoryPtr)(P1);
			FactoryPtr pFactory=(FactoryPtr)pVoidFactory;

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"calling factory1 at: "<<(void*)pFactory);
			return (*pFactory)(p1);
		}

		template<class P1, class P2>
		T * create(P1 p1, P2 p2){

			typedef T* (*FactoryPtr)(P1,P2);
			FactoryPtr pFactory=(FactoryPtr)pVoidFactory;

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"calling factory2 at: "<<(void*)pFactory);
			return (*pFactory)(p1,p2);
		}

		void* pVoidFactory;
};
/*************************************************************************/

template <class T>
class ModuleFactoryStore {
public:

	virtual ~ModuleFactoryStore()throw(){
		IAS_TRACER;
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"deleted at: "<<(void*)this);
	};

	typedef ::IAS::HashMapStringPairToPointer< Factory<T> >          ModulesMap;
	ModulesMap                                                        hmModules;


	Factory<T> *getFactory(const String& strLibrary, const String& strFactory){

		IAS_TRACER;
		typename ModulesMap::Key key(strLibrary,strFactory);

		if(hmModules.hasKey(key) == 0)
			loadModule(strLibrary,strFactory);

		return hmModules.at(key);
	}

protected:


	ModuleFactoryStore(){};

	void loadModule(const String& strLibrary,  const String& strFactory){

		IAS_TRACER;
		typename ModulesMap::Key key(strLibrary,strFactory);
		hmModules[key]=IAS_DFT_FACTORY< Factory<T> >::Create(strLibrary,strFactory);
	}

};
/*************************************************************************/
}
}

#endif /* _IAS_SYS_ModuleFactoryStore_H_ */
