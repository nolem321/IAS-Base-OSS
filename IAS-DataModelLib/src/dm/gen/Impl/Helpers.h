/*
 * File: IAS-DataModelLib/src/dm/gen/Impl/Helpers.h
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
#ifndef _IAS_DM_Gen_Helpers_H_
#define _IAS_DM_Gen_Helpers_H_

#include <commonlib/commonlib.h>

#include <vector>

namespace IAS {
namespace DM {
namespace Gen {
namespace Impl {
/*************************************************************************/
class Helpers {
public:

	static void URIToFilePath(const String& strURI, String& strOutput);
	static void URIToFilePath(const StringList& lstNSParts, String& strOutput);
	static String URIToFilePath(const StringList& lstNSParts);
	static String URIToFilePath(const String& strURI);

	static void URIToList(const String& strURI, StringList& lstOutput);

	static void URIToPrefix(const String& strURI, String& strOutput);
	static void URIToPrefix(const StringList& lstNSParts, String& strOutput);
	static String URIToPrefix(const StringList& lstNSParts);
	static String URIToPrefix(const String& strURI);

	static void PropertyToMethod(const String& strPrefix, const String& strProperty, String& strOutput);
	static String PropertyToMethod(const String& strPrefix, const String& strProperty);

	static String convertToSymbol(const String& strText, char cEscape = '_', bool bUpper=false);

private:
	static void ImproveURI(const String& strURI, String& strOutput);
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DMWrap_Cpp_HELPERS_H_ */
