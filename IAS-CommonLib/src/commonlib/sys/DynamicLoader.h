/*
 * File: IAS-CommonLib/src/commonlib/sys/DynamicLoader.h
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
#ifndef _IAS_SYS_DYNAMICLOADER_H_
#define _IAS_SYS_DYNAMICLOADER_H_

#include "../memory/memory.h"
#include "../logger/logger.h"
#include "../misc/InstanceFeature.h"

namespace IAS {
namespace SYS {

/*************************************************************************/
/** The class. */
 class DynamicLoader : public InstanceFeature<DynamicLoader>{
public:

	DynamicLoader();
	virtual ~DynamicLoader() throw();

protected:


};


/*************************************************************************/
}
}

#endif /* _IAS_SYS_DYNAMICLOADER_H_ */
