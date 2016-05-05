/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/Put.cpp
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

#include "Put.h"
#include <qs/api.h>

#include <qs/workers/proc/io/IOFactory.h>
#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <dm/tools/Formatter.h>

namespace IAS{
using namespace QS::API;
using namespace QS::Workers::Proc;

namespace TCT{


/*************************************************************************/
Put::Put(TestSuite* pTestSuite):
	theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

	reset();
}

/*************************************************************************/

Put::~Put() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void Put::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseEmpty",&::IAS::TCT::Put::caseEmpty);
	theTestRunner.addCase("caseZero",&::IAS::TCT::Put::caseZero);
	theTestRunner.addCase("caseOne",&::IAS::TCT::Put::caseOne);
	theTestRunner.addCase("caseTwo",&::IAS::TCT::Put::caseTwo);
	theTestRunner.addCase("caseThree",&::IAS::TCT::Put::caseThree);
	TestUnit::init("Put",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void Put::action(const Variant& v){

	Environment* TheEnvironment = Environment::GetInstance();
		TheEnvironment->shutdown();

		Connection::PtrHolder ptrConnection(TheEnvironment->connect(dmConnection));
		Session::PtrHolder ptrSession(ptrConnection->createSession(Session::SM_NonTransacted));

		Destination destination("Q.BIG");
		Producer::PtrHolder ptrProducer(
				ptrSession->createProducer(destination));
		Consumer::PtrHolder ptrConsumer(
				ptrSession->createConsumer(destination));

		IAS_DFT_FACTORY<Message>::PtrHolder ptrNewMessage;

		for (int i = 0; i < v.iNumMsgs; i++) {

			ptrNewMessage = ptrConnection->createMessage();

			if(v.bOnlyCreateEmpty)
				continue;


			StringStream ss;
			std::ostream& os(v.bMockContent ? ss : (std::ostream&)*(ptrNewMessage->getContent()));
			for(int j=0; j<10*v.iMsgSize; j++)
				os<<"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";


			ptrNewMessage->getAttributes()->setValue("TEST1","123456789012345678901234567890");
			ptrNewMessage->getAttributes()->setValue("TEST2","123456789012345678901234567890");
			ptrNewMessage->getAttributes()->setValue("TEST3","123456789012345678901234567890");

			if(v.bBigAttrs){
				for(int a=0;a<24;a++){
					String strName("ATTR_B_");
					strName+='A'+char(a);
					ptrNewMessage->getAttributes()->setValue(strName,"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
				}
			}

			if(v.bSend)
				ptrProducer->produce(ptrNewMessage);
		}


}
/*************************************************************************/
void Put::iterator(const String& strName, Variant& v){

	std::cout<<std::endl;

	for (v.iMsgSize = 1; v.iMsgSize <(v.bSend ? 16: 64); v.iMsgSize *= 2) {
		reset();
		TimeSample ts(true);
		action(v);
		long iTime = ts.getSample() / 1000;
		std::cout << strName<<" "<< v.iNumMsgs << " messages of size: "
				<< v.iMsgSize * 1000 << ", " << iTime << "ms., avg: "
				<< v.iNumMsgs * 1000 / iTime << " m/s." << std::endl;

		Environment* TheEnvironment = Environment::GetInstance();
		TheEnvironment->shutdown();
	}
}
/*************************************************************************/
void Put::caseEmpty(){

	Variant v;

	v.iNumMsgs=20000;

	v.bOnlyCreateEmpty=true;
	v.bMockContent=true;
	v.bBigAttrs=false;
	v.bSend=false;

	iterator("Case Empty ",v);
}
/*************************************************************************/
void Put::caseZero(){

	Variant v;

	v.iNumMsgs=20000;

	v.bOnlyCreateEmpty=false;
	v.bMockContent=true;
	v.bBigAttrs=false;
	v.bSend=false;

	iterator("Case Zero ",v);
}
/*************************************************************************/
void Put::caseOne(){

	Variant v;

	v.iNumMsgs=20000;

	v.bOnlyCreateEmpty=false;
	v.bMockContent=false;
	v.bBigAttrs=false;
	v.bSend=false;

	iterator("Case no-send ",v);
}
/*************************************************************************/
void Put::caseTwo(){

	Variant v;

	v.iNumMsgs=20000;

	v.bOnlyCreateEmpty=false;
	v.bMockContent=false;
	v.bBigAttrs=true;
	v.bSend=false;

	iterator("Case big-attrs ",v);
}
/*************************************************************************/
void Put::caseThree(){

	Variant v;

	v.iNumMsgs=5000;

	v.bOnlyCreateEmpty=false;
	v.bMockContent=false;
	v.bBigAttrs=false;
	v.bSend=true;

	iterator("Case send ",v);
}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
