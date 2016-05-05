/*
 * File: IAS-CommonLib/src/commonlib/net/http/HeaderOutputPump.h
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
#ifndef _IAS_Net_HTTP_HeaderOutputPump_H_
#define _IAS_Net_HTTP_HeaderOutputPump_H_

#include <commonlib/memory/memory.h>
#include <commonlib/net/async/IDataPump.h>

#include <cstddef>

namespace IAS {
namespace Net {
namespace HTTP {
class Header;
/*************************************************************************/
/** The HeaderOutputPump class.
 *
 */
class HeaderOutputPump
		: public IAS::Net::Async::IDataPump{
public:

	virtual ~HeaderOutputPump() throw();

	virtual IBlockIO::Result pump();

protected:
	HeaderOutputPump(Header *pHeader, IBlockIO* pBlockIO);

	Header          *pHeader;
	IBlockIO         *pBlockIO;

	String::size_type iOffset;

	String		     strContent;

	friend class Factory<HeaderOutputPump>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_HTTP_HeaderOutputPump_H_ */
