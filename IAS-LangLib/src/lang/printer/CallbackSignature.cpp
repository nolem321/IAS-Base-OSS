/*
 * File: IAS-LangLib/src/lang/printer/CallbackSignature.cpp
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
#include "CallbackSignature.h"
#include<lang/log/LogLevel.h>

namespace IAS {
namespace Lang {
namespace Printer {

/*************************************************************************/
CallbackSignature::~CallbackSignature(){}
/*************************************************************************/
void CallbackSignature::printIndent(CallbackSignature::CallbackCtx *pCtx,
									    std::ostream& os){

	IAS_CHECK_IF_NULL(pCtx);

	for(int i=0;i<pCtx->iIndent; i++)
		os<<"  ";
}

/*************************************************************************/
}
}
}
