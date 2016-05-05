/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ExprResultSetter.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_ExprResultSetter_ExprResultSetter_H_
#define _IAS_AS_Lang_Interpreter_Exe_ExprResultSetter_ExprResultSetter_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr {

/*************************************************************************/
/* No factory friends => do not allocate this class.
 */

class ExprResultSetter {
public:

	virtual ~ExprResultSetter(){};
	ExprResultSetter(DM::DataObject* ptrDM,
					 const DM::Property* pProperty,
					 int iIdx = -1);

	ExprResultSetter(const ExprResultSetter& other);

	virtual void assign(DM::DataObject* dmValue);
	virtual void assignList(DM::DataObjectList& refList);

	const DM::Property* getProperty()const;

protected:

	DM::DataObject* ptrDM;
	const DM::Property* pProperty;
	int iIdx;
};
/*************************************************************************/

}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_ExprResultSetter_ExprResultSetter_H_ */
