/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/GetRandomString.cpp
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
#include "GetRandomString.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
GetRandomString::GetRandomString(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;

	if(lstParamaters.size())
		srand(TypeTools::StringToInt(*lstParamaters.begin()));
	else
		srand(time(0) + getpid() + (((long)pthread_self() >> 2) & 0xffff));
}
/*************************************************************************/
GetRandomString::~GetRandomString() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const char  GetRandomString::CRandomChars  []=  "1234567890abcdefghijklmnoprstquwvxyzABCDEFGHIJKLMNOPRSTQUWVXYZab";
/*************************************************************************/
void GetRandomString::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);


	int iLength = pParameters->getInteger("length");

	StringStream ssTmp;

	while(iLength){
		int iValue = rand();
		for(int iIdx = 0; iLength && iIdx<sizeof(int); iIdx++,iValue >>= 1,iLength--)
			ssTmp<<CRandomChars[iValue & 0x3f];
	}


	pParameters->setString(String(Model::Dec::ResultDeclarationNode::CStrResultVariable),ssTmp.str());

}
/*************************************************************************/
Statement* GetRandomString::Create(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetRandomString>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
