/*
 * File: IAS-CommonLib/src/commonlib/config.h
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
#ifndef IAS_CONFIG_H_
#define IAS_CONFIG_H_


#define IAS_USE_PTHREADS 	    1
#define IAS_GNU_STACKTRACE 	    1

#define IAS_FEATURE_THREAD_SAFE 	1
#define IAS_FEATURE_STACKTRACE 	    1

#define IAS_SHOW_STACK_SIZE 16

#define IAS_STC_TID_TO_INT()   ((int)pthread_self())

#endif /* CONFIG_H_ */
