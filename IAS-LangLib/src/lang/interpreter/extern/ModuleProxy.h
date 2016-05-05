/*
 * File: IAS-LangLib/src/lang/interpreter/extern/ModuleProxy.h
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
#ifndef _IAS_Lang_Interpreter_Extern_ModuleProxy_H_
#define _IAS_Lang_Interpreter_Extern_ModuleProxy_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <lang/interpreter/exe/stmt/Statement.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern{
class Statement;
/*************************************************************************/
/** The ModuleProxy class.
 *
 */
class ModuleProxy {
public:

	virtual ~ModuleProxy() throw();

	void setup(const DM::DataFactory* pDataFactory);


	::IAS::Lang::Interpreter::Extern::Statement *createStatement(const String& strSymbol,
	 			 	   	   	   	   	   	   	   	                 const StringList& lstParameters);

	void cleanUp();

protected:
	ModuleProxy();

	typedef ::IAS::Lang::Interpreter::Extern::Statement* (*StatementFactoryPtr)(const StringList& lstParameters);

private:
	const DM::DataFactory* pDataFactory;

	typedef HashMapWithStringKey< StatementFactoryPtr> SymbolToFactoryMap;
	SymbolToFactoryMap  hmSymbolToFactory;

protected:
	void registerSymbol(const String& strSymbol,
						StatementFactoryPtr pStatementFactory);

	virtual void setupImpl();
	virtual void cleanUpImpl();

	friend class ::IAS::Factory<ModuleProxy>;
};

/*************************************************************************/

extern "C" {
	typedef ModuleProxy* (*ProxyConstructorPtr)();
};

}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_ModuleProxy_H_ */
