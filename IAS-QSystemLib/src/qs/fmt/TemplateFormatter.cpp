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
/****************************************************************q*********/
void TemplateFormatter::write(const DM::DataObject* dmData,
		 	 	 	 	  std::ostream&       ostream,
		 	 	 	 	  QS::API::Attributes *pAttributes){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pAttributes);

	TimeSample ts(::IAS::QS::LogLevel::INSTANCE.isProfile());
    ts.start();


	const Template* pTemplate(getTemplate(pAttributes, dmData));

	Tools::Template::Arguments args(dmData);
	pTemplate->evaluate(args,ostream);

	tsrSerialization.addSample(ts);

}

/*************************************************************************/
const Tools::Template* TemplateFormatter::tryTemplate(const String& strName) {

	IAS_TRACER;

	if(hmTemplates.count(strName) == 0){

	bool bFound = false;

	for (StringList::const_iterator it = lstTemplateDirectories.begin();
			!bFound && it != lstTemplateDirectories.end(); it++) {

		IAS_LOG(::IAS::QS::LogLevel::INSTANCE.isInfo(),
				"Loading template: "<<strName<<" from "<<(*it));

		try {
			String strValue;
			InputFile::LoadString(*it + "/" + strName, strValue);
			hmTemplates[strName] = IAS_DFT_FACTORY<Tools::Template>::Create(strValue);
			bFound = true;
		} catch (SystemException& e) {
			IAS_THROW(ItemNotFoundException("Template: "+strName))
		}

	}

	}

	return hmTemplates[strName];
}

/*************************************************************************/
const Tools::Template* TemplateFormatter::getTemplate(QS::API::Attributes *pAttributes,
												const DM::DataObject* dmData){
	IAS_TRACER;


	const Tools::Template* pTemplate = NULL;

	if(pAttributes->isSet(CStrAttr)){

			const String& strTemplateName(pAttributes->getValue(CStrAttr));
			pTemplate = tryTemplate(strTemplateName);

	}else{

		URI uri(dmData->getType()->getURI());
		String strTemplateName(uri.getHost()+"/"+uri.getPath()+"/"+dmData->getType()->getName()+".temp");

		pTemplate = tryTemplate(strTemplateName);

	}

	return pTemplate;
}
/*************************************************************************/
}
}
}
