/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWriterForMemory.cpp
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
#include "../../dm/xml/LibXMLWriterForMemory.h"
#include <commonlib/commonlib.h>
#include "dm/log/LogLevel.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
LibXMLWriterForMemory::LibXMLWriterForMemory(){

	IAS_TRACER;
	pXMLBuffer = xmlBufferCreate();
		if(pXMLBuffer == NULL)
	          IAS_THROW(XMLHelperException("xmlBufferCreate failed."));

	xmlTextWriterPtr pXMLTextWriter = xmlNewTextWriterMemory(pXMLBuffer, 0);
	LibXMLWriter::init(pXMLTextWriter);
}
/*************************************************************************/
LibXMLWriterForMemory::~LibXMLWriterForMemory() throw(){
	IAS_TRACER;
	cleanUp();
}
/*************************************************************************/
void LibXMLWriterForMemory::cleanUp(){
	IAS_TRACER;
	LibXMLWriter::cleanUp();
	if(pXMLBuffer==NULL)
		return;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"xmlBufferFree["<<(void*)pXMLBuffer<<"]");
	xmlBufferFree(pXMLBuffer);
	pXMLBuffer=NULL;
}
/*************************************************************************/
const char* LibXMLWriterForMemory::getBufferAsCString(){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(xmlBufferContent(pXMLBuffer));
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"XML["<<(const char*)xmlBufferContent(pXMLBuffer)<<"]");
	return (const char*)xmlBufferContent(pXMLBuffer);
}
/*************************************************************************/
}
}
}
