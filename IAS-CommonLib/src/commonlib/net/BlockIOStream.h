/*
 * File: IAS-CommonLib/src/commonlib/net/BlockIOStream.h
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
#ifndef _IAS_Net_BlockIOStream_H_
#define _IAS_Net_BlockIOStream_H_

#include <commonlib/memory/memory.h>

#include "BlockIOBuffer.h"
#include "FileHandle.h"

namespace IAS {
namespace Net {

class BlockIOStream :
      protected BlockIOBuffer,
	  public std::iostream{
public:
	virtual ~BlockIOStream()throw(){};

	BlockIOStream(IBlockIO* pIBlockIO);

	//TODO (M) forbid coping.
};
/*************************************************************************/
}
}

#endif /* _IAS_Net_BlockIOStream_H_ */
