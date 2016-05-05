/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/df/InputBase.h
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
#ifndef _IAS_QS_SDF_DF_InputBase_H_
#define _IAS_QS_SDF_DF_InputBase_H_

#include "../Driver.h"
#include <qs/api.h>

namespace IAS {
namespace QS {
namespace SDF {
namespace DF {

/*************************************************************************/
/** The InputBase class.
 *
 */
class InputBase : public SDF::InputDriver {
public:

	virtual ~InputBase() throw();

	virtual unsigned int skip(unsigned int iOffset);

	virtual unsigned int getNumMessages();

protected:

	InputBase(const API::Destination& destination);
	String strFileName;
	String strBaseName;

	InputFile inFile;

	Mutex mutex;

	int    iCount;

	std::istream* isp;

	Message* receiveImpl(int iTimeWait);
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_SDF_File_InputBase_H_ */
