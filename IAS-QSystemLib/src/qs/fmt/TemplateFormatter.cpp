/*
 * File: IAS-QSystemLib/src/qs/fmt/TemplateFormatter.cpp
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
#include "TemplateFormatter.h"
#include<qs/log/LogLevel.h>
#include "dm/json/JSONHelper.h"

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

const String& TemplateFormatter::CStrAttr("Template");
const String& TemplateFormatter::CEnvTemplateDir("IAS_QS_TEMPL_DIRS");

/*************************************************************************/
TemplateFormatter::TemplateFormatter(const DM::DataFactory* pDataFactory):pDataFactory(pDataFactory){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

	EnvTools::GetEnvTokenized(CEnvTemplateDir,lstTemplateDirectories,':');
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Number or template dirs: "<<lstTemplateDirectories.size());
}
/*************************************************************************/
TemplateFormatter::~TemplateFormatter() throw(){
	IAS_TRACER;

	//IAS_LOG(true,"Parsing:       "<<tsrParsing);
	//IAS_LOG(true,"Serializing:   "<<tsrSerialization);

}
/*************************************************************************/
void TemplateFormatter::read( DM::DataObjectPtr& dmData,
  	   	   				  std::istream&       istream,
  	   	   				  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	IAS_THROW(BadUsageException("Cannot read from the template formatter."))
}
/*************************************************************************/
class Arguments : public Template::Arguments{

	public:

	Arguments(const DM::DataObject* dmData):dmData(dmData){
		IAS_TRACER;
		IAS_CHECK_IF_NULL(dmData);
	};

	virtual ~Arguments(){};

	virtual const String& get(const String& strKey) const{
		IAS_TRACER;

		//TODO revise API, however single instance will not be called by more than one thread
		//and the Template class does not preserve value, so it is safe for now.

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"key: "<<strKey);

		if(hmValues.count(strKey)==0)
			const_cast<Arguments*>(this)->hmValues[strKey] = dmData->getString(strKey);


		return hmValues.at(strKey);
	}

	protected:
	  const DM::DataObject* dmData;
	  HashMapWithStringKey<String> hmValues;
};
/****************************************************************q*********/
void TemplateFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pAttributes);

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();


	const String& strTemplateName(pAttributes->getValue(CStrAttr));
	const Template* pTemplate(getTemplate(strTemplateName));

	Arguments args(dmData);
	pTemplate->evaluate(args,ostream);

	tsrSerialization.addSample(ts);

}
/*************************************************************************/
const Template* TemplateFormatter::getTemplate(const String& strTemplateName){
	IAS_TRACER;

	if(hmTemplates.count(strTemplateName) == 0){

		bool bFound = false;
		for(StringList::const_iterator it=lstTemplateDirectories.begin();!bFound && it != lstTemplateDirectories.end(); it++){

			try{
				String strValue;
				InputFile::LoadString(*it+"/"+strTemplateName,strValue);
				hmTemplates[strTemplateName]=IAS_DFT_FACTORY<Template>::Create(strValue);
				bFound=true;
			}catch(SystemException& e){	}

		}

		if(!bFound)
			IAS_THROW(ItemNotFoundException()<<"Template: "<<strTemplateName);
	}

	return hmTemplates[strTemplateName];
}
/*************************************************************************/
}
}
}
