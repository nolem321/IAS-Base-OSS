/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/sys/fs/GetUsage.cpp
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
namespace FS {

/*************************************************************************/
GetUsage::GetUsage(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
GetUsage::~GetUsage() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetUsage::readSample(DM::DataObjectList& lstSamples, const DM::DataFactory* pDataFactory)const{

	String strMTAB;

	IAS_DFT_FACTORY<InputFile>::PtrHolder ptrFile(IAS_DFT_FACTORY<InputFile>::Create("/etc/mtab"));
	ptrFile->open();
	std::istream& is(ptrFile->getStreamRef());

	StringList lstFileSystems;

	String strLine;

	while(std::getline(is,strLine)){

		String::size_type iStart=strLine.find(' ');
		iStart=strLine.find('/',iStart+1);
		String::size_type iEnd=strLine.find(' ',iStart+1);

		lstFileSystems.push_back(strLine.substr(iStart,iEnd-iStart));
	}

	struct statvfs info;

	DateTime tsNow(true);

	for (StringList::const_iterator it=lstFileSystems.begin(); it != lstFileSystems.end(); ++it) {

		IAS_LOG(LogLevel::INSTANCE.isSystem(),"FS: ["<<*it<<"]");

		if(statvfs((*it).c_str(),&info) != 0)
			IAS_THROW(SystemException("statvfs: ")<<(*it));

		DM::DataObjectPtr dmSample(pDataFactory->getType(
				"http://www.invenireaude.org/monitor/sys/fs","UsageSample")->createDataObject());
		dmSample->setString("resource",*it);

		static const int CLogScale = 20;

		unsigned long iSize  = ((unsigned long)info.f_bsize*info.f_blocks)>>CLogScale;
		unsigned long iFree  = ((unsigned long)info.f_bsize*info.f_bfree)>>CLogScale;
		unsigned long iAvail = ((unsigned long)info.f_bsize*info.f_bavail)>>CLogScale;

		if(iSize == 0 || info.f_fsid == 0)
			continue;

		dmSample->setInteger("used",iSize-iAvail);
		dmSample->setInteger("total",iSize);

		lstSamples.add(dmSample);
	}

};
/*************************************************************************/
void GetUsage::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	DM::DataObjectList& lstSamples(pParameters->getList(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable)));

	try{

		readSample(lstSamples, pCtx->getDataFactory());

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
Extern::Statement* GetUsage::Create(const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetUsage>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
