/*
 * File: IAS-CommonLib/src/commonlib/net/async/KnownLengthOutputPump.h
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
#ifndef _IAS_Net_Async_KnownLengthOutputPump_H_
#define _IAS_Net_Async_KnownLengthOutputPump_H_

#include <commonlib/tools/Buffer.h>

#include "IDataPump.h"
#include "../FileHandle.h"

namespace IAS {
namespace Net {
namespace Async {

/*************************************************************************/
/** The KnownLengthOutputPump class.
 *
 */
class KnownLengthOutputPump :
		public ::IAS::Buffer,
		public virtual IDataPump {

public:

	virtual ~KnownLengthOutputPump() throw();

	virtual IBlockIO::Result pump();

protected:
	KnownLengthOutputPump(IBlockIO* pBlockIO, std::istream& is, size_t iDataSize);

	IBlockIO* pBlockIO;
	std::istream& is;

	size_t iDataLeft;
	size_t iWriterLeft;
	size_t iWrittenBytes;

	friend class Factory<KnownLengthOutputPump>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Async_KnownLengthOutputPump_H_ */
