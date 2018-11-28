/*
 * File: IAS-QSystemLib/src/ds/Impl/System.h
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
#ifndef _IAS_DS_Impl_System_H_
#define _IAS_DS_Impl_System_H_

#include <org/invenireaude/qsystem/workers/ds/Parameter.h>


namespace IAS {

namespace QS {
namespace Fmt {
class FmtFactory;
}
}

namespace DS {

namespace API{
class Connection;
class SQLTricks;
}

namespace Impl {
class SQLTricks;

/*************************************************************************/
/** The System class.
 *
 */
class System {
public:
	virtual ~System() throw();
	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter)=0;

	QS::Fmt::FmtFactory *getFmtFactory()const;
  const API::SQLTricks* getSQLTricks()const;

protected:
  System(Impl::SQLTricks* pSQLTricks = NULL);

  IAS_DFT_FACTORY<SQLTricks>::PtrHolder ptrSQLTricks;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DS_Impl_System_H_ */
