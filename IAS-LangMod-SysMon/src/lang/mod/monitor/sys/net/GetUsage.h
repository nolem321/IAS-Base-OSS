/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/sys/net/GetUsage.h
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
#ifndef _IAS_Lang_MOD_Monitor_SYS_NET_GetUsage_H_
#define _IAS_Lang_MOD_Monitor_SYS_NET_GetUsage_H_

#include <commonlib/commonlib.h>

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>

namespace IAS {
namespace Lang {
namespace MOD {
namespace Monitor {
namespace SYS {
namespace NET {

/*************************************************************************/
/** The GetUsage class.
 *
 */
class GetUsage : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~GetUsage() throw();


	/** Creates an instance. */
	static Statement* Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

protected:
	GetUsage(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy);

	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	struct UsageValues{

		unsigned long	iTxBytes;
		unsigned long	iTxPackets;
		unsigned long	iTxErrors;
		unsigned long	iTxDropped;

		unsigned long	iRxBytes;
		unsigned long	iRxPackets;
		unsigned long	iRxErrors;
		unsigned long	iRxDropped;


		UsageValues();
		UsageValues(const struct UsageValues& other);

		UsageValues& operator -=(const struct UsageValues& other);
		UsageValues& operator =(const struct UsageValues& other);

	};

	int iFraction;

	void readSample(DM::DataObjectList& lstSamples, const DM::DataFactory* dmDataFactory)const;

	friend class Factory<GetUsage>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_Lang_MOD_Monitor_SYS_NET_GetUsage_H_ */
