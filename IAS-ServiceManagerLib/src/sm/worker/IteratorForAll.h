/*
 * File: IAS-ServiceManagerLib/src/sm/worker/IteratorForAll.h
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
#ifndef _IAS_SM_Worker_IteratorForAll_H_
#define _IAS_SM_Worker_IteratorForAll_H_

#include "Iterator.h"

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
/** The IteratorForAll class.
 *
 */
class IteratorForAll : public Iterator {
public:

	virtual ~IteratorForAll() throw();

protected:
	IteratorForAll(const Cfg::Config *pConfig, IWorker* pWorker);

	virtual void executeImpl();

	friend class ::IAS::Factory<IteratorForAll>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_IteratorForAll_H_ */
