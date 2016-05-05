/*
 * File: IAS-ServiceManagerLib/src/sm/cfg/ServiceIndexer.h
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
#ifndef _IAS_SM_Cfg_ServiceIndexer_H_
#define _IAS_SM_Cfg_ServiceIndexer_H_

#include <commonlib/commonlib.h>
#include <list>
#include "types.h"

namespace IAS {
namespace SM {
namespace Cfg {

/*************************************************************************/
/** The ServiceIndexer class.
 *
 */
class ServiceIndexer {
public:

	virtual ~ServiceIndexer() throw();

	void addEntry(GrpAttrPair aPair, int iIdx);

	void addEntry(const String& strAttrName,
				  const String& strAttrValue,
				  int iIdx);

	void getServiceIdxListByGrpAttrs(const GrpAttrPairList& lstGrpAttrPairs,
							         ServiceIdxList& refOutputList) const;

protected:
	ServiceIndexer();

	typedef HashMapStringPairToPointer<BitMap> GrpAttrToServiceIdxListMap;

	GrpAttrToServiceIdxListMap hmGrpAttrToServiceIdxList;

	bool getBitMap(const BitMap* &refPtrBitMap, const GrpAttrPair& aGrpAttrPair)const;

	friend class ::IAS::Factory<ServiceIndexer>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Cfg_ServiceIndexer_H_ */
