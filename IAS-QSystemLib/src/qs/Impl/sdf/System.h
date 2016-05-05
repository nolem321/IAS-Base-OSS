/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/System.h
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
#ifndef _IAS_QS_SDF_System_H_
#define _IAS_QS_SDF_System_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>

#include <qs/Impl/System.h>

namespace IAS {
namespace QS {
namespace SDF {

class ContentManager;

class InputDriver;
class OutputDriver;

/*************************************************************************/
/** The SDF class.
 *
 */
class System :
		public Impl::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection);

	ContentManager*  	getContentManager();


	InputDriver*  getBrowserDriver(const API::Destination& destination);
	InputDriver*  getInputDriver(const API::Destination& destination);
	OutputDriver* getOutputDriver(const API::Destination& destination);


protected:

	System();

	virtual InputDriver*  createBrowserDriver(const API::Destination& destination)=0;
	virtual InputDriver*  createInputDriver(const API::Destination& destination)=0;
	virtual OutputDriver* createOutputDriver(const API::Destination& destination)=0;

	IAS_DFT_FACTORY< ContentManager >::PtrHolder               ptrContentManager;
	String strName;

	typedef HashMapStringToPointer<InputDriver>  InputDriversMap;
	typedef HashMapStringToPointer<OutputDriver> OutputDriversMap;

	InputDriversMap      hmInputDrivers;
	InputDriversMap      hmBrowserDrivers;
	OutputDriversMap     hmOutputDrivers;

	Mutex mutex;
};
/*************************************************************************/

}
}
}

#endif /* _IAS_QS_SDF_System_H_ */
