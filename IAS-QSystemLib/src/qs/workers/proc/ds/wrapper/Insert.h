/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Insert.h
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
#ifndef _IAS_QS_Proc_Workers_DS_Wrapper_Insert_H_
#define _IAS_QS_Proc_Workers_DS_Wrapper_Insert_H_

#include <commonlib/commonlib.h>

#include "Wrapper.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {
class Lexer;
/*************************************************************************/
/** The Insert class.
 *
 */
class Insert : public Wrapper{
public:

	virtual ~Insert() throw();

	virtual void execute(::IAS::DM::DataObjectPtr& dm);

protected:
	Insert(::IAS::DS::API::Session* pSession,
		   Lexer *pLexer,
		   const ::IAS::DM::DataFactory* pDataFactory,
		   ::IAS::DM::DataObject* dm);


	::IAS::DS::API::StatementInsert::PtrHolder ptrInsert;

	SettersTable 		tabInputSetters;

	void parseInput(Lexer *pLexer);

	friend class Factory<Insert>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Proc_Workers_DS_Wrapper_Insert_H_ */
