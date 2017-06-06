/*
 * File: IAS-CommonLib/src/commonlib/ui/UserMessage.cpp
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#include "UserMessage.h"
#include "../commonlib.h"
#include "../time/Timestamp.h"
#include <unistd.h>
#include <iostream>
#include "../logger/Logger.h"

namespace IAS{

/*************************************************************************/
UserMessage::UserMessage(MessageCatalog::MsgId id):id(id){
	IAS_TRACER;
}
/*************************************************************************/
UserMessage::~UserMessage(){
	IAS_TRACER;
	String strText;
	MessageCatalog::GetInstance()->fillMessageText(strText,id,tabValues);
	show(strText);
}
/*************************************************************************/
UserMessage& UserMessage::operator<<(const char *s) {
    tabValues.push_back(s);
    return *this;
}
/*************************************************************************/
UserMessage& UserMessage::operator<<(const String& s) {
	tabValues.push_back(s);
    return *this;
}
/*************************************************************************/
UserMessage& UserMessage::operator<<(long iValue) {
	tabValues.push_back(TypeTools::IntToString(iValue));
    return *this;
}
/*************************************************************************/
void UserMessage::show(const String& strText){
	IAS_TRACER;
	// TODO (M) syslog

	static Mutex mutex;

	Mutex::Locker locker(mutex);

	if(LogLevel::INSTANCE.isDspMsg())
		Logger::GetInstance()->addEntry(strText.c_str());

}

}
