/*
 * File: IAS-QSystemLib/src/qs/fmt/URLEncodeFormatter.cpp
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
#include "URLEncodeFormatter.h"
#include <qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

const String& URLEncodeFormatter::CStrAttr("URLpt");

/*************************************************************************/
URLEncodeFormatter::URLEncodeFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);
	ptrURLEncodeHelper=IAS_DFT_FACTORY<DM::URLEnc::URLEncodeHelper>::Create(pDataFactory);

}
/*************************************************************************/
URLEncodeFormatter::~URLEncodeFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(true,"Parsing:       "<<tsrParsing);
	//IAS_LOG(true,"Serializing:   "<<tsrSerialization);

}
/*************************************************************************/
void URLEncodeFormatter::read( DM::DataObjectPtr& dmData,
  	   	   				  std::istream&       istream,
  	   	   				  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();

	IAS_CHECK_IF_NULL(pAttributes);

	const String& strTypeURI (pAttributes->getValue(CStrAttr));

	String::size_type iIdx = strTypeURI.find('#');

	if(iIdx == String::npos)
		IAS_THROW(BadUsageException("Cannot decode type from: ")<<CStrAttr<<"="<<strTypeURI);

	String strTypeNS(strTypeURI.substr(0,iIdx));
	String strTypeName(strTypeURI.substr(iIdx+1));

	const DM::Type* pType=pDataFactory->getType(strTypeNS,strTypeName);


	if(istream.peek() != EOF) {
		dmData=ptrURLEncodeHelper->load(istream,pType);
  } else {
		dmData = pType->createDataObject();
  }

	tsrParsing.addSample(ts);
}
/*************************************************************************/
void URLEncodeFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();


    if(pAttributes)
    	pAttributes->setValue(CStrAttr,dmData->getType()->getFullName());

	ptrURLEncodeHelper->save(ostream,dmData,false);

	ostream.flush();

	tsrSerialization.addSample(ts);


}
/*************************************************************************/
}
}
}
