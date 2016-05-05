/*
 * File: IAS-ServiceManagerExe/src/sm/cmdline/GrpAttrFeature.cpp
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
#include "GrpAttrFeature.h"

#include <commonlib/commonlib.h>
#include "ParameterException.h"

namespace IAS {
namespace SM {
namespace CmdLine {
/*************************************************************************/
const Cfg::GrpAttrPairList& GrpAttrFeature::getGrpAttrPairList() const {
	IAS_TRACER;
	return lstGrpAttrs;
}
/*************************************************************************/
bool GrpAttrFeature::hasGrpAttrPairList() const {
	IAS_TRACER;
	return lstGrpAttrs.size() != 0;
}
/*************************************************************************/
void GrpAttrFeature::parse(const String& strSpec) {
	IAS_TRACER;

	String::size_type iPos=String::npos;
	String::size_type iNextStart=0;

	while(iNextStart != String::npos){

		iPos = strSpec.find_first_of(',',iNextStart);

		if (iPos == String::npos){
			parsePair(strSpec.substr(iNextStart));
			iNextStart = String::npos;
		}else{
			parsePair(strSpec.substr(iNextStart,iPos-iNextStart));
			iNextStart=iPos+1;
		}
	}

}
/*************************************************************************/
void GrpAttrFeature::parsePair(const String& strSpec) {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"ParsePair["<<strSpec<<"]");

	String::size_type iPos = strSpec.find_first_of('=');

	if(iPos == String::npos)
		IAS_THROW(ParameterException("Missing '=' in grouping attributes specification."));

	Cfg::GrpAttrPair pair(strSpec.substr(0,iPos),strSpec.substr(iPos+1));

	lstGrpAttrs.push_back(pair);

}
/*************************************************************************/
}
}
}
