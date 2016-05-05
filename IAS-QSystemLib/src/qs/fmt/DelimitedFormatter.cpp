/*
 * File: IAS-QSystemLib/src/qs/fmt/DelimitedFormatter.cpp
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
#include "DelimitedFormatter.h"
#include<qs/log/LogLevel.h>
#include "dm/json/JSONHelper.h"

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

const String& DelimitedFormatter::CStrAttr("DELpt");

/*************************************************************************/
DelimitedFormatter::DelimitedFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);
	ptrJSONHelper=IAS_DFT_FACTORY<DM::JSON::JSONHelper>::Create(pDataFactory);

}
/*************************************************************************/
DelimitedFormatter::~DelimitedFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(true,"Parsing:       "<<tsrParsing);
	//IAS_LOG(true,"Serializing:   "<<tsrSerialization);

}
/*************************************************************************/
/* TODO (L) more functional praser: quotes \" "" etc.
 *
 */
class Reader {
public:
	Reader(std::istream& is):
		is(is),
		bIsSet(true){};

	void nextValue(){

		StringStream ssValue;

		bool bEnd=false;
		bIsSet=false;

		while(is.good() && !bEnd){

			int c=is.get();

			if(c == ',' || c == EOF){
				bEnd=true;
			}else{
				if(c == '\\'){
					c=is.get();
				}else{
					ssValue<<(char)c;
				}
				bIsSet=true;
			}
		}

		strValue=ssValue.str();
		IAS_LOG(QS::LogLevel::INSTANCE.isDetailedInfo(),"value=["<<strValue<<"]"<<bIsSet)
	}

	void read(DM::DataObject* dmData){
		nextValue();
		readImpl(dmData);
	}

protected:

	void readImpl(DM::DataObject* dmData){

		const DM::Type* pType =  dmData->getType();

		if(pType->isDataObjectType()){

			const DM::PropertyList& lstProperties(pType->asComplexType()->getProperties());

			for(int iIdx=0; iIdx<lstProperties.getSize(); iIdx++){
				const DM::Property* pProperty=lstProperties[iIdx];
				if(pProperty->isMulti())
					IAS_THROW(BadUsageException("Cannot serialize arrays to delimited formats."));

				if(iIdx)
					nextValue();

				if(isSet()||pProperty->getType()->isDataObjectType()){
					DM::DataObject* dmNew=dmData->createDataObject(pProperty);
					readImpl(dmNew);
				}

			}

		}else{

			if(isSet())
				dmData->setString(getValue());

		}
	}



	std::istream& is;

	bool bIsSet;
	String strValue;

	const String& getValue()const{ return strValue; };
	bool isSet()const{return bIsSet; };

};
/*************************************************************************/
void DelimitedFormatter::read( DM::DataObjectPtr& dmData,
  	   	   				  std::istream&       istream,
  	   	   				  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
	ts.start();

	IAS_CHECK_IF_NULL(pAttributes);

	try{

		const String& strTypeURI (pAttributes->getValue(CStrAttr));

		String::size_type iIdx = strTypeURI.find('#');

		if(iIdx == String::npos)
			IAS_THROW(BadUsageException("Cannot decode type from: ")<<CStrAttr<<"="<<strTypeURI);

		String strTypeNS(strTypeURI.substr(0,iIdx));
		String strTypeName(strTypeURI.substr(iIdx+1));

		const DM::Type* pType=pDataFactory->getType(strTypeNS,strTypeName);

		Reader reader(istream);
		dmData=pType->createDataObject();
		reader.read(dmData);

	}catch(Exception& e){
		dmData=pDataFactory->getDefaultType(DM::Type::TextType)->createDataObject(e.toString());
	}
	tsrParsing.addSample(ts);
}

/*************************************************************************/
class Writer {
public:
	Writer(std::ostream& os):os(os),bFirst(true){};

	void write(const DM::Type* pType){

		if(pType->isDataObjectType()){
			const DM::PropertyList& lstProperties(pType->asComplexType()->getProperties());

			for(int iIdx=0; iIdx<lstProperties.getSize(); iIdx++){
				const DM::Property* pProperty=lstProperties[iIdx];
				if(pProperty->isMulti())
					IAS_THROW(BadUsageException("Cannot serialize arrays to delimited formats."));

				write(pProperty->getType());
			}
		}else{
			if (!bFirst)
				os << ",";
			else
				bFirst = false;
		}
	}

	void write(const DM::DataObject* dmData){

		const DM::Type* pType =  dmData->getType();

		if(pType->isDataObjectType()){
			const DM::PropertyList& lstProperties(pType->asComplexType()->getProperties());

			for(int iIdx=0; iIdx<lstProperties.getSize(); iIdx++){
				const DM::Property* pProperty=lstProperties[iIdx];
				if(pProperty->isMulti())
					IAS_THROW(BadUsageException("Cannot serialize arrays to delimited formats."));

				if(dmData->isSet(pProperty)){
					const DM::DataObject* dmValue(dmData->getDataObject(pProperty));
					if(pProperty->getType()->equals(dmValue->getType()))
							write(dmData->getDataObject(pProperty));
					else
						IAS_THROW(BadUsageException("Cannot serialize property subtypes to delimited formats."));
				}else
					write(pProperty->getType());
			}
		}else{

			if (!bFirst)
				os << ",";
			else
				bFirst = false;

			String strValue(dmData->toString());
			for(String::const_iterator it=strValue.begin(); it != strValue.end(); it++){
				if(*it != ',')
					os<<(*it);
				else
					os<<"\\,";
			}
		}
	}

protected:
	std::ostream& os;
	bool bFirst;
};
/*************************************************************************/
void DelimitedFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();

    Writer writer(ostream);
    writer.write(dmData);

    ostream<<"\n";
	ostream.flush();

	tsrSerialization.addSample(ts);

}
/*************************************************************************/
}
}
}
