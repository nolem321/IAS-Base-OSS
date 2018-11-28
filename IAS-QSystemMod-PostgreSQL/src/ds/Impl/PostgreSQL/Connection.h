/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Connection.h
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
#ifndef _IAS_DS_PostgreSQL_Connection_H_
#define _IAS_DS_PostgreSQL_Connection_H_

#include <commonlib/commonlib.h>
#include <ds/api/Connection.h>
#include <ds/Impl/Connection.h>



#include <org/invenireaude/qsystem/workers/ds/Parameter.h>


namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

class System;
class SQLTricks;

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection : public virtual Impl::Connection {
public:

	virtual ~Connection() throw();

	virtual API::Session* createSession(API::Session::TransactionMode iMode);

	PostgreSQL::System *getSystem();

	inline String getName()const {return dmParameter->getName();}

	const ::org::invenireaude::qsystem::workers::ds::Parameter* getParameter()const{ return dmParameter; }

protected:
	Connection(PostgreSQL::System* pSystem,
      const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);

	friend class Factory<Connection>;

	PostgreSQL::System *pSystem;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DS_PostgreSQL_Connection_H_ */
