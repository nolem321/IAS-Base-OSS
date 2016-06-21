/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ProgramProvider.h
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
#ifndef _IAS_QS_Workers_Proc_ProgramProvider_H_
#define _IAS_QS_Workers_Proc_ProgramProvider_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

//TODO common include for Lang
#include <lang/interpreter/ProgramLoader.h>
#include <lang/model/Model.h>
#include <lang/tools/parser/LexerIStreamFactoryForFiles.h>
#include <lang/interpreter/proc/processor.h>

#include <org/invenireaude/qsystem/workers/Context.h>

#include "io/IOManager.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace Prog{
class ProgramSet;
}

/*************************************************************************/
/** The ProgramProvider class.
 *
 */
class ProgramProvider {
public:

	virtual ~ProgramProvider() throw();

	const IAS::Lang::Interpreter::Exe::Program*
	    loadProgram(const String& strProgramName);

	void load(const String& strProgramName, Prog::ProgramSet *pProgramSet);

	void getSources(const String& strProgramName,
					DM::DataObjectList& lstPrograms);

protected:

	Mutex mutex;
	ProgramProvider(::IAS::DM::DataFactory *pDataFactory);

	::IAS::DM::DataFactory *pDataFactory;

	IAS_DFT_FACTORY< IAS::Lang::Interpreter::ProgramLoader >::PtrHolder ptrLoader;

	friend class Factory<ProgramProvider>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_ProgramProvider_H_ */
