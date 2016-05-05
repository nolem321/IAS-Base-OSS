/*
 * File: IAS-ServiceManagerLib/src/sm/worker/Iterator.h
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
#ifndef _IAS_SM_Worker_Iterator_H_
#define _IAS_SM_Worker_Iterator_H_

#include "sm/cfg/types.h"
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Cfg{
class Config;
}
namespace Worker {
class IWorker;

/*************************************************************************/
/** The Iterator class.
 *
 */
class Iterator {
public:

	virtual ~Iterator() throw();

	static Iterator* Create(const Cfg::Config *pConfig,
							IWorker* pWorker,
							const Cfg::ServiceIdxList& lstServiceIdx);

	void execute();

protected:
	Iterator() throw();
	void init(const Cfg::Config *pConfig, IWorker* pWorker);

	const Cfg::Config *pConfig;
	IWorker* pWorker;

	virtual void executeImpl()=0;

	void executeServiceAction(const ::org::invenireaude::sm::cfg::Service *pService);

};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_Iterator_H_ */
