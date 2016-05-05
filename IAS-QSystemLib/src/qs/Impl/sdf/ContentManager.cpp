/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/ContentManager.cpp
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
#include "ContentManager.h"
#include<qs/log/LogLevel.h>
#include "Content.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace SDF {

/*************************************************************************/
ContentManager::ContentManager(){
	IAS_TRACER;
}
/*************************************************************************/
ContentManager::~ContentManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Content* ContentManager::allocate(){
	IAS_TRACER;
	return allocateImpl();
}
/*************************************************************************/
Content* ContentManager::allocateImpl(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Content>::Create();
}
/*************************************************************************/
}
}
}
