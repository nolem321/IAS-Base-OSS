/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/Helper.cpp
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
#include "Helper.h"

#include <qs/log/sps/LogLevel.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

const String Helper::CAttrNamePID("IAS_SPS_PID");
const String Helper::CAttrNameSEQ("IAS_SPS_SEQ");

/*************************************************************************/
void Helper::UpdateContext(org::invenireaude::qsystem::workers::Context *dmContext,
		           	   	  const String& strPID,
		           	   	  int   iSeq){

	IAS_TRACER;

		::org::invenireaude::qsystem::workers::Ext::AttributeList& lstAttributes(dmContext->getAttributesList());


		bool bPIDFound=false;
		bool bSeqFound=false;

		for(int iIdx=0;iIdx<lstAttributes.size();iIdx++){


			if(lstAttributes.at(iIdx)->getName().compare(CAttrNamePID) == 0){
				lstAttributes.at(iIdx)->setValue(strPID);
				bPIDFound=true;
			}

			if(lstAttributes.at(iIdx)->getName().compare(CAttrNameSEQ) == 0){
				lstAttributes.at(iIdx)->setValue(TypeTools::IntToString(iSeq));
				bSeqFound=true;
			}

		}

		if(!bPIDFound){
			::org::invenireaude::qsystem::workers::Attribute* pAttribute = dmContext->createAttributes();
			pAttribute->setName(CAttrNamePID);
			pAttribute->setValue(strPID);
		}

		if(!bSeqFound){
			::org::invenireaude::qsystem::workers::Attribute* pAttribute = dmContext->createAttributes();
			pAttribute->setName(CAttrNameSEQ);
			pAttribute->setValue(TypeTools::IntToString(iSeq));
		}

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"PID="<<strPID<<", Seq="<<iSeq);
}
/*************************************************************************/

void Helper::RetrieveContext(const org::invenireaude::qsystem::workers::Context *dmContext,
			           	  	String& strPID,
			           	   	int&    iSeq){
	IAS_TRACER;

	const workers::Ext::AttributeList& lstAttributes(dmContext->getAttributesList());

	for(int iIdx=0;iIdx<lstAttributes.size();iIdx++){
		if(lstAttributes.at(iIdx)->getName().compare(CAttrNamePID) == 0)
			strPID=lstAttributes.at(iIdx)->getValue();

		if(lstAttributes.at(iIdx)->getName().compare(CAttrNameSEQ) == 0)
			iSeq=TypeTools::StringToInt(lstAttributes.at(iIdx)->getValue());

	}

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"PID="<<strPID<<", Seq="<<iSeq);

}
/*************************************************************************/
}
}
}
}
}
}
