/*
 * File: IAS-CommonLib/src/commonlib/types/BitMap.cpp
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
#include "BitMap.h"

#include <commonlib/commonlib.h>

namespace IAS {
/*************************************************************************/
BitMap::BitMap(const BitMap* pSource) {
	IAS_TRACER;

	iSize = pSource->iSize;
	int iTabSize = iSize / (sizeof(Word) << 3) + 1;

	//TODO (M) macro or something to allocate basic tabs !!! Auto delete !!! - better implementation
	tValues = (Word*)::IAS::MemoryManager::GetInstance()->allocate(sizeof(Word)*iTabSize);

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "BitMap, iTabSize="<<iTabSize<<", sizeof(Word)="<<sizeof(Word));

	const Word *pSrc = pSource->tValues;
	Word *pDst = tValues;

	for (int iIdx = 0; iIdx < iTabSize; iIdx++) {
		*pDst++ = *pSrc++;
	}
}
/*************************************************************************/
BitMap::BitMap(unsigned int iSize) {
	IAS_TRACER;
	this->iSize = iSize;
	int iTabSize = iSize / (sizeof(Word) << 3) + 1;

	//TODO (M) macro or something to allocate basic tabs !!! Auto delete !!! - better implementation
	tValues = (Word*)::IAS::MemoryManager::GetInstance()->allocate(sizeof(Word)*iTabSize);

	clear();
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "BitMap, iTabSize="<<iTabSize<<", sizeof(Word)="<<sizeof(Word));
}
/*************************************************************************/
BitMap::~BitMap() throw () {
	IAS_TRACER;
	::IAS::MemoryManager::GetInstance()->free(tValues);
}
/*************************************************************************/
void BitMap::getBits(BitsList& refOutputList){
	IAS_TRACER;

	refOutputList.clear();

	int iTabSize = iSize / (sizeof(Word) << 3) + 1;
	for (int iIdx = 0; iIdx < iTabSize; iIdx++) {

		Word iCur = tValues[iIdx];
		if(iCur != 0){

			Word iMask = 0x1L;
			for(int iBit=0;iBit < (sizeof(Word) << 3);iBit++ ){
				if(iCur & iMask){
					refOutputList.push_back(iIdx*(sizeof(Word)<<3)+iBit);
				}
				iMask <<=1;

			}/*FOR:iBit*/

		}/*IF:*/
	}/*FOR:iIdx*/

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "found "<<refOutputList.size()<<" bits.");
}
/*************************************************************************/
//We need this inheritance to get access to the Word type.
class BitMapHelper: public BitMap {
public:
	static inline unsigned int getIdxMask(size_t iSize) {
		unsigned int iMask = (sizeof(BitMap::Word) << 3) - 1;
		return iMask;
	}

	static unsigned int iIdxMask;

	static inline void IdxToWord(unsigned int iBitIdx, unsigned int& refTabIdx, BitMap::Word& iBitMask) {
		IAS_TRACER;
		refTabIdx = iBitIdx / (sizeof(BitMap::Word) << 3);
		iBitMask = 0x1L;
		iBitMask <<= iBitIdx & iIdxMask;
 		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), iBitIdx<<"="<<refTabIdx<<":"<<(void*)(long)iBitMask<<", mask="<<(void*)(long)iIdxMask);
	}
	;
};
/*************************************************************************/
unsigned int BitMapHelper::iIdxMask = BitMapHelper::getIdxMask(sizeof(BitMap::Word));
/*************************************************************************/
bool BitMap::getBit(unsigned int iIdx) {
	IAS_TRACER;

	if (iIdx >= iSize)
		IAS_THROW(BadUsageException("BitMap index >= iSize"));

	unsigned int iTabIdx;
	Word iMask;

	BitMapHelper::IdxToWord(iIdx, iTabIdx, iMask);
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "Word="<<(void*)tValues[iTabIdx]);
	return tValues[iTabIdx] & iMask;
}
/*************************************************************************/
void BitMap::setBit(unsigned int iIdx, bool bValue) {
	IAS_TRACER;

	if (iIdx >= iSize)
		IAS_THROW(BadUsageException("BitMap index >= iSize"));

	unsigned int iTabIdx;
	Word iMask;

	BitMapHelper::IdxToWord(iIdx, iTabIdx, iMask);
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "WordPre= "<<(void*)tValues[iTabIdx]);

	if (bValue)
		tValues[iTabIdx] |= iMask;
	else
		tValues[iTabIdx] ^= iMask;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "WordAfter="<<(void*)tValues[iTabIdx]);
}
/*************************************************************************/
void BitMap::makeOr(const BitMap* pOther) {
	IAS_TRACER;

	if (pOther->iSize != iSize)
		IAS_THROW(BadUsageException("BitMap::XOR:pOther->iSize != iSize"));

	int iTabSize = iSize / (sizeof(Word) << 3) + 1;
	for (int iIdx = 0; iIdx < iTabSize; iIdx++) {
		tValues[iIdx] |= pOther->tValues[iIdx];
	}

}
/*************************************************************************/
void BitMap::makeAnd(const BitMap* pOther) {
	IAS_TRACER;

	if (pOther->iSize != iSize)
		IAS_THROW(BadUsageException("BitMap::XOR:pOther->iSize != iSize"));

	int iTabSize = iSize / (sizeof(Word) << 3) + 1;
	for (int iIdx = 0; iIdx < iTabSize; iIdx++) {
		tValues[iIdx] &= pOther->tValues[iIdx];
	}

}
/*************************************************************************/
void BitMap::clear() {
	IAS_TRACER;
	int iTabSize = iSize / (sizeof(Word) << 3) + 1;
	for (int iIdx = 0; iIdx < iTabSize; iIdx++) {
		tValues[iIdx] = 0;
	}
}
/*************************************************************************/
int BitMap::getSize() const {
	IAS_TRACER;
	return iSize;
}
/*************************************************************************/

}
