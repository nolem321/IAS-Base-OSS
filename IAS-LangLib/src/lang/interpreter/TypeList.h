/*
 * File: IAS-LangLib/src/lang/interpreter/TypeList.h
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
#ifndef _IAS_Lang_Interpreter_TypeList_H_
#define _IAS_Lang_Interpreter_TypeList_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include <vector>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe{
class Program;
namespace Expr{
class ExprList;
}
}

/*************************************************************************/

typedef std::list< ::IAS::Lang::Interpreter::Exe::Program * > ProgramList;

/*************************************************************************/
/** The TypeList class.
 *
 */
class TypeList {

	public:
		typedef std::vector< const ::IAS::DM::Type* > TypeVector;

		typedef TypeVector::const_iterator const_iterator;


		inline const_iterator begin() const {return lstTypes.begin();};
		inline const_iterator end()   const {return lstTypes.end();};
		inline bool           isAnyThing()const{return bAnyThing; };

		const ::IAS::DM::Type* operator[](size_t iIdx)const;



		size_t size()const {return lstTypes.size(); };


		TypeList(bool bAnyThing=true);

		TypeList(const Exe::Expr::ExprList* pExprList);

		void append(const IAS::DM::Type* pType);

	protected:

	bool bAnyThing;
	TypeVector lstTypes;
};

/*************************************************************************/
}
}
}


#endif /* _IAS_Lang_Interpreter_TypeList_H_ */
