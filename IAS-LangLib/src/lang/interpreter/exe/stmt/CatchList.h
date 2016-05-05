/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/CatchList.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Stmt_CatchList_H_
#define _IAS_Lang_Interpreter_Exe_Stmt_CatchList_H_

#include <commonlib/commonlib.h>

#include <list>
#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

class Catch;

/*************************************************************************/
/** The CatchList class.
 *
 */
class CatchList {
public:

	virtual ~CatchList() throw();

	void addCatch(Catch* pCatch);
	bool match(const DM::Type* pType, Catch* &refPtrCatch)const;

protected:
	CatchList();

	typedef std::list<Catch*>   CatchSectionsList;
	CatchSectionsList           lstCatchSections;

	IAS_DFT_FACTORY<Catch>::PtrHoldersCollection phcCatches;
	friend class ::IAS::Factory<CatchList>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Stmt_CatchList_H_ */
