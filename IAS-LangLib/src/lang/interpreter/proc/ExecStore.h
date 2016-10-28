/*
 * File: IAS-LangLib/src/lang/interpreter/proc/ExecStore.h
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
#ifndef _IAS_Lang_Interpreter_ExecStore_H_
#define _IAS_Lang_Interpreter_ExecStore_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "../TypeList.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec{
class TypeDefinitionNode;
}
class Model;
class ProgramNode;
}

namespace Interpreter {
namespace Exe{
class Program;
namespace Expr{
class ExprList;
}
}
namespace Extern{
class ModuleStore;
}

namespace Proc {
/*************************************************************************/
/** The ExecStore class.
 *
 */
class ExecStore {
public:

	virtual ~ExecStore() throw();

	::IAS::Lang::Interpreter::Exe::Program *getExecutable(const String& strName,
														  const TypeList& lstTypes);

	::IAS::Lang::Interpreter::Exe::Program *getExecutable(const String& strName,
														  const TypeList& lstTypes,
														  const StringList& lstSearchPath);

	::IAS::Lang::Interpreter::Exe::Program *getExecutable(const Model::ProgramNode* pProgramNode);


	const DM::Type* resolveType(const String& strType,
			                     const String& strNamespace);

	::IAS::Lang::Interpreter::Extern::ModuleStore* getExternalModules()const;

	void findAllMatches(const TypeList& lstTypes, ProgramList& lstOutput);


	const ::IAS::Lang::Model::Model* getModel()const{ return pModel;}
	const ::IAS::DM::DataFactory* getDataFactory()const{ return pDataFactory;}

protected:

	ExecStore(const ::IAS::Lang::Model::Model* pModel, ::IAS::DM::DataFactory  *pDataFactory);

	const ::IAS::Lang::Model::Model* pModel;

	::IAS::DM::DataFactory  *pDataFactory;

	bool getExecutableImpl(const String& strName,
						   const TypeList& lstTypes,
						   ::IAS::Lang::Interpreter::Exe::Program* &refOutput);


	void buildExecutable(const Model::ProgramNode* pProgramNode);
	void defineType(const Model::Dec::TypeDefinitionNode* pTypeDefinitionNode);


	typedef HashMapOfPointers< const ::IAS::Lang::Model::ProgramNode*,
							   ::IAS::Lang::Interpreter::Exe::Program >  ExecutablesMap;


	ExecutablesMap hmExecutables;

	friend class StandardProgramNodeHandler;//For this method only.
	friend class ExternalProgramNodeHandler;//For this method only.
	void registerExecutable(const Model::ProgramNode* pProgramNode,
							::IAS::Lang::Interpreter::Exe::Program *Program);

	IAS_DFT_FACTORY< ::IAS::Lang::Interpreter::Extern::ModuleStore >::PtrHolder ptrModuleStore;

	bool matchParameteres(const ::IAS::Lang::Model::ProgramNode* pProgramNode,
						  const TypeList& lstTypes)const;

	String createPrintableSignature(const TypeList& lstTypes)const;

	bool bInitialized;

	void initialize();

	friend class ::IAS::Factory<ExecStore>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Interpreter_ExecStore_H_ */
