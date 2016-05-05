/*
 * File: IAS-QSystemLib/src/qs/fmt/StringFormatter.cpp
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
#include "StringFormatter.h"
#include <qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

/*************************************************************************/
StringFormatter::StringFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

}
/*************************************************************************/
StringFormatter::~StringFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(true,"Parsing:       "<<tsrParsing);
	//IAS_LOG(true,"Serializing:   "<<tsrSerialization);

}
/*************************************************************************/
void StringFormatter::read( DM::DataObjectPtr& dmData,
  	   	   				  std::istream&       istream,
  	   	   				  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();

	StringStream ssValue;
	MiscTools::CopyStreams(istream,ssValue);

	dmData=pDataFactory->getDefaultType(DM::Type::TextType)->createDataObject(ssValue.str());

	tsrParsing.addSample(ts);
}
/*************************************************************************/
void StringFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();

    ostream<<dmData->toString();
	ostream.flush();

	tsrSerialization.addSample(ts);


}
/*************************************************************************/
}
}
}
