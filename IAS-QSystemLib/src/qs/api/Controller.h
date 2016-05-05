/*
 * File: IAS-QSystemLib/src/qs/api/Controller.h
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
#ifndef _IAS_QS_API_Controller_H_
#define _IAS_QS_API_Controller_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace API {

class Message;

/*************************************************************************/
/** The Controller class.
 *
 */
class Controller {
public:

	virtual ~Controller() throw(){};

	virtual unsigned int getNumMessages()=0;

	//TODO
	//virtual void getIOProcesses(unsigned int& iNumReaders, unsigned int& iNumWriters);
	//virtual void writeEnalbed(boolean bState);
	//virtual void readEnalbed(boolean bState);

	typedef IAS_DFT_FACTORY<Controller>::PtrHolder PtrHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Controller_H_ */

