/*
 * File: IAS-CommonLib/src/commonlib/net/async/InputDataPump.h
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
#ifndef _IAS_Net_Async_InputDataPump_H_
#define _IAS_Net_Async_InputDataPump_H_

#include <commonlib/tools/Buffer.h>

#include "IDataPump.h"
#include "../FileHandle.h"

namespace IAS {
namespace Net {
namespace Async {

/*************************************************************************/
/** The InputDataPump class.
 *
 */
class InputDataPump :
		public ::IAS::Buffer,
		public virtual IDataPump {

public:

	virtual ~InputDataPump() throw();

	virtual IBlockIO::Result pump();

protected:
	InputDataPump(IBlockIO* pBlockIO, std::ostream& os);

	IBlockIO* pBlockIO;
	std::ostream& os;

	DataSize    iOffset;

	friend class Factory<InputDataPump>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Async_InputDataPump_H_ */
