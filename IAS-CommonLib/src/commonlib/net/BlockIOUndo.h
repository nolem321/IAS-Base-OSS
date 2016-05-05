/*
 * File: IAS-CommonLib/src/commonlib/net/BlockIOUndo.h
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
#ifndef _IAS_Net_BlockIOUndo_H_
#define _IAS_Net_BlockIOUndo_H_

#include "BlockIO.h"
#include <commonlib/tools/Buffer.h>

namespace IAS {
namespace Net {

/*************************************************************************/
/** The BlockIOUndo class.
 *
 */
class BlockIOUndo : public IBlockIO, private Buffer{
public:

	virtual ~BlockIOUndo() throw();


	virtual void undo(void* pData, size_t iDataSize);


protected:

	bool readUndone(void *pData, size_t iBufferLen, size_t& iDataSize);

	BlockIOUndo();

	size_t iUndoDataStart;
	size_t iUndoDataLen;

	static const size_t CMaxSize=0x10000;
	static const size_t CKeepSize=0x1000;

	friend class Factory<BlockIOUndo>;
};

/*************************************************************************/
}
}

#endif /* _IAS_Net_BlockIOUndo_H_ */
