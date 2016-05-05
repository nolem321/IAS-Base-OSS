/*
 * File: IAS-QSystemLib/src/qs/net/StateMachine.h
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
#ifndef _StateMachine_H_
#define _StateMachine_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Net {


/*************************************************************************/
/** The StateMachine class - old stuff move somewhere else - http server ?
 *
 */

class StateMachine {
public:

protected:

	class Context {
	public:
		virtual void doSomeWork()=0;
		virtual ~Context() throw(){};
	};


public:

	class ContextWork{
	public:

		ContextWork(StateMachine *pStateMachine):
			pStateMachine(pStateMachine){
			pContext=pStateMachine->pickAvailableContext();
		}

		void work(){
			pContext->doSomeWork();
		}

		~ContextWork(){
			pStateMachine->returnContext(pContext);
		}

	protected:

		Context      *pContext;
		StateMachine *pStateMachine;
	};

protected:

	virtual Context* pickAvailableContext()=0;
	virtual void     returnContext(Context* pContext);

	virtual ~StateMachine() throw(){};
};

/*************************************************************************/

}
}
}
#endif /* _StateMachine_H_ */
