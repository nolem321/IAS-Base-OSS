/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWriterForFile.cpp
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
#include "../../dm/xml/LibXMLWriterForFile.h"
#include <commonlib/commonlib.h>

#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
LibXMLWriterForFile::LibXMLWriterForFile(const String& strFileName){
	IAS_TRACER;

	xmlTextWriterPtr pXMLTextWriter = xmlNewTextWriterFilename(strFileName.c_str(), 0);

	if(pXMLTextWriter == NULL)
		IAS_THROW(XMLHelperException(String("Cannot open output file: ")+=strFileName));

	LibXMLWriter::init(pXMLTextWriter);
}
/*************************************************************************/
LibXMLWriterForFile::~LibXMLWriterForFile() throw(){
	IAS_TRACER;

}
/*************************************************************************/
}
}
}
