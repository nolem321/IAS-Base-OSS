/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/WrappedStatement.cpp
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
#include "WrappedStatement.h"

#include<qs/log/sps/LogLevel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

/*************************************************************************/
WrappedStatement::WrappedStatement(const String& strDataSource, const String& strSpecification):
									strSpecification(strSpecification),
									strDataSource(strDataSource){
	IAS_TRACER;
}

/*************************************************************************/
WrappedStatement::~WrappedStatement() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
}
}
