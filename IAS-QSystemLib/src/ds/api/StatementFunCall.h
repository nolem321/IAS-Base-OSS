/*
 * File: IAS-QSystemLib/src/ds/api/StatementFunCall.h
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
#ifndef _IAS_DS_API_StatementFunCall_H_
#define _IAS_DS_API_StatementFunCall_H_

#include <commonlib/commonlib.h>

#include "StatementCall.h"

namespace IAS {
namespace DS {
namespace API {

/*************************************************************************/
/** The Consumer class.
 *
 */
class StatementFunCall :
		public virtual StatementCall {
public:

	virtual ~StatementFunCall() throw(){};

	typedef IAS_DFT_FACTORY<StatementFunCall>::PtrHolder PtrHolder;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_DS_API_StatementFunCall_H_ */
