/*
 * File: IAS-CommonLib/src/commonlib/net/FileHandle.h
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
#ifndef _IAS_Net_FileHandle_H_
#define _IAS_Net_FileHandle_H_

#include <commonlib/memory/memory.h>

#include "BlockIOUndo.h"
#include "Peer.h"

namespace IAS {
namespace Net {

/*************************************************************************/
/** The FileHandle class.
 *
 */

class FileHandle : public BlockIOUndo{
public:

	virtual ~FileHandle()throw();


	virtual Result  read(void *pData, size_t iBufferLen, size_t& iDataSize);
	virtual Result  write(const void *pData, size_t iDataSize, size_t& iWritten);

	int getFD() const { return iFileDescriptor; };

	void setNonBlocking();

	void setTimeout(int iTimeout);
	static const int  C_UnLimited = -1;

	void setPeer(const Peer& peer);

	const Peer& getPeer()const;

protected:
	FileHandle(int iFileDescriptor);

	void close();

	enum WaitMode{
		WM_Read,
		WM_Write
	};

	bool waitForData(WaitMode iMode);

	int iFileDescriptor;
	int iTimeout;

	Peer peer;

	static const int  C_NonBlock = -2;

	friend class Factory<FileHandle>;


};
/*************************************************************************/
}
}

#endif /* _IAS_Net_FileHandle_H_ */
