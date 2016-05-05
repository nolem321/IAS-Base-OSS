/*
 * File: IAS-CommonLib/src/commonlib/net/async/IDataPump.h
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
#ifndef _IAS_Net_Async_IDataPump_H_
#define _IAS_Net_Async_IDataPump_H_

#include <commonlib/tools/Buffer.h>
#include "../BlockIO.h"

namespace IAS {
namespace Net {
namespace Async {

//TODO (M)make safe, checksum, encryption etc.
//TODO (M) Factory with "protocol" as a parameter.

/*************************************************************************/
/** The IDataPump class.
 *
 */
class IDataPump {
public:

	virtual ~IDataPump() throw(){};

	virtual IBlockIO::Result pump()=0;

protected:

	typedef unsigned int DataSize;

	static const size_t CLenghtOffset=sizeof(DataSize);

};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_Async_IDataPump_H_ */
