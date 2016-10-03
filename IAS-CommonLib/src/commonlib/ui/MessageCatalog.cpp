/*
 * File: IAS-CommonLib/src/commonlib/ui/MessageCatalog.cpp
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

#include "MessageCatalog.h"
#include "../commonlib.h"
#include "commonlib/tools/EnvTools.h"
#include "commonlib/sys/fs/DirectoryReader.h"

#include "../threads/Mutex.h"

/*************************************************************************/
namespace IAS{

const char MessageCatalog::SPECIAL_DSPMSG_CHAR = '&';

/*************************************************************************/
MessageCatalog::MessageCatalog(){
	IAS_TRACER;

}
/*************************************************************************/
MessageCatalog::~MessageCatalog(){
	IAS_TRACER;

}
/*************************************************************************/
void MessageCatalog::init(){
	IAS_TRACER;
}
/*************************************************************************/
void MessageCatalog::loadFile(const String& strFileName){
	IAS_TRACER;

	IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"Loading Messages from:["<<strFileName<<"]");


	InputFile ifMessages(strFileName);
	ifMessages.open();

	if(! ifMessages.isOpenedAndGood() ){
		IAS_THROW(ConfigException(strFileName));
	}

	int iLineNo=0;

	while(ifMessages.isOpenedAndGood()){

		char sLine[256];
		ifMessages.getStreamRef().getline(sLine, 255, '\n');

			iLineNo++;

			if(*sLine == '#')
				continue;

			String strLine(sLine);
			int iPos = strLine.find('=');

			if(iPos == String::npos){
				IAS_THROW(ConfigException("Missing '='",strFileName.c_str(),iLineNo));
			}

			int iIdx=TypeTools::StringToInt(strLine.substr(0,iPos));
			String strMessage=strLine.substr(iPos+1);

			IAS_LOG(IAS::LogLevel::INSTANCE.isDetailedInfo(),"["<<iIdx<<"]=["<<strMessage<<"]");

			hmMessages[iIdx]   		= strMessage;

			return;
		}

}
/*************************************************************************/
void MessageCatalog::MessageCatalogUpdater::UpdateCatalog(MsgId idMsg, const String& strMessage){
	MessageCatalog::GetInstance()->update(idMsg, strMessage);
}
/*************************************************************************/
static Mutex _mutex;
/*************************************************************************/
void MessageCatalog::update(MsgId idMsg, const String& strMessage){

	Mutex::Locker locker(_mutex);

	if(hmMessages.count(idMsg)){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Two User Messages with the same id: "<<idMsg<<", has: "<<hmMessages[idMsg]<<", got: "<<strMessage);
		return;
	}

	hmMessages[idMsg] = strMessage;
}
/*************************************************************************/
void MessageCatalog::fillMessageText(String& strOutput,
					 				 MsgId   iMessageId,
									 const std::vector<String>& tabValues){
	IAS_TRACER;

	String strMsg;

	Mutex::Locker locker(_mutex);

	if(hmMessages.count(iMessageId) == 0){
		StringStream ss;
		ss<<"IASE-0000 No Text for message with id="<<iMessageId;
		strMsg=ss.str();
	}else{
		 strMsg=hmMessages[iMessageId];
	}


	String::iterator it;
	char c;

	for(it=strMsg.begin(); it != strMsg.end(); it++){
		c=*it;
		if(c != SPECIAL_DSPMSG_CHAR)
			strOutput+=c;
		else{
			if(it != strMsg.end()){
				c=*(++it);
				switch(c){
					case '1': if(tabValues.size() >= 1) strOutput+=tabValues[0]; break;
					case '2': if(tabValues.size() >= 2) strOutput+=tabValues[1]; break;
					case '3': if(tabValues.size() >= 3) strOutput+=tabValues[2]; break;
					case '4': if(tabValues.size() >= 4) strOutput+=tabValues[3]; break;
				  default:
					  strOutput+=SPECIAL_DSPMSG_CHAR;
					  strOutput+=c;
				}/* switch */
			}else
				strOutput+=SPECIAL_DSPMSG_CHAR;
		}/* IF: '&_' */

	}/* FOR: */

}
/*************************************************************************/
const String MessageCatalog::ENV_DSP_MSGS_DIR("IAS_DSP_MSGS_DIR");
const String MessageCatalog::ENV_DSP_MSGS_DIR_DEFALUT("msgs");
/*************************************************************************/
void MessageCatalog::loadExternalMessages(){
	IAS_TRACER;

	Mutex::Locker locker(_mutex);

	String strDirectory(ENV_DSP_MSGS_DIR_DEFALUT);
	EnvTools::GetEnv(ENV_DSP_MSGS_DIR,strDirectory);

	IAS_DFT_FACTORY<SYS::FS::DirectoryReader>::PtrHolder ptrDirectoryReader;

	ptrDirectoryReader=IAS_DFT_FACTORY<SYS::FS::DirectoryReader>::Create(strDirectory);
	ptrDirectoryReader->read();

	const SYS::FS::DirectoryReader::EntriesList& lstEntries=ptrDirectoryReader->getEntries();

	for(int iIdx=0; iIdx<lstEntries.size(); iIdx++){
		String strFile(lstEntries[iIdx]->strFile);
		//TODO (LL) match sufix.
		loadFile(strFile);
	}
}
/*************************************************************************/
}/* namespace IAS */

