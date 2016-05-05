/*
 * File: IAS-ServiceManagerLib/src/sm/worker/IteratorForSelected.h
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
#ifndef _IAS_SM_Worker_IteratorForSelected_H_
#define _IAS_SM_Worker_IteratorForSelected_H_

#include "Iterator.h"

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
/** The IteratorForSelected class.
 *
 */
class IteratorForSelected : public Iterator {
public:

	virtual ~IteratorForSelected() throw();

protected:
	IteratorForSelected(const Cfg::ServiceIdxList& lstServiceIdx,const Cfg::Config *pConfig, IWorker* pWorker);

	virtual void executeImpl();

	Cfg::ServiceIdxList lstServiceIdx;

	friend class ::IAS::Factory<IteratorForSelected>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_IteratorForSelected_H_ */
