/*
 * File: IAS-LangLib/src/lang/interpreter/proc/exception/ProcessorLinkedException.cpp
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
#include "ProcessorLinkedException.h"

#include<lang/log/LogLevel.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
/*************************************************************************/
ProcessorLinkedException::ProcessorLinkedException(::IAS::Exception& e,
		 const Tools::Parser::SourceLocation& sourceLocation,
		 const Model::Node *pNode):
		ProcessorException(e.toString()),
		sourceLocation(sourceLocation),
		pNode(pNode){
	IAS_TRACER;
}
/*************************************************************************/
ProcessorLinkedException::~ProcessorLinkedException() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const char* ProcessorLinkedException::getName(){
	IAS_TRACER;
	return "ProcessorLinkedException";
}
/*************************************************************************/
}
}
}
}
