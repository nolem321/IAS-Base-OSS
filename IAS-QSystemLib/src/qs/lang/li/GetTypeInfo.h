/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ti/GetTypeInfo.h
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
#ifndef _IAS_QS_Lang_LI_GetTypeInfo_H_
#define _IAS_QS_Lang_LI_GetTypeInfo_H_

#include <lang/interpreter/extern/Statement.h>
#include <lang/interpreter/exe/Context.h>
#include <set>

#include <org/invenireaude/qsystem/typeinfo/TypeBase.h>

namespace IAS {
namespace QS {
namespace Lang {
namespace LI {
/*************************************************************************/
/** The GetTypeInfo class.
 *
 */
class GetTypeInfo : public ::IAS::Lang::Interpreter::Extern::Statement {
public:

	virtual ~GetTypeInfo() throw();

	/** Creates an instance. */
	static Statement* Create(const StringList& lstParamaters);

protected:

	virtual void executeExternal(::IAS::Lang::Interpreter::Exe::Context *pCtx) const;

	GetTypeInfo(const StringList& lstParamaters);

	class Cache {

	public:
		Cache();
		void init(const DM::DataFactory* pDataFactory);

		typedef std::set<const DM::Type*> TypesSet;
		typedef std::map<const DM::Type*, TypesSet> TypesToSetMap;

		TypesToSetMap hmDirectExtensions;
		TypesToSetMap hmAllExtensions;
		TypesToSetMap hmReferences;

		void getDirectExtensions(org::invenireaude::qsystem::typeinfo::TypeBase* pResult, const DM::Type* pType);
		void getAllExtensions(org::invenireaude::qsystem::typeinfo::TypeBase* pResult, const DM::Type* pType);
		void getReferences(org::invenireaude::qsystem::typeinfo::TypeBase* pResult, const DM::Type* pType);

	protected:
		void buildExtensions(const DM::DataFactory* pDataFactory);
		void buildReferences(const DM::DataFactory* pDataFactory);


		Mutex mutex;
		bool bInitialized;
	};

	static Cache TheCache;
	friend class ::IAS::Factory<GetTypeInfo>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Extern_Std_GetTypeInfo_H_ */
