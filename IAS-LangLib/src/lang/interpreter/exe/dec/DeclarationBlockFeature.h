/*
 * File: IAS-LangLib/src/lang/interpreter/exe/dec/DeclarationBlockFeature.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_DeclarationBlockFeature_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_DeclarationBlockFeature_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "VariableDeclaration.h"
#include <list>

#include "TypeCreator.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Dec {

/*************************************************************************/
/** The class. */
 class DeclarationBlockFeature : protected TypeCreator{
public:

	virtual ~DeclarationBlockFeature() throw();

	void addVariable(Exe::Dec::VariableDeclaration* pVariableDeclaration){
		addProperty(pVariableDeclaration);
	}

	bool hasVariable(const String& strName) const{
		return hasProperty(strName);
	}

	const DM::Property* getVariableProperty(const String& strName) const{
		return getProperty(strName);
	}

	virtual void declareBlockVariables(DM::DataFactory *pDataFactory);

	DM::DataObject* createAndInitializeVariables() const;

	virtual const DM::Type *getType() const;

protected:
	DeclarationBlockFeature()throw();

public:
	/*************************************************************************/
	class AutoPopUp {

	public:

		AutoPopUp(Context *pCtx, DM::DataObject *pVariables) throw();
		~AutoPopUp();

	private:
		Context *pCtx;
		friend class ::IAS::Factory<DeclarationBlockFeature>;
	};
	friend class ::IAS::Factory<DeclarationBlockFeature>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENTLISTS_H_ */
