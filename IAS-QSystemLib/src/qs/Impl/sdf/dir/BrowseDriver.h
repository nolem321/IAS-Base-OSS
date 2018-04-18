/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/dir/BrowseDriver.h
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
#ifndef _IAS_QS_SDF_Dir_BrowseDriver_H_
#define _IAS_QS_SDF_Dir_BrowseDriver_H_

#include <commonlib/sys/fs/DirectoryReader.h>

#include "InputBase.h"
#include <qs/api.h>

namespace IAS {
namespace QS {
namespace SDF {
namespace Dir {

/*************************************************************************/
/** The BrowseDriver class.
 *
 */
class BrowseDriver : public InputBase {
public:

	virtual ~BrowseDriver() throw();
	virtual Message* receive(int iTimeWait, API::Attributes* pSelector);

protected:

	BrowseDriver(const API::Destination& destination);
	friend class Factory<BrowseDriver>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_SDF_Dir_BrowseDriver_H_ */
