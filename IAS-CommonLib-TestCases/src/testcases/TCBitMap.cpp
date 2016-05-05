/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCBitMap.cpp
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

#include "TCBitMap.h"

namespace IAS {
namespace TCT {

int iSize = 550;
int iIdxs1[] = { 3, 6, 8, 15, 17, 53, 67, 74, 123, 243, 323, 448, -1 };
int iIdxs2[] = { 2, 6, 9, 15, 16, 34, 67, 73, 121, 244, 323, 448, -1 };
/*************************************************************************/

TCBitMap::TCBitMap(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/
TCBitMap::~TCBitMap() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void TCBitMap::fill(BitMap* pBitMap, int *tab) {
	IAS_TRACER;

	for (int i = 0; tab[i] > 0; i++) {
		pBitMap->setBit(tab[i], true);
	}
}
/*************************************************************************/
void TCBitMap::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("testSetGet",&::IAS::TCT::TCBitMap::testSetGet);
	theTestRunner.addCase("testGetBits",&::IAS::TCT::TCBitMap::testGetBits);
	theTestRunner.addCase("testOr",&::IAS::TCT::TCBitMap::testOr);
	theTestRunner.addCase("testAnd",&::IAS::TCT::TCBitMap::testAnd);
	theTestRunner.addCase("testCopy",&::IAS::TCT::TCBitMap::testCopy);
	TestUnit::init("TCBitMap",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCBitMap::testSetGet() {
	IAS_TRACER;

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap(IAS_DFT_FACTORY<BitMap>::Create(iSize));

	fill(ptrBitMap, iIdxs1);

	int i = 0;
	for (int j = 0; j < iSize; j++) {
		if (iIdxs1[i] == j) {
			if (!ptrBitMap->getBit(j)) {
				IAS_LOG(LogLevel::INSTANCE.isError(), "iIdx="<<j);
				IAS_THROW(InternalException("TCBitMap::testSetGet:1"))
			}
			i++;
		} else {
			if (ptrBitMap->getBit(j)) {
				IAS_LOG(LogLevel::INSTANCE.isError(), "iIdx="<<j);
				IAS_THROW(InternalException("TCBitMap::testSetGet:2"))
			}
		}
	}
}
/*************************************************************************/
void TCBitMap::testGetBits() {
	IAS_TRACER;

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap(IAS_DFT_FACTORY<BitMap>::Create(iSize));

	fill(ptrBitMap, iIdxs1);

	BitMap::BitsList lstBits;
	ptrBitMap->getBits(lstBits);
	BitMap::BitsList::const_iterator it = lstBits.begin();
	int i = 0;
	for (; iIdxs1[i] > 0 && it != lstBits.end(); i++, it++) {
		//std::cerr<<iIdxs1[i]<<":"<<*it<<std::endl;
		if (iIdxs1[i] != *it) {
			IAS_LOG(LogLevel::INSTANCE.isError(), "iIdx="<<i);
			IAS_THROW(InternalException("TCBitMap::testGetBits:1"))
		}
	}

	if (iIdxs1[i] > 0 || it != lstBits.end())
		IAS_THROW(InternalException("TCBitMap::testGetBits:2"));
}
/*************************************************************************/
void TCBitMap::testOr() {
	IAS_TRACER;

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap1(IAS_DFT_FACTORY<BitMap>::Create(iSize));
	fill(ptrBitMap1, iIdxs1);

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap2(IAS_DFT_FACTORY<BitMap>::Create(iSize));
	fill(ptrBitMap2, iIdxs2);

	ptrBitMap2->makeOr(ptrBitMap1);

	int i1 = 0;
	int i2 = 0;
	for (int j = 0; j < iSize; j++) {

		if (iIdxs1[i1] != j && iIdxs2[i2] != j) {
			if (ptrBitMap2->getBit(j)) {
				IAS_LOG(LogLevel::INSTANCE.isError(), "iIdx="<<j);
				IAS_THROW(InternalException("TCBitMap::testOr:3"))
			}

		}

		if (iIdxs1[i1] == j) {
			if (!ptrBitMap2->getBit(j))
				IAS_THROW(InternalException("TCBitMap::testOr:1"))
			i1++;
		}

		if (iIdxs2[i2] == j) {
			if (!ptrBitMap2->getBit(j))
				IAS_THROW(InternalException("TCBitMap::testOr:2"))
			i2++;
		}

	}

}
/*************************************************************************/
void TCBitMap::testAnd() {
	IAS_TRACER;

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap1(IAS_DFT_FACTORY<BitMap>::Create(iSize));
	fill(ptrBitMap1, iIdxs1);

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap2(IAS_DFT_FACTORY<BitMap>::Create(iSize));
	fill(ptrBitMap2, iIdxs2);

	ptrBitMap2->makeAnd(ptrBitMap1);

	int i1 = 0;
	int i2 = 0;
	for (int j = 0; j < iSize; j++) {

		if (iIdxs1[i1] != j || iIdxs2[i2] != j) {
			if (ptrBitMap2->getBit(j)) {
				IAS_LOG(LogLevel::INSTANCE.isError(), "iIdx="<<j);
				IAS_THROW(InternalException("TCBitMap::testAnd:1"))
			}
		} else {
			if (!ptrBitMap2->getBit(j))
				IAS_THROW(InternalException("TCBitMap::testAnd:2"))
		}

		if (iIdxs1[i1] == j)
			i1++;

		if (iIdxs2[i2] == j)
			i2++;

	}
}
/*************************************************************************/
void TCBitMap::testCopy() {
	IAS_TRACER;

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap1(IAS_DFT_FACTORY<BitMap>::Create(iSize));
	fill(ptrBitMap1, iIdxs1);

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrBitMap2(IAS_DFT_FACTORY<BitMap>::Create(ptrBitMap1.getPointer()));

	if (ptrBitMap1->getSize() != ptrBitMap2->getSize())
		IAS_THROW(InternalException("TCBitMap::testCopy:1"))

	for (int j = 0; j < iSize; j++) {
		if (ptrBitMap1->getBit(j) != ptrBitMap2->getBit(j))
			IAS_THROW(InternalException("TCBitMap::testCopy:2"))
	}

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
