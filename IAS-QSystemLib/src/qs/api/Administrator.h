/*
 * File: IAS-QSystemLib/src/qs/api/Administrator.h
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
#ifndef _IAS_QS_API_Administrator_H_
#define _IAS_QS_API_Administrator_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/stats/SystemStats.h>

namespace IAS {
namespace QS {
namespace API {

/*************************************************************************/
/** The Administrator class.
 *
 */
class Administrator {
public:

	virtual ~Administrator() throw(){};

	virtual ::org::invenireaude::qsystem::stats::Ext::SystemStatsPtr getStats(bool bReset)=0;

	typedef IAS_DFT_FACTORY<Administrator>::PtrHolder PtrHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Administrator_H_ */

