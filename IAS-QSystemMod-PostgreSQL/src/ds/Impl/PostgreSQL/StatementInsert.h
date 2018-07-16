/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/StatementInsert.h
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
#ifndef _IAS_DS_Impl_PostgreSQL_StatementInsert_H_
#define _IAS_DS_Impl_PostgreSQL_StatementInsert_H_

#include <commonlib/commonlib.h>

#include <ds/api/StatementInsert.h>

#include "Statement.h"
#include "Input.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
/** The StatementInsert class.
 *
 */
class StatementInsert :
		public virtual Statement,
		public virtual API::StatementInsert,
		public virtual Input{
public:

	virtual ~StatementInsert() throw();

	//virtual void prepare();
	virtual void execute();

protected:
	StatementInsert(Session* pSession);

	friend class Factory<StatementInsert>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_PostgreSQL_StatementInsert_H_ */
