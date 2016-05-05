/*
 * File: IAS-QSystemLib/src/qs/Impl/net/Message.cpp
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

#include <qs/Impl/base/Attributes.h>

#include <commonlib/commonlib.h>
#include "Session.h"

namespace IAS {
namespace QS {
namespace Net {

/*************************************************************************/
Message::Message(){
	IAS_TRACER;
	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();
}
/*************************************************************************/
Message::Message(API::Message* pMessage){
	IAS_TRACER;

	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create(*pMessage->getAttributes());

	ptrContent=IAS_DFT_FACTORY<Content>::Create();
	MiscTools::CopyStreams(*pMessage->getContent(),*ptrContent);
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
QS::Base::Attributes* Message::getBaseAttributes()const{
	IAS_TRACER;
	return ptrAttributes;
}
/*************************************************************************/
const String& Message::getHost()const{
	IAS_TRACER;
	return strHost;
}
/*************************************************************************/
void Message::setHost(const String& strHost){
	IAS_TRACER;
	this->strHost=strHost;
}
/*************************************************************************/
const String& Message::getResource()const{
	IAS_TRACER;
	return strResource;
}
/*************************************************************************/
void Message::setResource(const String& strResource){
	IAS_TRACER;
	this->strResource=strResource;
}
/*************************************************************************/

}
}
}
