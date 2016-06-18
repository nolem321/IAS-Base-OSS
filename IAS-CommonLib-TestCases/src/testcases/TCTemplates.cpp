/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCTemplates.cpp
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

#include "TCTemplates.h"

#include <iomanip>
#include <unistd.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
TCTemplates::TCTemplates(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/
TCTemplates::~TCTemplates() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCTemplates::init(TestSuite* pTestSuite){	
	IAS_TRACER;

	theTestRunner.addCase("Simple",&::IAS::TCT::TCTemplates::caseSimple);
	theTestRunner.addCase("Nested",&::IAS::TCT::TCTemplates::caseNested);

	TestUnit::init("TCTemplates",&theTestRunner,pTestSuite);
}

/*************************************************************************/
void TCTemplates::runCase(Template::Arguments& a, const Template* t, const String& strResult){

	IAS_TRACER;

	IAS::TimeSample ts(true);
	StringStream os;
	t->evaluate(a,os);

	if(strResult.compare(os.str()) != 0){

		std::cout<<"Exp: "<<strResult<<"\n";

		std::cout<<"Got: "<<os.str()<<"\n";

		IAS_THROW(InternalException("Template failed"));
	}
}
/*************************************************************************/
void TCTemplates::caseSimple(){

	IAS_TRACER;

	Template::Arguments args;

	args.add("K1","V1");
	args.add("K2","V2");
	args.add("K3","V3");

	IAS_DFT_FACTORY<Template>::PtrHolder ptrTemplate(IAS_DFT_FACTORY<Template>::Create("${K1}$${K2}$$${K3}"));
	runCase(args,ptrTemplate,"V1$${K2}$$V3");
}
/*************************************************************************/
void TCTemplates::caseNested(){

	IAS_TRACER;

	Template::Arguments args;

	args.add("K1","OV1");
	args.add("K2","V2");
	args.add("K3","V3");

	Template::Arguments* pNested = NULL;

	pNested = args.createNested("N1");
	pNested->add("K1","NV1a");
	pNested->add("K2","NV2a");

	pNested = args.createNested("N1");
	pNested->add("K1","NV1b");
	pNested->add("K2","NV2b");

	IAS_DFT_FACTORY<Template>::PtrHolder ptrTemplate(
			IAS_DFT_FACTORY<Template>::Create(
					"${K1}${*N1}[ begin n:${K1} o:${K3} end ] ${*N1}${K1}"
					));

	runCase(args,ptrTemplate,"OV1[ begin n:NV1a o:V3 end ] [ begin n:NV1b o:V3 end ] OV1");
}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
