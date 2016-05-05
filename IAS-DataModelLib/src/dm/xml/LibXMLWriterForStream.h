/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWriterForStream.h
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
#ifndef _IAS_DM_XML_LibXMLWriterForStream_H_
#define _IAS_DM_XML_LibXMLWriterForStream_H_

#include "../../dm/xml/LibXMLWriter.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
/** The class. */
 class LibXMLWriterForStream  : public LibXMLWriter{
public:

	virtual ~LibXMLWriterForStream() throw();
	const char* getBufferAsCString();

protected:
	LibXMLWriterForStream(std::ostream& os);


	xmlOutputBufferPtr   pOutputBuffer;
	void cleanUp();

	static int OutputWriteCallback(void* context,  const char * buffer, int len);
	static int OutputCloseCallback(void* context);

	std::ostream& os;

	friend class ::IAS::Factory<LibXMLWriterForStream>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_DM_XML_LIBXMLWRITERFORMEMORY_H_ */
