/*
 * File: IAS-CommonLib/src/commonlib/net/http/HeaderInputPump.h
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
#ifndef _IAS_Net_HTTP_HeaderInputPump_H_
#define _IAS_Net_HTTP_HeaderInputPump_H_

#include <commonlib/memory/memory.h>
#include <commonlib/net/async/IDataPump.h>

#include <cstddef>

namespace IAS {
namespace Net {
namespace HTTP {
class Header;
/*************************************************************************/
/** The HeaderInputPump class.
 *
 */
class HeaderInputPump
		: public IAS::Net::Async::IDataPump,
		  protected Buffer{
public:

	virtual ~HeaderInputPump() throw();

	virtual IBlockIO::Result pump();

protected:
	HeaderInputPump(Header *pHeader, IBlockIO* pBlockIO);

	Header           *pHeader;
	IBlockIO         *pBlockIO;
	StringStream     ssContent;

	bool locateEndOfHeader(size_t& iNewBytes);

	int             iCounter;

	friend class Factory<HeaderInputPump>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_HTTP_HeaderInputPump_H_ */
