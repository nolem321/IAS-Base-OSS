/*
 * File: IAS-CommonLib/src/commonlib/memory/memory.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#ifndef IASMEMORY_H_
#define IASMEMORY_H_

#include "mm/MemoryManager.h"
#include "../exception/MemoryException.h"
#include "../exception/InternalException.h"

#include "errno.h"

#define IAS_CHECK_IF_NULL(p)       \
{                                                                       \
        if(p == NULL){                                                  \
        	IAS_THROW(IAS::InternalException("null pointer!"))          \
        }                                                               \
}

//TODO (M) Check entries if know pointer and test
#define IAS_CHECK_IF_VALID(p)       \
{                                                                       \
        if(p == NULL){                                                  \
        	IAS_THROW(IAS::InternalException("null pointer!"))          \
        }                                                               \
}

#define IAS_DFT_FACTORY ::IAS::MemoryManagerFactory

#endif /*IASMEMORY_H_*/
