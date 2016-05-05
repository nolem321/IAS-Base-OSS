/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/ContentManager.h
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
#ifndef _IAS_QS_System_ContentManager_H_
#define _IAS_QS_System_ContentManager_H_

#include <qs/api/ContentManager.h>
#include "Content.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
class ContentStorage;
}


/*************************************************************************/
/** The ContentManager class.
 *
 */
class ContentManager : public virtual API::ContentManager {
public:

	virtual ~ContentManager() throw();

	virtual API::Content* allocate();

	Content* allocateImpl();

protected:
	ContentManager(QS::SHM::Shared::ContentStorage *pContentStorage);

	QS::SHM::Shared::ContentStorage *pContentStorage;

	friend class Factory<ContentManager>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_ContentManager_H_ */
