/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/wrapper/Select.h
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
#ifndef _IAS_QS_Proc_Workers_DS_Wrapper_Select_H_
#define _IAS_QS_Proc_Workers_DS_Wrapper_Select_H_

#include <commonlib/commonlib.h>

#include "Wrapper.h"
#include "Lexer.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
namespace Wrapper {

/*************************************************************************/
/** The Select class.
 *
 */
class Select : public Wrapper{
public:

	virtual ~Select() throw();

protected:
	Select(::IAS::DS::API::Session* pSession,
		   const ::IAS::DM::Type* pType);


	::IAS::DS::API::StatementSelect::PtrHolder ptrSelect;

	SettersTable 	        	tabInputSetters;
	ResultSetSettersTable 		tabResultSetSetters;

	void parseResult(Lexer* pLexer,
			         ResultSetSettersTable& tabResultSetSetters,
					 Lexer::Token iStopToken,
					 bool bFirst);

	void parseResultAndFromAndWhere(Lexer *pLexer,
				  			  DM::DataObject* dm,
							  ResultSetSettersTable& tabResultSetSetters,
							  bool bFirst);

	bool isForUpdate()const { return bForUpdate; }

	/*************************************************************************/
	class AutoClose {
	public:

		AutoClose(IAS::DS::API::IResultSetOutput *pRSO):pRSO(pRSO){};

		~AutoClose(){
			pRSO->close();
		}

	private:
		IAS::DS::API::IResultSetOutput *pRSO;
	};

private:
	bool bForUpdate;

	friend class Factory<Select>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Proc_Workers_DS_Wrapper_Select_H_ */
