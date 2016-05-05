/*
 * File: IAS-ServiceManagerLib/src/sm/cfg/ServiceIndexer.cpp
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
#include "ServiceIndexer.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace SM {
namespace Cfg {

/*************************************************************************/
ServiceIndexer::ServiceIndexer(){
	IAS_TRACER;
}
/*************************************************************************/
ServiceIndexer::~ServiceIndexer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ServiceIndexer::addEntry(GrpAttrPair aPair, int iIdx){
	IAS_TRACER;
	addEntry(aPair.first, aPair.second, iIdx);
}
/*************************************************************************/
void ServiceIndexer::addEntry(const String& strAttrName,
							  const String& strAttrValue,
							  int iIdx){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Entry: ("<<strAttrName<<","<<strAttrValue<<")="<<iIdx);

	GrpAttrToServiceIdxListMap::Key key(strAttrName,strAttrValue);

	if(!hmGrpAttrToServiceIdxList.hasKey(key)){
		hmGrpAttrToServiceIdxList[key]=IAS_DFT_FACTORY<BitMap>::Create(256);
	}

	hmGrpAttrToServiceIdxList.at(key)->setBit(iIdx);

}
/*************************************************************************/
void ServiceIndexer::getServiceIdxListByGrpAttrs(const GrpAttrPairList& lstGrpAttrPairs,
												 ServiceIdxList& refOutputList) const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"size="<<lstGrpAttrPairs.size());

	GrpAttrPairList::const_iterator it = lstGrpAttrPairs.begin();

	if(it == lstGrpAttrPairs.end())
		return;

	const BitMap *pCurentBitMap = NULL;

	if(!getBitMap(pCurentBitMap,*it)){
		IAS_THROW(ItemNotFoundException("No attribute pair found: "+it->first+","+it->second));
	}

	IAS_DFT_FACTORY<BitMap>::PtrHolder ptrWorkingBitMap(IAS_DFT_FACTORY<BitMap>::Create(pCurentBitMap));

	it++;
	while(it != lstGrpAttrPairs.end()){

		if(getBitMap(pCurentBitMap,*it)){
			ptrWorkingBitMap->makeAnd(pCurentBitMap);
		}else{
			IAS_THROW(ItemNotFoundException("No attribute pair found: "+it->first+","+it->second));
		}

		it++;
	}

	ptrWorkingBitMap->getBits(refOutputList);
}
/*************************************************************************/
bool ServiceIndexer::getBitMap(const BitMap* &refPtrBitMap,
							   const GrpAttrPair& aGrpAttrPair)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"BitMap: ("<<aGrpAttrPair.first<<","<<aGrpAttrPair.second<<")");

	GrpAttrToServiceIdxListMap::Key key(aGrpAttrPair.first,aGrpAttrPair.second);
	if(!hmGrpAttrToServiceIdxList.hasKey(key))
		return false;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"BitMap: found !");

	refPtrBitMap=hmGrpAttrToServiceIdxList.at(key);

	return true;
}
/*************************************************************************/
}
}
}
