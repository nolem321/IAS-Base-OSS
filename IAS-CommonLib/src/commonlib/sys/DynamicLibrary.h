/*
 * File: IAS-CommonLib/src/commonlib/sys/DynamicLibrary.h
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
#ifndef _IAS_SYS_DYNAMICLIBRARY_H_
#define _IAS_SYS_DYNAMICLIBRARY_H_

#include <dlfcn.h>
#include "../types.h"


namespace IAS {
namespace SYS {


/*************************************************************************/
/** The class. */
 class DynamicLibrary {
public:

	DynamicLibrary(const String& strFileName, int  iMode = RTLD_LAZY | RTLD_LOCAL);
	virtual ~DynamicLibrary()throw();

	void* getSymbol(const String& strSymbolName);

protected:


	void* pHandle;
	String strFileName;
};

/*************************************************************************/
}
}

#endif /* _IAS_SYS_DYNAMICLIBRARY_H_ */
