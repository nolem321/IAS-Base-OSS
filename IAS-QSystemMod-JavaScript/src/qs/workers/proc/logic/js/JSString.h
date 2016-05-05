/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/JSString.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_JS_JSString_H_
#define _IAS_QS_Workers_Proc_Logic_JS_JSString_H_

#include <commonlib/commonlib.h>

#include "jsapi.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS {


/*************************************************************************/
/** The JSString class.
 *
 */
class JSString {
public:

	JSContext * const cx;
	jschar *pData;
	size_t iLength;

public:
	JSString(JSContext *cx) :
			cx(cx), pData(NULL), iLength(0) {
	}
	~JSString() {
		if(pData)
		delete pData;
	}

	void operator=(const String& strValue) {
		inflateString(strValue);
	}

	void load(std::istream& is){
		iLength=0;

		//TODO use buffer!
		pData = new jschar[10000];

		std::istream::char_type c;

		while( (c=is.get()) != EOF){
			pData[iLength++] = (unsigned char) c;
			if(iLength > 10000)
				IAS_THROW(InternalException("//TODO use buffer!"))
		}

		pData[iLength] = 0;
	}

	const jschar *getChars() const {
		return pData;
	}

	size_t length() const {
		return iLength;
	}


protected:

	void inflateString(const String& strValue){

		IAS_TRACER;

		pData = new jschar[strValue.length() + 1];
		if (!pData)
		  IAS_THROW(InternalException("chars == null"));

		iLength=strValue.length();

		for(int iIdx=0; iIdx < iLength; iIdx++)
			pData[iIdx] = (unsigned char) strValue[iIdx];

		pData[iLength] = 0;

	}
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_JS_JSString_H_ */
