/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/io/Manager.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_IO_Manager_H_
#define _IAS_QS_Workers_Proc_WCM_IO_Manager_H_

#include <commonlib/commonlib.h>


#include <qs/workers/proc/io/IOManager.h>
#include <qs/workers/proc/io/IOFactory.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
class WorkContextManager;
namespace IO {

class Context;
/*************************************************************************/
/** The Manager class.
 *
 */
class Manager :
		public Proc::IO::IOManager{
	public:

	virtual ~Manager() throw();

	virtual Proc::IO::Output* getOutput(const String& strName)const;
	virtual void addOutput(const String& strName, Proc::IO::Output* pOutput);

	virtual Proc::IO::Input* getInput(const String& strName)const;
	virtual void addInput(const String& strName, Proc::IO::Input* pOutput);

	virtual Proc::IO::Controller* getController(const String& strName)const;
	virtual void addController(const String& strName, Proc::IO::Controller* pController);

protected:

	Manager(WorkContextManager* pWorkContextManager);
	WorkContextManager* pWorkContextManager;

	friend class Factory<Manager>;

	typedef HashMapStringToPointer<Proc::IO::Output>       OutputsMap;
	OutputsMap                                             hmOutputs;

	typedef HashMapStringToPointer<Proc::IO::Input>        InputsMap;
	InputsMap                                              hmInputs;

	typedef HashMapStringToPointer<Proc::IO::Controller>   ControllersMap;
	ControllersMap                                         hmControllers;

	IAS_DFT_FACTORY<Proc::IO::IOFactory>::PtrHolder        ptrFactory;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_WCM_IO_Manager_H_ */
