/*
 * File: IAS-CommonLib/src/commonlib/logger/StackTraceContainer.cpp
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
#include "StackTraceContainer.h"
#include <pthread.h>

#include "../threads/ThreadSpecific.h"
#include "StackTrace.h"

#include "../memory/ma/Factory.h"

namespace IAS {

static ThreadSpecificOwner<StandardFactory<StackTrace>,StackTrace> _TheStackTrace;
/*************************************************************************/
StackTrace *StackContainer::GetThreadStack(){
	return _TheStackTrace.GetOrCreate();
}
/*************************************************************************/


}
