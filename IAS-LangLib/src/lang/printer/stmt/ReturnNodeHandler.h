/*
 * File: IAS-LangLib/src/lang/printer/stmt/ReturnNodeHandler.h
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
#ifndef _IAS_AS_Lang_Printer_Stmt_ReturnNodeHandler_H_
#define _IAS_AS_Lang_Printer_Stmt_ReturnNodeHandler_H_

#include <lang/printer/CallbackSignature.h>

namespace IAS {
namespace Lang {
namespace Printer {
namespace Stmt {

/*************************************************************************/
/** The class. */
 class ReturnNodeHandler :
 public ::IAS::Lang::Printer::CallbackSignature {
public:

	virtual ~ReturnNodeHandler() throw();


	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os);
protected:
	ReturnNodeHandler()throw();
	

	friend class ::IAS::Factory<ReturnNodeHandler>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Printer_Stmt_ReturnNodeHandler_H_ */
