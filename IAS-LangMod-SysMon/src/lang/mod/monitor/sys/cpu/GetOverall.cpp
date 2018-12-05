/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/sys/cpu/GetOverall.cpp
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
#include "GetOverall.h"


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
namespace CPU {

/*************************************************************************/
GetOverall::GetOverall(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy):
	iFraction(/*TODO sysconf(_SC_CLK_TCK)*/){
	IAS_TRACER;

	iFraction/=100;
}
/*************************************************************************/
GetOverall::~GetOverall() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetOverall::readSample(DM::DataObjectPtr& dmSample)const{
	IAS_TRACER;

	String strStats;
	StringList lstLines;
	InputFile::LoadString("/proc/stat",strStats);
	TypeTools::Tokenize(strStats,lstLines,'\n');

	//this method is designated const so we have to use some globals;

	static Mutex mutex;
	static struct OverallValues ovOld;

	Mutex::Locker locker(mutex);

	for (StringList::const_iterator itLines=lstLines.begin(); itLines != lstLines.end(); ++itLines) {

		StringStream ssLine(*itLines);

		String strProperty;
		ssLine>>strProperty;

		struct OverallValues ovNow;

		if(strProperty.compare("cpu"))
			continue;

		ssLine>>ovNow.iUser;
		ssLine>>ovNow.iNice;
		ssLine>>ovNow.iSystem;
		ssLine>>ovNow.iIdle;
		ssLine>>ovNow.iWait;


		IAS_LOG(true,ovNow.iUser);
		struct OverallValues ovTmp(ovNow);
		ovNow-=ovOld;
		ovOld=ovTmp;

		unsigned long iSum = ovNow.iUser + ovNow.iNice + ovNow.iSystem + ovNow.iIdle + ovNow.iWait;

		dmSample->setInteger("user",100*ovNow.iUser/iSum);

		dmSample->setInteger("nice",100*ovNow.iNice/iSum);
		dmSample->setInteger("system",100*ovNow.iSystem/iSum);
		dmSample->setInteger("idle",100*ovNow.iIdle/iSum);
		dmSample->setInteger("wait",100*ovNow.iWait/iSum);
	}

}
/*************************************************************************/
void GetOverall::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	DM::DataObjectPtr dmSample(pCtx->getDataFactory()->getType(
			"http://www.invenireaude.org/monitor/sys/cpu","OverallSample")->createDataObject());

	try{

		readSample(dmSample);
		pParameters->setDataObject(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),dmSample);


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
GetOverall::OverallValues::OverallValues():
	iUser(0),
	iNice(0),
	iSystem(0),
	iWait(0),
	iIdle(0){
	IAS_TRACER;

}
/*************************************************************************/
GetOverall::OverallValues::OverallValues(struct OverallValues& other){
	IAS_TRACER;
	(*this)=other;
}
/*************************************************************************/
GetOverall::OverallValues& GetOverall::OverallValues::operator -=(struct OverallValues& other){
	IAS_TRACER;

	this->iUser   -= other.iUser;
	this->iNice   -= other.iNice;
	this->iSystem -= other.iSystem;
	this->iWait   -= other.iWait;
	this->iIdle   -= other.iIdle;

	return *this;
}
/*************************************************************************/
GetOverall::OverallValues& GetOverall::OverallValues::operator =(struct OverallValues& other){
	IAS_TRACER;

	this->iUser   = other.iUser;
	this->iNice   = other.iNice;
	this->iSystem = other.iSystem;
	this->iWait   = other.iWait;
	this->iIdle   = other.iIdle;

	return *this;
}
/*************************************************************************/
Extern::Statement* GetOverall::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetOverall>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
