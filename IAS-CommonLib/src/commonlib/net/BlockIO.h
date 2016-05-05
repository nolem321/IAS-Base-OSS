/*
 * File: IAS-CommonLib/src/commonlib/net/BlockIO.h
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
#ifndef _IAS_Net_BlockIO_H_
#define _IAS_Net_BlockIO_H_

#include <cstddef>

namespace IAS {
namespace Net {

/*************************************************************************/
/** The BlockIO class.
 *
 */
class IBlockIO {

public:

	virtual ~IBlockIO()throw(){};

	enum Result {
		RC_OK           = 0,
		RC_WantRead     = 1,
		RC_WantWrite    = 2,
		RC_WantAny      = 3         //SSL accept,connect etc.
	};

	virtual Result read(void *pData, size_t iBufferLen, size_t& iDataSize)=0;
	virtual Result write(const void *pData, size_t iDataSize, size_t& iWritten)=0;

	virtual void undo(void* pData, size_t iDataSize)=0;
};

/*************************************************************************/
}
}

#endif /* _IAS_Net_BlockIO_H_ */
