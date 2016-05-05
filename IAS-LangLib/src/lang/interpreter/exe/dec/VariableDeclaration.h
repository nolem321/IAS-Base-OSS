/*
 * File: IAS-LangLib/src/lang/interpreter/exe/dec/VariableDeclaration.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_VARIABLEDECLARATION_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_VARIABLEDECLARATION_H_

#include <commonlib/commonlib.h>

#include "dm/datamodel.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Dec {

/*************************************************************************/
/** The class. */
 class VariableDeclaration {
public:

	virtual ~VariableDeclaration() throw();

	void setSeq(int iSeq);

	inline const String&    getName() const { return strName; };
	inline const DM::Type *getType() const { return pType;   };
	inline int              getSeq() const  { return iSeq;    };
	inline bool             isArray() const { return bIsArray; };
protected:
	VariableDeclaration(const String& strName,
			   	   	    const DM::Type *pType,
			   	   	    bool bIsArray);


	String           strName;
	const DM::Type *pType;
	bool             bIsArray;

	int              iSeq;
	friend class ::IAS::Factory<VariableDeclaration>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_VARIABLEDECLARATION_H_ */
