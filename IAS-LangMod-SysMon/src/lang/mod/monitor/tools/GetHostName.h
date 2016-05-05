/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/tools/GetHostName.h
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
#ifndef _IAS_Lang_MOD_Monitor_Tools_GetHostName_H_
#define _IAS_Lang_MOD_Monitor_Tools_GetHostName_H_

#include <commonlib/commonlib.h>

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>

namespace IAS  {
namespace Lang {
namespace MOD  {
namespace Monitor{
namespace Tools  {

/*************************************************************************/
/** The GetHostName class.
 *
 */
class GetHostName : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~GetHostName() throw();


	/** Creates an instance. */
	static Statement* Create(const StringList& lstParamaters);

protected:
	GetHostName(const StringList& lstParamaters);

	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	friend class Factory<GetHostName>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_MOD_Monitor_Tools_GetHostName_H_ */
