/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ReplaceRegExp.cpp
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
#include "ReplaceRegExp.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

#include <regex>


#ifdef __GNUC__
#define ias_regex_ns ::std
#else
#define ias_regex_ns ::std::tr1
#endif

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
ReplaceRegExp::ReplaceRegExp(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
ReplaceRegExp::~ReplaceRegExp() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ReplaceRegExp::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strArgument = pParameters->getString("strArgument");
	const String strPattern  = pParameters->getString("strPattern");
	const String strNewText  = pParameters->getString("strNewText");


	ias_regex_ns::regex   expression(strPattern);

	pParameters->setString(Model::Dec::ResultDeclarationNode::CStrResultVariable, ias_regex_ns::regex_replace(strArgument, expression, strNewText.c_str()));

}
/*************************************************************************/
Statement* ReplaceRegExp::Create(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ReplaceRegExp>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
