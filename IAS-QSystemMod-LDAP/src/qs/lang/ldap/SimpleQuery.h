/*
 * File: IAS-QSystemMod-SysMon/src/qs/lang/ldap/SimpleQuery.h
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
#ifndef _IAS_QS_Lang_LDAP_SimpleQuery_H_
#define _IAS_QS_Lang_LDAP_SimpleQuery_H_

#include <commonlib/commonlib.h>

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>

namespace IAS  {
namespace Tools {
namespace LDAP {
class Connector;
}
}
namespace QS  {
namespace Lang {
namespace LDAP  {

/*************************************************************************/
/** The SimpleQuery class.
 *
 */
class SimpleQuery : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~SimpleQuery() throw();


	/** Creates an instance. */
	static Statement* Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

protected:
	SimpleQuery(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	String strConnection;
	friend class Factory<SimpleQuery>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Lang_LDAP_SimpleQuery_H_ */
