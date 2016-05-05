/*
 * File: IAS-LangLib/src/lang/export/text/CallbackSignature.h
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
#ifndef _IAS_AS_Lang_Export_Text_CALLBACKSIGNATURE_H_
#define _IAS_AS_Lang_Export_Text_CALLBACKSIGNATURE_H_

#include <commonlib/commonlib.h>
#include "lang/model/Node.h"

#include <dm/datamodel.h>
#include <lang/interpreter/TypeList.h>
#include "SourceStore.h"

namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
class SourceStore;
/*************************************************************************/

/** The class. */
 class CallbackSignature {
public:

	virtual ~CallbackSignature(){};

	struct CallbackCtx{
		CallbackCtx(bool bDeclarationOnly,
					SourceStore* pSourceStore);
		int    iIndent;
		bool   bDeclarationOnly;
		SourceStore          *getSourceStore() const;

	protected:

		SourceStore*  pSourceStore;
	};

	struct Result{
		StringStream               ssOutput;
	};

	virtual void call(const Model::Node* pNode,
						CallbackCtx *pCtx,
						Result& aResult)=0;

protected:

	void printIndent(CallbackCtx *pCtx,
				     CallbackSignature::Result& aResult);

	void printType(CallbackCtx *pCtx,
				   CallbackSignature::Result& aResult,
				   const String& strType,
				   const String& strNamespace);

	void printFunCall(CallbackCtx *pCtx,
					  CallbackSignature::Result& aResult,
					  const String& strFunName,
					  const String& strArgs);

	void printKeyword(CallbackSignature::Result& aResult,
				   	  const String& strKeyword);

	friend class ::IAS::Factory<CallbackSignature>;
};

/*************************************************************************/
}
}
}
}


#endif /* _IAS_AS_Lang_Export_Text_CALLBACKREGISTER_H_ */
