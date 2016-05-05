/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Update.h
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
#ifndef _IAS_QS_Proc_Workers_DS_Wrapper_Update_H_
#define _IAS_QS_Proc_Workers_DS_Wrapper_Update_H_

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
/** The Update class.
 *
 */
class Update : public Wrapper{
public:

	virtual ~Update() throw();

	virtual void execute(::IAS::DM::DataObjectPtr& dm);

protected:
	Update(::IAS::DS::API::Session* pSession,
		   Lexer *pLexer,
		   const ::IAS::DM::DataFactory* pDataFactory,
		   ::IAS::DM::DataObject* dm);


	::IAS::DS::API::StatementUpdate::PtrHolder ptrUpdate;
	SettersTable 	                           tabInputSetters;

	friend class Factory<Update>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Proc_Workers_DS_Wrapper_Update_H_ */
