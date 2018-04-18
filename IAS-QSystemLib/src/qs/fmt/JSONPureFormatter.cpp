/*
 * File: IAS-QSystemLib/src/qs/fmt/JSONPureFormatter.cpp
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
#include "JSONPureFormatter.h"
#include<qs/log/LogLevel.h>
#include "dm/json/JSONHelper.h"

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

const String& JSONPureFormatter::CStrTypeAttr("JSONpt");
const String& JSONPureFormatter::CStrElementAttr("JSONel");
const String& JSONPureFormatter::CStrNoPure("JSONno");
/*************************************************************************/
JSONPureFormatter::JSONPureFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);
	ptrJSONHelper=IAS_DFT_FACTORY<DM::JSON::JSONHelper>::Create(pDataFactory);

}
/*************************************************************************/
JSONPureFormatter::~JSONPureFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(true,"Parsing:       "<<tsrParsing);
	//IAS_LOG(true,"Serializing:   "<<tsrSerialization);

}
/*************************************************************************/
void JSONPureFormatter::read( DM::DataObjectPtr& dmData,
  	   	   				  std::istream&       istream,
  	   	   				  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();

	IAS_CHECK_IF_NULL(pAttributes);

	const DM::Type* pType = NULL;


	if(pAttributes && pAttributes->isSet(CStrTypeAttr)){

		String strTypeURI(substitute(pAttributes->getValue(CStrTypeAttr),pAttributes));

		String::size_type iIdx = strTypeURI.find('#');
		if(iIdx == String::npos)
			IAS_THROW(BadUsageException("Cannot decode type from: ")<<CStrTypeAttr<<"="<<strTypeURI);

		String strTypeNS(strTypeURI.substr(0,iIdx));
		String strTypeName(strTypeURI.substr(iIdx+1));

		try{
			pType = pDataFactory->getType(strTypeNS,strTypeName);

		}catch(...){
			IAS_LOG(LogLevel::INSTANCE.isInfo(),CStrTypeAttr<<" is useless.");
			pAttributes->unset(CStrTypeAttr);
			pAttributes->setValue(CStrNoPure,"Y");
		}

	}else if(pAttributes && pAttributes->isSet(CStrElementAttr)){

		String strElement(substitute(pAttributes->getValue(CStrElementAttr), pAttributes));

		String::size_type iIdx = strElement.find_last_of('/');

		if(iIdx == String::npos)
				IAS_THROW(BadUsageException("Cannot decode element type from: ")<<CStrElementAttr<<"="<<strElement);

		String strElementNS(strElement.substr(0,iIdx));
		String strElementName(strElement.substr(iIdx+1));

		IAS_LOG(true, strElement);

		try{
			IAS_LOG(true, strElementNS);
			const DM::ComplexType* pRootType = pDataFactory->getType(strElementNS,DM::DataFactory::RootTypeName)->asComplexType();
			IAS_LOG(true, strElementName);
			pType = pRootType->getProperties().getProperty(strElementName)->getType();
		}catch(...){
			IAS_LOG(LogLevel::INSTANCE.isInfo(),CStrElementAttr<<" is useless.");
			pAttributes->unset(CStrElementAttr);
			pAttributes->setValue(CStrNoPure,"Y");
		}
	}

	if(istream.peek() != EOF)
		dmData=ptrJSONHelper->load(istream,pType);
	else{
		if(pType)
			dmData = pType->createDataObject();
		else{
			IAS_THROW(BadUsageException("Cannot parse input data"));
		}
	}

	tsrParsing.addSample(ts);
}
/*************************************************************************/
void JSONPureFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();


    if(pAttributes && !pAttributes->isSet(CStrElementAttr))
    	pAttributes->setValue(CStrTypeAttr,dmData->getType()->getFullName());

	ptrJSONHelper->save(ostream,dmData,!pAttributes || (pAttributes->isSet(CStrNoPure)));

	ostream.flush();

	tsrSerialization.addSample(ts);


}
/*************************************************************************/
String JSONPureFormatter::substitute(const String& strPattern, const QS::API::Attributes *pAttributes)const{
	IAS_TRACER;

	StringStream ssResult;

	for(String::const_iterator it=strPattern.begin(); it != strPattern.end(); it++){

		if(*it == '$'){

			if(++it != strPattern.end() && *it == '{'){

				String strName;

				while(++it != strPattern.end() && *it != '}')
					strName+=(*it);

				if(*it != '}')
					IAS_THROW(BadUsageException("Missing '}' in environment pattern."))

				ssResult<<pAttributes->getValue(strName);

			}

		}else{
			ssResult<<*it;
		}


	}

	return ssResult.str();
}
/*************************************************************************/
}
}
}
