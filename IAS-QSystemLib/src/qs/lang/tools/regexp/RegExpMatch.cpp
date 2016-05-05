/*
 * File: IAS-QSystemLib/src/qs/lang/tools/regexp/RegExpMatch.cpp
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
#include "RegExpMatch.h"
#include <qs/log/LogLevel.h>


namespace IAS {
namespace QS {
namespace Lang {
namespace Tools {
namespace RegExp {

/*************************************************************************/
RegExpMatch::RegExpMatch(const String& strRegExp, const DM::Type* pType):
		expression(strRegExp),
		strRegExp(strRegExp),
		pType(pType){
	IAS_TRACER;

}
/*************************************************************************/
RegExpMatch::~RegExpMatch() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void RegExpMatch::addXPath(unsigned int id, const String& strXPath){
	IAS_TRACER;

	tabSetters.push_back(IAS_DFT_FACTORY<SetterEntry>::Create(id,
				IAS_DFT_FACTORY<DM::Tools::Setter>::Create(strXPath,pType)));
}
/*************************************************************************/
bool RegExpMatch::match(const String& strValue, DM::DataObjectPtr& dm)const{
	IAS_TRACER;
	ias_regex_ns::match_results<String::const_iterator> match;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"["<<strRegExp<<"] match: "<<strValue);

	if(ias_regex_ns::regex_search(strValue, match, expression)){

		dm = pType->createDataObject();

		for(SettersVector::const_iterator it=tabSetters.begin();
				it != tabSetters.end(); it++){

			unsigned int id = (*it)->getId();
			if(id >= match.size())
				IAS_THROW(BadUsageException("RegExp groups index out of bound."));


			//String strValue = (match.begin());
			//String strValue2(match[id]);
			String strValue(std::string(match[id]).c_str());
			IAS_LOG(QS::LogLevel::INSTANCE.isDetailedInfo(),"value="<<strValue);
			(*it)->getSetter()->setString(dm, strValue);
		}

		return true;
	}else
		return false;

}
/*************************************************************************/
}
}
}
}
}
