/*
 * File: IAS-QSystemLib/src/qs/lang/tools/ExecuteSystemCmd.cpp
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
#include "ExecuteSystemCmd.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <lang/model/dec/ResultDeclarationNode.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {

/*************************************************************************/
ExecuteSystemCmd::ExecuteSystemCmd(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

}
/*************************************************************************/
ExecuteSystemCmd::~ExecuteSystemCmd() throw(){
	IAS_TRACER;
}
/*************************************************************************/
struct ArgsArray{
	ArgsArray(unsigned int iNumEntries):argv(0){
		argv = (const char**)malloc((1+iNumEntries)*sizeof(const char*));
	}

	~ArgsArray(){
		if(argv)
			free(argv);
	}

	const char* *argv;
};
/*************************************************************************/
int ExecuteSystemCmd::execute(const String& strCommand, const StringList& lstArgs)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Will execute: "<<strCommand);

	ArgsArray a(1 + lstArgs.size());

	a.argv[0]=strCommand.c_str();

	int iIdx = 1;

	for(StringList::const_iterator it = lstArgs.begin();
		it != lstArgs.end();
	    it++,iIdx++){
		a.argv[iIdx] = (*it).c_str();
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"argv["<<iIdx<<"]="<<(*it));
	}

	a.argv[iIdx]=NULL;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Fork + execve: "<<strCommand);

	int iPid=::fork();

	switch(iPid){
		case -1 :
			IAS_THROW(SystemException("fork()"));
			break;

		case 0 :
			::execvp(a.argv[0],(char* const*)a.argv);

		default:
			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Child PID:"<<iPid);

			int iStatus;

			if(::waitpid(iPid,&iStatus,0) == -1)
				IAS_THROW(SystemException("wait()"));

			if(!WIFEXITED(iStatus))
				IAS_THROW(BadUsageException(strCommand));

			return WEXITSTATUS(iStatus);
	}

}
/*************************************************************************/
void ExecuteSystemCmd::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* dmParameters = pCtx->getBlockVariables(0);

	const DM::ComplexType* pType = dmParameters->getType()->asComplexType();
	const DM::PropertyList& lstProperties(pType->getProperties());

	String strCommand;
	StringList lstArgs;


	for(int iIdx=0; iIdx < lstProperties.getSize(); iIdx++){
		const DM::Property *pProperty = lstProperties[iIdx];
		if(iIdx == 0)
			strCommand=dmParameters->getString(pProperty);
		else if(pProperty->getName().compare(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable) != 0)
			lstArgs.push_back(dmParameters->getString(pProperty));
	}

	try{

		dmParameters->setInteger(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
									execute(strCommand,lstArgs));


	}catch(Exception& e){

		//TODO (H) use exceptions from the tools namespace.

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}


}
/*************************************************************************/
Extern::Statement* ExecuteSystemCmd::Create(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ExecuteSystemCmd>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

