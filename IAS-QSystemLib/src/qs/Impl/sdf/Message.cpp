/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Message.cpp
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
#include "Message.h"
#include<qs/log/LogLevel.h>
#include "ContentManager.h"
#include <qs/Impl/base/Attributes.h>

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/shared/MsgEntry.h>

namespace IAS {
namespace QS {
namespace SDF {

/*************************************************************************/
Message::Message(){
	IAS_TRACER;
	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();
}
/*************************************************************************/
Message::Message(std::istream& is){
	IAS_TRACER;
	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();

	MiscTools::CopyStreams(is,*ptrContent);
}
/*************************************************************************/
void Message::write(std::ostream& os){
	IAS_TRACER;

	MiscTools::CopyStreams(*ptrContent,os);
}
/*************************************************************************/
Message::~Message() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Content* Message::getContent(){
	IAS_TRACER;
	return ptrContent;
}
/*************************************************************************/
API::Attributes* Message::getAttributes(){
	IAS_TRACER;
	return ptrAttributes;
}
/*************************************************************************/

}
}
}
