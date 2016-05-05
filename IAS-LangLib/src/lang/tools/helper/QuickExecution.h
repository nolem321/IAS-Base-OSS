/*
 * File: IAS-LangLib/src/lang/tools/helper/QuickExecution.h
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
#ifndef _IAS_AS_Lang_Tools_Helper_QuickExecution_H_
#define _IAS_AS_Lang_Tools_Helper_QuickExecution_H_


#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include <lang/interpreter/proc/processor.h>
#include <lang/interpreter/ProgramLoader.h>

namespace IAS {
namespace Lang {
namespace Tools {
namespace Helper {

/*************************************************************************/
/** The class. */
class QuickExecution {
	public:

	virtual void loadXML(const String& strFileName);
	virtual void setXML(const String& strXML);
	virtual void saveXML(const String& strFileName);
	virtual void getXML(String& strXML);

	virtual void loadProgram(const String& strProgramName);
	virtual void execute();

protected:
	QuickExecution();
	virtual ~QuickExecution() throw ();

	static ::IAS::DM::DataFactory* ptrDataFactory;

	friend class ::IAS::Factory<QuickExecution>;

	::IAS::DM::DataObjectPtr ptrInputDataObject;
	::IAS::DM::DataObjectPtr ptrOutputDataObject;

	Interpreter::Exe::Program *pProgram;

	IAS_DFT_FACTORY<Interpreter::ProgramLoader>::PtrHolder ptrLoader;

};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Tools_Helper_QuickExecution_H_ */
