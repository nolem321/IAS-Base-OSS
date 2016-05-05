/*
 * File: IAS-CommonLib/src/commonlib/caches/SimpleCacheSynchronized.h
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

#ifndef SimpleCacheSynchronized_H_
#define SimpleCacheSynchronized_H_

#include "../logger/logger.h"
#include "../memory/ma/PtrHolder.h"

#include <map>

#include "CacheBase.h"
#include "../threads/Mutex.h"

/*
 *
 */
namespace IAS {
namespace Cache {

/*************************************************************************/
/** The simple cache template with synchronization features.
 *
 */
template<class TR, class TK>
/** The class. */
 class SimpleCacheSynchronized : public SimpleCache<TR,TK> {


public:

	SimpleCacheSynchronized() throw(){ IAS_TRACER;	};
	virtual ~SimpleCacheSynchronized()throw(){ IAS_TRACER; };

	virtual TR* getResource(const TK& key){
		IAS_TRACER;

		Mutex::Locker locker(theLock);
		return  SimpleCache<TR,TK>::getResource(key);
	}


protected:

	Mutex theLock;

};

}
}

#endif /* SimpleCacheSynchronized_H_ */
