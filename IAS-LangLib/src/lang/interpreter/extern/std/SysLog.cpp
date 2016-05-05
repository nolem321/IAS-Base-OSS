/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/SysLog.cpp
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
#include "SysLog.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>
 #include <syslog.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
/*************************************************************************/
SysLog::SysLog(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
SysLog::~SysLog() throw(){
	IAS_TRACER;
}
/*************************************************************************/
struct _PriorityMapper {

	typedef HashMapWithStringKey<int> Map;

	Map hmValues;

	_PriorityMapper(){
		 hmValues["LOG_EMERG"]=LOG_EMERG;
		 hmValues["LOG_ALERT"]=LOG_ALERT;
		 hmValues["LOG_CRIT"]=LOG_CRIT;
		 hmValues["LOG_ERR"]=LOG_ERR;
		 hmValues["LOG_WARNING"]=LOG_WARNING;
		 hmValues["LOG_NOTICE"]=LOG_NOTICE;
		 hmValues["LOG_INFO"]=LOG_INFO;
		 hmValues["LOG_DEBUG"]=LOG_DEBUG;
	}

	int operator[](const String& strValue)const{
		Map::const_iterator it=hmValues.find(strValue);

		if(it == hmValues.end())
			IAS_THROW(ItemNotFoundException("SysLog Priority: " + strValue));

		return it->second;
	}
};
/*************************************************************************/
static _PriorityMapper _priorityMapper;
/*************************************************************************/
void SysLog::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strPriority = pParameters->getString("priority");
	const String strMessage  = pParameters->getString("message");

	::syslog(_priorityMapper[strPriority], strMessage.c_str());

	IAS_LOG(LogLevel::INSTANCE.isInfo()||
			(LogLevel::INSTANCE.isError() && _priorityMapper[strPriority] <= LOG_ERR),"LOG:"<<strMessage);

}
/*************************************************************************/
Statement* SysLog::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<SysLog>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}
}
