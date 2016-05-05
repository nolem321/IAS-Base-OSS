/*
 * File: IAS-QSystemLib-TestCases/src/testcases/TCEventCounter.cpp
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
#include "commonlib/commonlib.h"

#include "TCEventCounter.h"
#include <qs/workers/proc/ec/simple/EventCounter.h>

#include <org/invenireaude/qsystem/workers/ec/SimpleEventCounter.h>
#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/ec/DataFactory.h>


namespace IAS{
using namespace QS::Workers::Proc::EC;
using namespace org::invenireaude::qsystem::workers::ec;

namespace TCT{


/*************************************************************************/
TCEventCounter::TCEventCounter(TestSuite* pTestSuite):
	theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCEventCounter::~TCEventCounter() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCEventCounter::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::TCEventCounter::caseOne);
	theTestRunner.addCase("caseTwo",&::IAS::TCT::TCEventCounter::caseTwo);
	theTestRunner.addCase("caseThree",&::IAS::TCT::TCEventCounter::caseThree);

	TestUnit::init("TCEventCounter",&theTestRunner,pTestSuite);

}
/*************************************************************************/
void TCEventCounter::caseOne(){
	IAS_TRACER;
	
	try{
		File::Remove("/dev/shm/EC.caseOne");
		File::Remove("/dev/shm/EC.caseOne.s");
		File::Remove("/dev/shm/EC.caseOne.k");
	}catch(...){};

	Ext::SimpleEventCounterPtr ptrParameters(
			DataFactory::GetInstance()->getSimpleEventCounterType()->createSimpleEventCounter());

	ptrParameters->createConnection()->setLocation("caseOne");
	ptrParameters->setAvgKeyLen(32);
	ptrParameters->setResetInterval(5);
	ptrParameters->setSize(1024);

	IAS_DFT_FACTORY<EventCounter>::PtrHolder ptrEventCounter(
			IAS_DFT_FACTORY<Simple::EventCounter>::Create(ptrParameters));


	long ts = 1000;

	Ext::RecordPtr dmRecord;

	ptrEventCounter->update("KeyOne",10,ts++,dmRecord);
	ptrEventCounter->update("KeyOne",20,ts++,dmRecord);
	ptrEventCounter->update("KeyOne",30,ts++,dmRecord);
	ptrEventCounter->update("KeyOne",40,ts++,dmRecord);

	ptrEventCounter->read("KeyOne",dmRecord);

	if(dmRecord->getCount() != 4)
		IAS_THROW(BadUsageException("Test01, check 01"));

	ptrEventCounter->update("KeyTwo",110,ts,dmRecord);
	ptrEventCounter->update("KeyTwo",210,ts,dmRecord);
	ptrEventCounter->update("KeyTwo",310,ts,dmRecord);
	ptrEventCounter->update("KeyTwo",410,ts,dmRecord);


	if(!ptrEventCounter->read("KeyTwo",dmRecord) || dmRecord->getCount() != 4)
		IAS_THROW(BadUsageException("Test01, check 02"));


	ptrEventCounter->update("KeyOne",100,ts++,dmRecord);
	ptrEventCounter->update("KeyOne",200,ts++,dmRecord);
	ptrEventCounter->update("KeyOne",300,ts++,dmRecord);
	ptrEventCounter->update("KeyOne",400,ts++,dmRecord);

	if(!ptrEventCounter->read("KeyOne",dmRecord) || dmRecord->getCount()  != 3)
		IAS_THROW(BadUsageException("Test01, check 03"));

	if(ptrEventCounter->read("KeyTwo",dmRecord))
			IAS_THROW(BadUsageException("Test01, check 04"));

}
/*************************************************************************/
void TCEventCounter::caseTwo(){
	IAS_TRACER;




}
/*************************************************************************/
void TCEventCounter::caseThree(){
	IAS_TRACER;

}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
