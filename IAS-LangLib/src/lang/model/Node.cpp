/*
 * File: IAS-LangLib/src/lang/model/Node.cpp
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
#include "Node.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Model {

/*************************************************************************/
Node::Node(){
	IAS_TRACER;
}
/*************************************************************************/
Node::~Node() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Node::setSourceLocation(const Tools::Parser::SourceLocation& sourceLocation){
	IAS_TRACER;
	this->sourceLocation=sourceLocation;
}
/*************************************************************************/
const Tools::Parser::SourceLocation& Node::getSourceLocation()const{
	IAS_TRACER;
	return sourceLocation;
}
/*************************************************************************/
}
}
}
