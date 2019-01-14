/*
 * File: IAS-QSystemLib/src/qs/fmt/RawFormatter.cpp
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
#include "RawFormatter.h"
#include <qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
RawFormatter::RawFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

}
/*************************************************************************/
RawFormatter::~RawFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(true,"Parsing:       "<<tsrParsing);
	//IAS_LOG(true,"Serializing:   "<<tsrSerialization);

}

typedef std::basic_iostream<char> ByteStream;


/*************************************************************************/
void RawFormatter::read( DM::DataObjectPtr& dmData,
  	   	   				  std::istream&       istream,
  	   	   				  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();


	istream.seekg (0, istream.end);
	DM::RawContent aRawContent(istream.tellg());
	istream.seekg (0, istream.beg);

  if(aRawContent.getSize())
	  istream.read(aRawContent.getBuffer<char>(),aRawContent.getSize());

	dmData=pDataFactory->getDefaultType(DM::Type::RawType)->createDataObject();
	dmData->setRaw(&aRawContent);

	tsrParsing.addSample(ts);
}
/*************************************************************************/
void RawFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();

    DM::RawContent aRawContent;
    dmData->toRaw(&aRawContent);

    if(aRawContent.getSize())
      ostream.write(aRawContent.getBuffer<char>(),aRawContent.getSize());

	  ostream.flush();

	tsrSerialization.addSample(ts);


}
/*************************************************************************/
}
}
}
