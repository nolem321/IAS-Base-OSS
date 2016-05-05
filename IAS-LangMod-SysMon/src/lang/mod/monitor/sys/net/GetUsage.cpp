/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/sys/net/GetUsage.cpp
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
namespace NET {

/*************************************************************************/
GetUsage::GetUsage(const StringList& lstParamaters):
	iFraction(/*TODO sysconf(_SC_CLK_TCK)*/1000){
	IAS_TRACER;

	iFraction/=100;
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
	InputFile::LoadString("/proc/net/dev",strStats);
	TypeTools::Tokenize(strStats,lstLines,'\n');

	IAS_LOG(LogLevel::INSTANCE.isInfo(),strStats);

	//this method is designated const so we have to use some globals;

	static Mutex mutex;
	static std::map<String,struct UsageValues> hmOld;

	Mutex::Locker locker(mutex);

	StringList::iterator itLines=lstLines.begin();
	itLines++;
	itLines++;

	while(itLines != lstLines.end() && (*itLines).find(':') != String::npos) {

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"line: "<<*itLines);

		(*itLines)[(*itLines).find(':')]=' ';

		StringStream ssLine(*itLines);

		DM::DataObjectPtr dmSample(pDataFactory->getType(
					"http://www.invenireaude.org/monitor/sys/net","UsageSample")->createDataObject());

		String strInterface;
		ssLine>>strInterface;


		long iDummy;

		struct UsageValues ovNow;

		ssLine>>ovNow.iRxBytes;
		ssLine>>ovNow.iRxPackets;
		ssLine>>ovNow.iRxErrors;
		ssLine>>ovNow.iRxDropped;

		ssLine>>iDummy;
		ssLine>>iDummy;
		ssLine>>iDummy;
		ssLine>>iDummy;

		ssLine>>ovNow.iTxBytes;
		ssLine>>ovNow.iTxPackets;
		ssLine>>ovNow.iTxErrors;
		ssLine>>ovNow.iTxDropped;

		if(hmOld.count(strInterface)){
			struct UsageValues ovTmp(ovNow);
			struct UsageValues& ovOld(hmOld[strInterface]);
			ovNow-=ovOld;
			ovOld=ovTmp;

			dmSample->setString("resource",   strInterface);
			dmSample->setInteger("rxBytes",   ovNow.iRxBytes);
			dmSample->setInteger("rxPackets", ovNow.iRxPackets);
			dmSample->setInteger("rxErrors",  ovNow.iRxErrors);
			dmSample->setInteger("rxDropped", ovNow.iRxDropped);

			dmSample->setInteger("txBytes",   ovNow.iTxBytes);
			dmSample->setInteger("txPackets", ovNow.iTxPackets);
			dmSample->setInteger("txErrors",  ovNow.iTxErrors);
			dmSample->setInteger("txDropped", ovNow.iTxDropped);
			lstSamples.add(dmSample);
		}else{
			hmOld[strInterface]=ovNow;
		}

		++itLines;

	}

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
GetUsage::UsageValues::UsageValues():
		iTxBytes(0),
		iTxPackets(0),
		iTxErrors(0),
		iTxDropped(0),
		iRxBytes(0),
		iRxPackets(0),
		iRxErrors(0),
		iRxDropped(0){
	IAS_TRACER;

}
/*************************************************************************/
GetUsage::UsageValues::UsageValues(const struct UsageValues& other){
	IAS_TRACER;
	(*this)=other;
}
/*************************************************************************/
GetUsage::UsageValues& GetUsage::UsageValues::operator -=(const struct UsageValues& other){
	IAS_TRACER;


	this->iTxBytes    -= other.iTxBytes;
	this->iTxPackets  -= other.iTxPackets;
	this->iTxErrors   -= other.iTxErrors;
	this->iTxDropped  -= other.iTxDropped;

	this->iRxBytes    -= other.iRxBytes;
	this->iRxPackets  -= other.iRxPackets;
	this->iRxErrors   -= other.iRxErrors;
	this->iRxDropped  -= other.iRxDropped;

	return *this;
}
/*************************************************************************/
GetUsage::UsageValues& GetUsage::UsageValues::operator =(const struct UsageValues& other){
	IAS_TRACER;


	this->iTxBytes    = other.iTxBytes;
	this->iTxPackets  = other.iTxPackets;
	this->iTxErrors   = other.iTxErrors;
	this->iTxDropped  = other.iTxDropped;

	this->iRxBytes    = other.iRxBytes;
	this->iRxPackets  = other.iRxPackets;
	this->iRxErrors   = other.iRxErrors;
	this->iRxDropped  = other.iRxDropped;

	return *this;
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
