/*
 * File: IAS-ServiceManagerLib/src/sm/cfg/types.h
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
#ifndef _IAS_SM_Cfg_Types_H_
#define _IAS_SM_Cfg_Types_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace SM {
namespace Cfg {

typedef ::IAS::BitMap::BitsList ServiceIdxList;
typedef std::pair<const String, const String> GrpAttrPair;
typedef std::list<GrpAttrPair> GrpAttrPairList;

}
}
}

#endif
