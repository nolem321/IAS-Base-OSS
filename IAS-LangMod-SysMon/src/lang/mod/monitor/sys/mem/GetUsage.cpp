/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/sys/mem/GetUsage.cpp
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
#include "GetUsage.h"

#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <sys/statvfs.h>

using namespace ::IAS::Lang::Interpreter;

namespace IAS {
namespace Lang {
namespace MOD {
namespace Monitor {
namespace SYS {
namespace MEM {

/*************************************************************************/
GetUsage::GetUsage(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
GetUsage::~GetUsage() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetUsage::readSample(DM::DataObjectList& lstSamples, const DM::DataFactory* pDataFactory)const{
	IAS_TRACER;

	String strStats;
	StringList lstLines;
	InputFile::LoadString("/proc/meminfo",strStats);
	TypeTools::Tokenize(strStats,lstLines,'\n');

	StringList::iterator itLines=lstLines.begin();

	DM::DataObjectPtr dmSample(pDataFactory->getType(
				"http://www.invenireaude.org/monitor/sys/mem","UsageSample")->createDataObject());
	dmSample->setString("resource","ALL");

	while(itLines != lstLines.end() && (*itLines).find(':') != String::npos) {

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"line: "<<*itLines);

		StringStream ssLine(*itLines);

		String strProperty;
		long iValue;
		ssLine>>strProperty;
		ssLine>>iValue;

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"property: "<<strProperty);

		if(!strProperty.compare("MemTotal:")){
			dmSample->setInteger("memTotal",iValue);
		}else if(!strProperty.compare("MemFree:")){
			dmSample->setInteger("memFree",iValue);
		}else if(!strProperty.compare("SwapTotal:")){
			dmSample->setInteger("swapTotal",iValue);
		}else if(!strProperty.compare("SwapFree:")){
			dmSample->setInteger("swapFree",iValue);
		}else if(!strProperty.compare("Cached:")){
			dmSample->setInteger("cached",iValue);
		}else if(!strProperty.compare("Buffers:")){
			dmSample->setInteger("buffers",iValue);
		}

		++itLines;
	}

	lstSamples.add(dmSample);
}
/*************************************************************************/
void GetUsage::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);


	DM::DataObjectList& lstSamples(pParameters->getList(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable)));

	try{

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Reading samples.");

		readSample(lstSamples,pCtx->getDataFactory());

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Got: "<<lstSamples.size()<<" samples.");

	}catch(Exception& e){

		IAS_LOG(LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		::org::invenireaude::qsystem::workers::Ext::ExceptionPtr dmException=
				::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createException();

		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));

	}

}
/*************************************************************************/
Extern::Statement* GetUsage::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetUsage>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}
}
}
