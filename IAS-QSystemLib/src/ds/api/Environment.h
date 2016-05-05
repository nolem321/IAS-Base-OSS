/*
 * File: IAS-QSystemLib/src/ds/api/Environment.h
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
#ifndef _IAS_DS_API_Environment_H_
#define _IAS_DS_API_Environment_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/ds/Parameter.h>

namespace IAS {
namespace DS {
namespace API {

class Connection;
class Content;
class ContentManager;
class Message;

/*************************************************************************/
/** The Environment class.
 *
 */
class Environment {
public:

	virtual ~Environment() throw(){};


	virtual Connection* connect(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter)=0;

	static Environment* GetInstance();

	virtual void shutdown() = 0;

protected:

	//Environment(){};

	friend class Factory<Environment>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DS_API_Environment_H_ */
