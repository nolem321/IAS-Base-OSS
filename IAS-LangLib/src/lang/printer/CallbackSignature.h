/*
 * File: IAS-LangLib/src/lang/printer/CallbackSignature.h
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
#ifndef _IAS_AS_Lang_Printer_CALLBACKSIGNATURE_H_
#define _IAS_AS_Lang_Printer_CALLBACKSIGNATURE_H_

#include <commonlib/commonlib.h>
#include "lang/model/Node.h"

namespace IAS {
namespace Lang {
namespace Printer {

/*************************************************************************/

/** The class. */
 class CallbackSignature {
public:

	virtual ~CallbackSignature();
	struct CallbackCtx{
		CallbackCtx():iIndent(0){};
		int iIndent;
	};

	virtual void call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os)=0;

protected:

	void printIndent(CallbackCtx *pCtx, std::ostream& os);

	friend class ::IAS::Factory<CallbackSignature>;
};

/*************************************************************************/
}
}
}


#endif /* _IAS_AS_Lang_Printer_CALLBACKREGISTER_H_ */
