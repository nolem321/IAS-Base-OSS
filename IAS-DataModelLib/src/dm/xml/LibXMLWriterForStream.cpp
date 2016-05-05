/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWriterForStream.cpp
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
#include "../../dm/xml/LibXMLWriterForStream.h"
#include <commonlib/commonlib.h>
#include "dm/log/LogLevel.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
int LibXMLWriterForStream::OutputWriteCallback(void* context,  const char * buffer, int len){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(context);
	LibXMLWriterForStream *object=static_cast<LibXMLWriterForStream*>(context);
	object->os.write(buffer,len);

	return len;
}
/*************************************************************************/
int LibXMLWriterForStream::OutputCloseCallback(void* context){
	IAS_TRACER;
	LibXMLWriterForStream *object=static_cast<LibXMLWriterForStream*>(context);
	object->os.flush();
	return 0;
}
/*************************************************************************/
LibXMLWriterForStream::LibXMLWriterForStream(std::ostream& os):os(os){

	IAS_TRACER;
	pOutputBuffer = xmlOutputBufferCreateIO(&(LibXMLWriterForStream::OutputWriteCallback),
											&(LibXMLWriterForStream::OutputCloseCallback),
											(void*)this,NULL);
		if(pOutputBuffer == NULL)
	          IAS_THROW(XMLHelperException("xmlOutputBufferCreateIO failed."));

	xmlTextWriterPtr pXMLTextWriter = xmlNewTextWriter(pOutputBuffer);
	LibXMLWriter::init(pXMLTextWriter);
}
/*************************************************************************/
LibXMLWriterForStream::~LibXMLWriterForStream() throw(){
	IAS_TRACER;
	cleanUp();
}
/*************************************************************************/
void LibXMLWriterForStream::cleanUp(){
	IAS_TRACER;
	LibXMLWriter::cleanUp();
	//TODO nothing to clean here ?
}
/*************************************************************************/
}
}
}
