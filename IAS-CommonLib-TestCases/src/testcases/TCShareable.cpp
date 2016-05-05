/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCShareable.cpp
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

#include "TCShareable.h"

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <unistd.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
TCShareable::TCShareable(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

	strObjectName="/IAS.Test.";
	strObjectName+=__FUNCTION__;
}
/*************************************************************************/
TCShareable::~TCShareable() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCShareable::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCShareable::caseALL);
	TestUnit::init("TCShareable",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCShareable::testChild(const String& strName){
	IAS_TRACER;


	int child;
	switch(child=fork()){

	case -1: perror("fork"); break;
	case 0:
	{
		SharedContent<Object>::Descriptor desc;
		desc.setName(strObjectName);
		desc.setOpenMode(SharedContent<Object>::Descriptor::OM_ATTACH);

		IAS_DFT_FACTORY< SharedContent<Object> >::PtrHolder ptrSharedContent;
		ptrSharedContent = IAS_DFT_FACTORY< SharedContent<Object> >::Create(desc);

		Object *o = ptrSharedContent->get();
		if(o->iValue!=102)
			IAS_THROW(InternalException("TCShareable: o->iValue!=102"));

		if(strncmp(o->strValue,"Creator",256) != 0)
			IAS_THROW(InternalException("TCShareable:: Creator"));

		strcpy(o->strValue,strName.c_str());
		o->iValue=1000;

	}
	exit(0);

	default:
		waitpid(child,NULL,0);
		std::cerr << "\nCHILD Terminated:" <<child<<std::endl;
	}

}
/*************************************************************************/
void TCShareable::caseALL(){
	IAS_TRACER;

	SharedContent<Object>::Descriptor desc;
	desc.setName(strObjectName);
	desc.setOpenMode(SharedContent<Object>::Descriptor::OM_CREATE_ALWAYS);
	desc.setCloseMode(SharedContent<Object>::Descriptor::CM_DESTROY);

	IAS_DFT_FACTORY< SharedContent<Object> >::PtrHolder ptrSharedContent;
	ptrSharedContent = IAS_DFT_FACTORY< SharedContent<Object> >::Create(desc);

	Object *o = ptrSharedContent->get();
	o->iValue=102;
	strcpy(o->strValue,"Creator");

	testChild(strObjectName);

	if(strncmp(o->strValue,strObjectName.c_str(),256) != 0)
		IAS_THROW(InternalException("TCShareable::testALL/String"));

	if(o->iValue != 1000)
		IAS_THROW(InternalException("TCShareable::testALL/Integer"));

	std::cerr<<"Values"<<o->strValue<<":"<<o->iValue<<std::endl;
}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
