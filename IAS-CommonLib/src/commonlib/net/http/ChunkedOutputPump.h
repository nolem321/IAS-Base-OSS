/*
 * File: IAS-CommonLib/src/commonlib/net/http/ChunkedOutputPump.h
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
#ifndef _IAS_Net_HTTP_ChunkedOutputPump_H_
#define _IAS_Net_HTTP_ChunkedOutputPump_H_

#include <commonlib/tools/Buffer.h>
#include <commonlib/net/async/IDataPump.h>

#include "../FileHandle.h"

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
/** The ChunkedOutputPump class.
 *
 */
class ChunkedOutputPump :
		public ::IAS::Buffer,
		public virtual Net::Async::IDataPump {

public:

	virtual ~ChunkedOutputPump() throw();

	virtual IBlockIO::Result pump();

protected:
	ChunkedOutputPump(IBlockIO* pBlockIO, std::istream& is);

	IBlockIO* pBlockIO;
	std::istream& is;

	size_t iDataSize;
	size_t iWrittenBytes;

	bool bEndOfData;

	static const size_t CLenghtOffset=4+2;

	void updateBuffer();

	friend class Factory<ChunkedOutputPump>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_HTTP_ChunkedOutputPump_H_ */
