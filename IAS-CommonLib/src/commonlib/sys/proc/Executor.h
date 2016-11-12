/*
 * File: IAS-CommonLib/src/commonlib/sys/proc/Executor.h
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
#ifndef _IAS_SYS_Proc_Executor_H_
#define _IAS_SYS_Proc_Executor_H_


#include "commonlib/types.h"
#include <list>

#include "Runnable.h"

namespace IAS {
namespace SYS {
namespace Proc {

/*************************************************************************/
/** The Executor class.
 *
 */
class Executor : public ::IAS::SYS::Proc::Runnable {
public:

	Executor(const String& strCommand);
	virtual ~Executor() throw();

	void appendArg(const String& strArg);
	virtual void run();

	void setApplyEnv(bool bApplyEnv);

protected:

	String strCommand;

	typedef StringList ArgsList;
	ArgsList           lstArgs;
	bool bApplyEnv;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SYS_Proc_Executor_H_ */
