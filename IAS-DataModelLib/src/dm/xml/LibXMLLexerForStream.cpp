/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLLexerForStream.cpp
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
#include "../../dm/xml/LibXMLLexerForStream.h"

#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"
#include "../../dm/xml/LibXMLWrapper.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
LibXMLLexerForStream::LibXMLLexerForStream(std::istream& is):is(is){
	IAS_TRACER;

	LibXMLWrapper::GetInstance();

	//TODO encoding & options
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"XML for stream, this="<<(void*)this);

	xmlTextReaderPtr pXMLTextReader =
			xmlReaderForIO(&(LibXMLLexerForStream::OutputReadCallback),
						   &(LibXMLLexerForStream::OutputCloseCallback),
						   (void*)this, NULL, NULL, 0);

	if(pXMLTextReader == NULL)
		IAS_THROW(XMLHelperException(String("Cannot create xmlReaderForMemory.")));

	setup(pXMLTextReader);
}
/*************************************************************************/
LibXMLLexerForStream::~LibXMLLexerForStream() throw(){
	IAS_TRACER;
}
/*************************************************************************/
int LibXMLLexerForStream::OutputReadCallback(void* context,  char * buffer, int len){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(context);
	LibXMLLexerForStream *object=static_cast<LibXMLLexerForStream*>(context);

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"object="<<context<<", len="<<len);

	object->is.read(buffer,len);

	return object->is.gcount();
}
/*************************************************************************/
int LibXMLLexerForStream::OutputCloseCallback(void* context){
	IAS_TRACER;

	return 0;
}
/*************************************************************************/
}
}
}
