/*
 * File: IAS-LangLib/src/lang/interpreter/exe/dec/TypeCreator.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_TypeCreator_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_TypeCreator_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "VariableDeclaration.h"
#include <list>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Dec {

/*************************************************************************/
/** The class. */
 class TypeCreator {
public:

	virtual ~TypeCreator() throw();

	void addProperty(Exe::Dec::VariableDeclaration* pVariableDeclaration);

	bool hasProperty(const String& strName) const;
	const DM::Property* getProperty(const String& strName) const;


	virtual void declareType(DM::DataFactory *pDataFactory,
							 const String& strName,
							 const String& strNamespace,
							 const DM::Type* pBaseType=0);


	const DM::Type *getType() const;


protected:
	TypeCreator()throw();

	HashMapStringToPointer<Exe::Dec::VariableDeclaration> hmVariables;
	int iSeq;

	DM::Type *pType;

public:
	friend class ::IAS::Factory<TypeCreator>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENTLISTS_H_ */
