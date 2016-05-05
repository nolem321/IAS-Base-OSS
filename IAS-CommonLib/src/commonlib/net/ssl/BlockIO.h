/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/BlockIO.h
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
#ifndef _IAS_Net_SSL_BlockIO_H_
#define _IAS_Net_SSL_BlockIO_H_

#include "../FileHandle.h"
#include <commonlib/memory/ma/Factory.h>
#include <openssl/ssl.h>

namespace IAS {
namespace Net {
class FileHandle;
namespace SSL {

/*************************************************************************/
/** The BlockIO class.
 *
 */
class BlockIO /*: Net::IReadBlockIO, Net::IWriteBlockIO */{
public:

	virtual ~BlockIO() throw();

	virtual int   write(const void *pData, size_t iDataSize);
	virtual int   read(void *pData, size_t iDataSize);

	BIO *getBIO(){return bio;};

	enum Method{
		M_Socket,
		M_File,
	};
protected:
	BlockIO(Net::FileHandle* pFileHandle, Method iMethod=M_Socket);

	BIO *bio;
	friend class Factory<BlockIO>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_SSL_BlockIO_H_ */
