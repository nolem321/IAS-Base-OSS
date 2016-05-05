/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCRefCountingPtr.cpp
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

#include "TCRefCountingPtr.h"

namespace IAS {
namespace TCT {

class TestObject;

typedef ::IAS::StandardFactory<TestObject>::RefCountingPtr TestObjectPtr;

class TestObject: public RefCountingPointee {
public:
	TestObject(const String& strName, bool *pIndicator){
		IAS_CHECK_IF_NULL(pIndicator);
		this->pIndicator=pIndicator;
		this->strName=strName;
		std::cout << strName << " :Object created. \n";
		*pIndicator = true;
	}

	~TestObject() {
		std::cout << strName << " :Object destroyed. \n";
		*pIndicator = false;
	}

	static TestObjectPtr Create(const String& strName, bool *pIndicator) {
		IAS_TRACER;

		TestObjectPtr ptrNew;
		ptrNew=StandardFactory<TestObject>::Create(strName, pIndicator);

		return ptrNew;
	}

protected:
	String strName;
	bool *pIndicator;

};

/*************************************************************************/

TCRefCountingPtr::TCRefCountingPtr(TestSuite* pTestSuite) :
	theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCRefCountingPtr::~TCRefCountingPtr() throw () {
	IAS_TRACER;
}

/*************************************************************************/
void TCRefCountingPtr::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCRefCountingPtr::caseALL);
	TestUnit::init("TCRefCountingPtr",&theTestRunner,pTestSuite);
}

/*************************************************************************/
void TCRefCountingPtr::caseALL() {
	IAS_TRACER;
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);

	IAS_MY_STACK().printStack(std::cout);

	bool bZero(false);
	bool bFirst(false);
	bool bSecond(false);

	std::cout << "before:\n";

	{
		TestObjectPtr ptrFirst;
	}
	std::cout << "after:\n";
	{
		TestObjectPtr ptrFirst(TestObject::Create("Zero", &bZero));
		if (!bZero)
			IAS_THROW(InternalException(String("Zero not initialized")));
	}
	if (bZero)
		IAS_THROW(InternalException(String("Zero not destroyed")));

	{
		std::cout << "before first:\n";
		TestObjectPtr ptrFirst = TestObject::Create("First", &bFirst);
		if (!bFirst)
			IAS_THROW(InternalException(String("Zero not initialized")));

		std::cout << "after first:\n";
		{
			std::cout << "now three copies:\n";
			TestObjectPtr ptrFirstCopy = ptrFirst;
			TestObjectPtr ptrFirstCopyTwo(ptrFirst);
			TestObjectPtr ptrFirstCopyThree(ptrFirstCopy);
			std::cout << "overwrite with a second.\n";
			ptrFirst = TestObject::Create("Second", &bSecond);
			if (!bSecond)
				IAS_THROW(InternalException(String("Second not initialized")));

			std::cout << "should delete the first.\n";
		}
		if (bFirst)
			IAS_THROW(InternalException(String("First not destroyed")));

		std::cout << "should delete the second.\n";
	}

	if (bSecond)
		IAS_THROW(InternalException(String("Second not destroyed")));

	std::cout << "Success !!!\n";

}

/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
