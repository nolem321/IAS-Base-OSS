/*
 * File: IAS-LangLib/src/lang/printer/expr/LogicalOrNodeHandler.h
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
#ifndef _IAS_AS_Lang_Printer_Expr_LogicalOrNodeHandler_H_
#define _IAS_AS_Lang_Printer_Expr_LogicalOrNodeHandler_H_

#include "LogicalBinaryOperNodeHandler.h"

namespace IAS {
namespace Lang {
namespace Printer {
namespace Expr {

/*************************************************************************/
/** The class. */
 class LogicalOrNodeHandler : public LogicalBinaryOperNodeHandler {
public:

	virtual ~LogicalOrNodeHandler() throw();


	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os);

protected:
	LogicalOrNodeHandler();
	

	friend class ::IAS::Factory<LogicalOrNodeHandler>;
};

/*************************************************************************/
}
}
}
}


#endif /* _IAS_AS_Lang_Printer_Expr_RelationalEqNODEHANDLER_H_ */
