/*
 * File: IAS-DataModelLib/src/dm/tools/Formatter.h
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
#ifndef _IAS_DM_Tools_Formatter_H_
#define _IAS_DM_Tools_Formatter_H_

#include <commonlib/commonlib.h>

#include "../../dm/DataObject.h"

namespace IAS {
namespace DM {
class DataFactory;
class Type;
namespace Tools {

/*************************************************************************/
/** The Formatter class.
 *
 */
class Formatter {
public:

	static DM::DataObjectPtr LoadStream(std::istream&is, const DM::DataFactory* pDataFactory, const DM::Type* pExpectedType=NULL);
	static DM::DataObjectPtr LoadFile(const String& strFileName, const DM::DataFactory* pDataFactory, const DM::Type* pExpectedType=NULL);

};
/*************************************************************************/
}
}
}

#endif /* _IAS_DM_Tools_Formatter_H_ */
