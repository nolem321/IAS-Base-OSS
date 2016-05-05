/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLLexerForFile.h
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
#ifndef _IAS_DM_XML_LibXMLLexerForFile_H_
#define _IAS_DM_XML_LibXMLLexerForFile_H_

#include <commonlib/commonlib.h>

#include "../../dm/xml/LibXMLLexer.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
/** The LibXMLLexerForFile class.
 *
 */
class LibXMLLexerForFile : public LibXMLLexer{
public:

	virtual ~LibXMLLexerForFile() throw();


protected:
	LibXMLLexerForFile(const String& strFileName);

	friend class Factory<LibXMLLexerForFile>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_LibXMLLexerForFile_H_ */
