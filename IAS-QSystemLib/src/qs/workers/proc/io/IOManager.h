/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/IOManager.h
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
#ifndef _IAS_QS_Workers_Proc_IO_IOManager_H_
#define _IAS_QS_Workers_Proc_IO_IOManager_H_

#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

class Output;
class Input;
class Controller;

/*************************************************************************/
class IOManager {
public:
	virtual ~IOManager() throw(){};

	virtual Output* getOutput(const String& strName)const=0;
	virtual void addOutput(const String& strName, Output* pOutput)=0;

	virtual Input* getInput(const String& strName)const=0;
	virtual void addInput(const String& strName, Input* pOutput)=0;

	virtual Controller* getController(const String& strName)const=0;
	virtual void addController(const String& strName, Controller* pController)=0;

	virtual Output*     getDefaultOutput()const;
	virtual Output*     getDefaultError()const;
	virtual Input*      getDefaultInput()const;

protected:
	IOManager()throw();

	void setDefaultOutput(const String& strName);
	void setDefaultInput(const String& strName);
	void setDefaultError(const String& strName);

private:
	String strDefaultInput;
	String strDefaultOutput;
	String strDefaultError;
};
/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_IO_IOManager_H_ */
