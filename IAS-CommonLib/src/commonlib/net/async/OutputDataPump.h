/*
 * File: IAS-CommonLib/src/commonlib/net/async/OutputDataPump.h
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
#ifndef _IAS_Net_Async_OutputDataPump_H_
#define _IAS_Net_Async_OutputDataPump_H_

#include <commonlib/tools/Buffer.h>

#include "IDataPump.h"
#include "../FileHandle.h"

namespace IAS {
namespace Net {
namespace Async {

/*************************************************************************/
/** The OutputDataPump class.
 *
 */
class OutputDataPump :
		public ::IAS::Buffer,
		public virtual IDataPump {

public:

	virtual ~OutputDataPump() throw();

	virtual IBlockIO::Result pump();

protected:
	OutputDataPump(IBlockIO* pBlockIO, std::istream& is);

	IBlockIO* pBlockIO;
	std::istream& is;

	int iDataSize;
	int iWrittenBytes;

	bool bEndOfData;
	friend class Factory<OutputDataPump>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Async_OutputDataPump_H_ */
