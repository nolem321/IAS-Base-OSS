/*
 * File: IAS-QSystemMod-SPS/src/qs/lang/sps/SetVersion.cpp
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
#include "SetVersion.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace SPS {

/*************************************************************************/
SetVersion::SetVersion(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
SetVersion::~SetVersion() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SetVersion::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String& strVersion = pParameters->getString("version");

	pProcessCacheEntry->getProcessInstance()->setVer(strVersion);

}
/*************************************************************************/
Extern::Statement* SetVersion::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<SetVersion>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}

