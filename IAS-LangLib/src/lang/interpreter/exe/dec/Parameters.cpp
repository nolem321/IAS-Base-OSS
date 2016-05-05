/*
 * File: IAS-LangLib/src/lang/interpreter/exe/dec/Parameters.cpp
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
#include "Parameters.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "lang/model/dec/ResultDeclarationNode.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Dec {

/*************************************************************************/
Parameters::Parameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Parameters::~Parameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool Parameters::hasResult()const{
	IAS_TRACER;

	try{

		getType()->asComplexType()->getProperties().getProperty(Model::Dec::ResultDeclarationNode::CStrResultVariable);
		return true;

	}catch(ItemNotFoundException& e){
		return false;
	}
}
/*************************************************************************/
const DM::Property* Parameters::getResultProperty() const{
	IAS_TRACER;
	return getType()->asComplexType()->getProperties().getProperty(Model::Dec::ResultDeclarationNode::CStrResultVariable);
}
/*************************************************************************/
}
}
}
}
}
