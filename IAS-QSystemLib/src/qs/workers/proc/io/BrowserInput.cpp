/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/BrowserInput.cpp
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
#include "BrowserInput.h"
#include<qs/log/LogLevel.h>
#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
BrowserInput::BrowserInput(const ::org::invenireaude::qsystem::workers::io::BrowserInput* dmParameters,
						   WCM::WorkContextManager* pWorkContextManager):
		Common(dmParameters,pWorkContextManager),
		iRecycleMode(RM_Never){

	IAS_TRACER;

	ptrBrowser=getSession()->createBrowser(destination);

	if(dmParameters->isSetAutoRecycle())
		iRecycleMode=StringToRecycleMode(dmParameters->getAutoRecycle());

}
/*************************************************************************/
BrowserInput::~BrowserInput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
unsigned int BrowserInput::skip(unsigned int iOffset){
	IAS_TRACER;

	return ptrBrowser->skip(iOffset);
}
/*************************************************************************/
API::Message* BrowserInput::get(API::Attributes* pAttributes, int iTimeout){
	IAS_TRACER;

	if(iRecycleMode == RM_Always)
		ptrBrowser=getSession()->createBrowser(destination);

	try{
		return ptrBrowser->receive((iTimeout == Input::CDefaultTimeout ? this->iTimeout : iTimeout),pAttributes);
	}catch(EndOfDataException& e){

		if(iRecycleMode == RM_Never)
			throw;

		ptrBrowser=getSession()->createBrowser(destination);

		if(iRecycleMode == RM_Next)
			throw;

		return ptrBrowser->receive(0,pAttributes);
	}

}
/*************************************************************************/
BrowserInput::RecycleMode BrowserInput::StringToRecycleMode(const String& strValue){

	String strLCase;


	for(String::const_iterator it=strValue.begin(); it!=strValue.end(); it++){
		strLCase+=std::tolower(*it);
	}

	if(strLCase.compare("always")==0)
		return RM_Always;

	if(strLCase.compare("never")==0)
		return RM_Never;

	if(strLCase.compare("next")==0)
		return RM_Next;

	if(strLCase.compare("immediate")==0)
		return RM_Immediate;

	IAS_THROW(ConfigException(strValue+" <= cannot be decoded into a browser recycle mode."));

}
/*************************************************************************/
}
}
}
}
}
