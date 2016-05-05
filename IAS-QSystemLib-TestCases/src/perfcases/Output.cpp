/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/Output.cpp
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

#include "Output.h"
#include <qs/api.h>

#include <qs/workers/proc/io/IOFactory.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/Input.h>

#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>



#include <dm/tools/Formatter.h>

namespace IAS{
using namespace QS::API;
using namespace QS::Workers::Proc;

namespace TCT{

/*************************************************************************/
Output::Output(TestSuite* pTestSuite):
	theTestRunner(this),
	parameters("samples/perftest/io.spec.xml"){
	IAS_TRACER;
	init(pTestSuite);

	reset();

	ptrGlobalContext=IAS_DFT_FACTORY<IAS::QS::Workers::Proc::GlobalContext>::Create(&parameters);

}
/*************************************************************************/

Output::~Output() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void Output::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseAll",&::IAS::TCT::Output::caseAll);
	TestUnit::init("Output",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void Output::send(const Variant& v){

	IAS_DFT_FACTORY<Message>::PtrHolder ptrNewMessage;

	IO::Output* pOutput=ptrWorkContextManager->getIOManager()->getOutput("output");

	StringStream ss;
	for(int j=0; j<10*v.iMsgSize; j++)
		ss<<"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";

	org::invenireaude::qsystem::workers::Ext::ContextPtr dmData(
			org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());


	for(int j=0; j<10*v.iMsgSize; j++){

		org::invenireaude::qsystem::workers::Ext::AttributePtr dmAttribute(
			org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createAttribute());

		dmAttribute->setName("TEST");
		dmAttribute->setValue("1234567890123456789012345678901234567890123456789");
		dmData->getAttributesList().add(dmAttribute);
	}


	for (int i = 0; i < v.iNumMsgs && !SYS::Signal::GetInstance()->isStopping(); i++) {

		org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(
				org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());

		if(v.bSmallAttrs || v.bSerialize){

		org::invenireaude::qsystem::workers::Ext::AttributePtr dmAttribute(
				org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createAttribute());

		dmAttribute = org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createAttribute();
		dmAttribute->setName("FMT");
		dmAttribute->setValue("JSON");
		dmContext->getAttributesList().add(dmAttribute);

		if(v.bSmallAttrs) {
			dmAttribute = org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createAttribute();
			dmAttribute->setName("TEST1");
			dmAttribute->setValue("123456789012345678901234567890");
			dmContext->getAttributesList().add(dmAttribute);

			dmAttribute = org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createAttribute();
			dmAttribute->setName("TEST2");
			dmAttribute->setValue("123456789012345678901234567890");
			dmContext->getAttributesList().add(dmAttribute);

			dmAttribute = org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createAttribute();
			dmAttribute->setName("TEST3");
			dmAttribute->setValue("123456789012345678901234567890");
			dmContext->getAttributesList().add(dmAttribute);
		}

		if(v.bBigAttrs)
			for(int a=0;a<24;a++){
				String strName("ATTR_B_");
				strName+='A'+char(a);
				dmAttribute = org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createAttribute();
				dmAttribute->setName(strName);
				dmAttribute->setValue("123456789012345678901234567890");
				dmContext->getAttributesList().add(dmAttribute);
			}
		}


		if(v.bSend){
			if(v.bSerialize){

				pOutput->send(dmContext,dmData);

			}else{
				ss.clear();
				ss.seekg(0);
				pOutput->send(dmContext,ss);
			}
		}

	}


}
/*************************************************************************/
void Output::receive(const Variant& v){

	if(!v.bSend)
		return;

	IAS_DFT_FACTORY<Message>::PtrHolder ptrNewMessage;

	IO::Input* pInput=ptrWorkContextManager->getIOManager()->getInput("input");

	DM::DataObjectPtr dmData;

	for (int i = 0; i < v.iNumMsgs && !SYS::Signal::GetInstance()->isStopping(); i++) {

		org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(
				org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());

		if(v.bSerialize)
				pInput->receive(dmContext,dmData);
			else
				pInput->receive(dmContext,ptrNewMessage);

	}

}
/*************************************************************************/
void Output::iterator(Variant& v){


	if((v.bBigAttrs && !v.bSmallAttrs) || (v.bSerialize && !v.bSend))
		return;

	if(SYS::Signal::GetInstance()->isStopping())
		return;

	std::cout<<std::endl;

	if(v.bSmallAttrs){

		if(v.bBigAttrs)
			std::cout<<"big attr ";
		else
			std::cout<<"attr ";
	}

	if(v.bSerialize)
		std::cout<<"serialize ";
	if(v.bSend)
		std::cout<<"send ";

	std::cout<<std::endl;

	for (v.iMsgSize = 1; v.iMsgSize <(v.bSend ? 16: 64); v.iMsgSize *= 2) {
		reset();

		ptrWorkContextManager=IAS_DFT_FACTORY<IAS::QS::Workers::Proc::WCM::WorkContextManager>::Create(
				ptrGlobalContext);

		{
			TimeSample ts(true);
			send(v);
			long iTime = ts.getSample() / 1000 + 1;
			std::cout << v.iNumMsgs << " messages of size: "
				<< v.iMsgSize * 1000 << ", " << iTime << "ms., avg: "
				<< v.iNumMsgs * 1000 / iTime << " m/s.";
		}

		if(v.bSend){

			TimeSample ts(true);
			receive(v);
			long iTime = ts.getSample() / 1000 + 1;
			std::cout << ", received: " << iTime << "ms., avg: "
				<< v.iNumMsgs * 1000 / iTime << " m/s.";
		}

		std::cout<<std::endl;
		ptrWorkContextManager=0;

		Environment* TheEnvironment = Environment::GetInstance();
		TheEnvironment->shutdown();
	}
}

/*************************************************************************/
void Output::caseAll(){

	Variant v;

	v.iNumMsgs=5000;

	for(int iSmallAttrs=0; iSmallAttrs < 2; iSmallAttrs++)
		for(int iBigAttrs=0; iBigAttrs < 2; iBigAttrs++)
			for(int iSend=0; iSend < 2; iSend++)
				for(int iSerialize=0; iSerialize < 2; iSerialize++){

					v.bSmallAttrs=iSmallAttrs;
					v.bBigAttrs=iBigAttrs;
					v.bSend=iSend;
					v.bSerialize=iSerialize;

					iterator(v);
				}
}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
