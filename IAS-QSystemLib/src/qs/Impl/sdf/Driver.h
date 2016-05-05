/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Driver.h
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
#ifndef _IAS_QS_SDF_Driver_H_
#define _IAS_QS_SDF_Driver_H_

#include <commonlib/commonlib.h>


namespace IAS {
namespace QS {
namespace SDF {

class Message;
/*************************************************************************/
class InputDriver  {
public:
	virtual ~InputDriver(){};

	virtual Message* receive(int iTimeWait)=0;
	virtual unsigned int skip(unsigned int iOffset)=0;
	virtual unsigned int getNumMessages()=0;

	void updateFormat(Message *pMessage, const String& strFileName);
};
/*************************************************************************/
class OutputDriver  {
public:
	virtual ~OutputDriver(){};

	virtual bool send(Message* pMessage)=0;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_QS_SDF_Driver_H_ */
