/*
 * File: IAS-QSystemLib/src/ds/Impl/SQLTricks.h
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
#ifndef _IAS_DS_Impl_SQLTricks_H_
#define _IAS_DS_Impl_SQLTricks_H_

#include <ds/api/SQLTricks.h>

namespace IAS {
namespace DS {
namespace Impl {

/*************************************************************************/
/** The SQLTricks class.
 *
 */
class SQLTricks :
		public virtual API::SQLTricks{

public:

	virtual ~SQLTricks() throw();
	virtual bool skipFunctionOutputParameters()const;

  virtual String makeProcedureCall(const String& strSQLText)const;
  virtual String makeFunctionCall(const String& strSQLText)const;

protected:

	SQLTricks();

	friend class ::IAS::Factory<SQLTricks>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DS_Impl_SQLTricks_H_ */
