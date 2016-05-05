/*
 * File: IAS-LangLib/src/lang/interpreter/extern/Module.h
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
#ifndef _IAS_Lang_Interpreter_Extern_Module_H_
#define _IAS_Lang_Interpreter_Extern_Module_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include "Statement.h"

namespace IAS {
namespace Lang {
namespace Interpreter {

namespace Exe{
namespace Stmt{
class Statement;
}
}

namespace Extern {

class ModuleProxy;

/*************************************************************************/
/** The Module class.
 *
 */
class Module : public ::IAS::SYS::DynamicLibrary {
public:

	virtual ~Module() throw();

	::IAS::Lang::Interpreter::Extern::Statement *createStatement(const String& strSymbol,
	 			 	   	   	   	   	   	   	   	                 const StringList& lstParameters);

protected:
	Module(const String& strModule,
		   const String& strProxy,
		   const DM::DataFactory* pDataFactory);

	IAS_DFT_FACTORY<ModuleProxy>::PtrHolder ptrModuleProxy;

	friend class ::IAS::Factory<Module>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Module_H_ */
