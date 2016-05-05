/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSerializationHelper.cpp
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

#include "TCSerializationHelper.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
TCSerializationHelper::TCSerializationHelper(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCSerializationHelper::~TCSerializationHelper() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCSerializationHelper::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("c01",&::IAS::TCT::TCSerializationHelper::case01);
	TestUnit::init("TCSerializationHelper",&theTestRunner,pTestSuite);
}
/*************************************************************************/
struct Data{

	Data(const String& strValue, int iValue):
		strValue1(strValue+"One"),
		strValue2(strValue+"Two"),
		iValue1(iValue),
		iValue2(iValue+2000){};

	Data():iValue1(0),iValue2(0){};

	String strValue1;
	String strValue2;

	int    iValue1;
	int    iValue2;

	bool operator ==(const Data& other){
		return other.strValue1.compare(strValue1)==0 &&
			   other.strValue2.compare(strValue2)==0 &&
			   other.iValue1 == iValue1 &&
			   other.iValue2 == iValue2;
	}

	bool operator !=(const Data& other){
		return !( (*this) == other );
	}
};

/*************************************************************************/
void TCSerializationHelper::case01(){
	IAS_TRACER;


	SerializationHelper sh;

	StringStream ssTmp1;

	Data in("Data ąćęółńźż 123456789 \n \t ąą ",123);
	Data out;

	sh.write(in.strValue1,ssTmp1);
	sh.write(in.iValue1,ssTmp1);
	sh.write(in.strValue2,ssTmp1);
	sh.write(in.iValue2,ssTmp1);

	StringStream ssTmp2(ssTmp1.str());

	sh.read(out.strValue1,ssTmp2);
	sh.read(out.iValue1,ssTmp2);
	sh.read(out.strValue2,ssTmp2);
	sh.read(out.iValue2,ssTmp2);

	if(out != in)
		IAS_THROW(InternalException("No match !"));

	if(ssTmp2.get() != EOF)
		IAS_THROW(InternalException("EOF expected !"));

	std::cerr<<out.strValue1<<std::endl;
	std::cerr<<out.strValue2<<std::endl;
	std::cerr<<out.iValue1<<std::endl;
	std::cerr<<out.iValue2<<std::endl;

}

/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */

