/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Statement.h
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
#ifndef _IAS_DS_Impl_PostgreSQL_Statement_H_
#define _IAS_DS_Impl_PostgreSQL_Statement_H_

#include <commonlib/commonlib.h>
#include <ds/api/Statement.h>

#include "libpq-fe.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {
class Session;
/*************************************************************************/
/** The Statement class.
 *
 */
class Statement :
		public virtual DS::API::Statement {
public:

	virtual ~Statement() throw();

	virtual void setSQLText(const String& strSQLText);

	virtual void prepare();

	inline const String& getSQLText()const{ return strSQLText; }

	Session* getSession()const{return pSession;}

	PGresult *getPGResult(){ return rh; };

protected:
	Statement(Session* pSession);

	String strSQLText;
	Session* pSession;

	class PGResultHolder {
	public:
		PGResultHolder(PGresult *res = 0);
		~PGResultHolder();

		PGResultHolder& operator = (PGresult * res);

		operator PGresult *();

	protected:
		PGresult *res;
	};

	PGResultHolder rh;

	String strPQName;

	friend class Factory<Statement>;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_PostgreSQL_Statement_H_ */
