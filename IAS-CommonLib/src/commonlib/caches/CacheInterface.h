/*
 * File: IAS-CommonLib/src/commonlib/caches/CacheInterface.h
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

#ifndef CACHEINTERFACE_H_
#define CACHEINTERFACE_H_

#include "../logger/logger.h"
#include "../memory/ma/PtrHolder.h"

#include <map>

/*************************************************************************/
/** The cache interface.
 *
 */
namespace IAS {
namespace Cache {

template<class TR, class TK>
/** The class. */
 class CacheInterface {
public:

	virtual ~CacheInterface(){};
	virtual TR* getResource(const TK& key) = 0;

};

}
}

#endif /* SIMPLECACHE_H_ */
