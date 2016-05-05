/*
 * File: IAS-CommonLib/src/commonlib/net/http/ChunkedInputPump.h
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
#ifndef _IAS_Net_HTTP_ChunkedInputPump_H_
#define _IAS_Net_HTTP_ChunkedInputPump_H_

#include <commonlib/tools/Buffer.h>
#include <commonlib/net/async/IDataPump.h>

#include "../FileHandle.h"

namespace IAS {
namespace Net {
namespace HTTP {

/*************************************************************************/
/** The ChunkedInputPump class.
 *
 */
class ChunkedInputPump :
		public ::IAS::Buffer,
		public virtual Net::Async::IDataPump {

public:

	virtual ~ChunkedInputPump() throw();

	virtual IBlockIO::Result pump();

protected:
	ChunkedInputPump(IBlockIO* pBlockIO, std::ostream& os);

	IBlockIO* pBlockIO;
	std::ostream& os;

	bool        bEndOfData;
	size_t      iChunkSize;

	enum State {
		S_Length,
		S_CR,
		S_LF,
		S_Data,
		S_DataCR,
		S_DataLF
	};

	State iState;

	bool computeDataLen();

	friend class Factory<ChunkedInputPump>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_HTTP_ChunkedInputPump_H_ */
